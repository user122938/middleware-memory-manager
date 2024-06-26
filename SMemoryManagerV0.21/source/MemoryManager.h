#pragma once

#include "IMemoryManager.h"
#include "PageIndex.h"
#include "Exception.h"
#include "ExceptionManager.h"

    /**
   	*
   	* @brief 메모리 할당, 해제 관리 클래스
    * @details 메모리 공간을 페이지 단위로 나누어 PageIndex배열을 생성하고 객체를 할당, 해제한다.
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class MemoryManager : public IMemoryManager {
private:
	char* pBuffer;
	size_t sizeBuffer;

	int numPages;
	size_t sizePage;
	PageIndex* aPageIndex;

	size_t normalizeSize(size_t size) {
		size_t size1 = size >> 4;
		size_t size2 = size1 << 4;
		size = ((size == size2) ? size1 : ++size1) << 4;
		return size;
	}
	PageIndex* allocateNewPages(size_t sizeSlot) {
		int numPagesRequired = (sizeSlot % sizePage) == 0 ? (int)(sizeSlot / sizePage) : (int)(sizeSlot / sizePage) + 1;

		PageIndex* pPageIndexAllocated = nullptr;
		bool bFound = false;
		int numConsequtivePages = 0;

		for (int i = numPages - 1; i >= 0; i--) {
			if (bFound) {
				if (this->aPageIndex[i].isAllocated()) {
					break;
				}
				else {
					numConsequtivePages++;
					this->aPageIndex[i].setNumConsecutivePages(numConsequtivePages);
				}
			}
			else {
				if (!this->aPageIndex[i].isAllocated()) {
					if (this->aPageIndex[i].getNumConsecutivePages() == numPagesRequired) {
						pPageIndexAllocated = &(this->aPageIndex[i]);
						for (int k = i; k < i + numPagesRequired; k++) {
							this->aPageIndex[k].initialize(sizeSlot);
							this->aPageIndex[k].setBAllocated(true);
						}
						bFound = true;
					}
				}
			}
		}
		return pPageIndexAllocated;
	}

	void collectGarbage() {

	}

public:
	/**
 	*
 	* @brief malloc함수를 통해 MemoryManager 생성
	* @param size MemoryManager 크기
	* @return MemoryManager 메모리 주소
 	* @date 2024-05-21
 	* @version 0.21
 	*
 	*/
	void* operator new(size_t size) {
		return malloc(size);
	}

	/**
 	*
 	* @brief free함수를 통해 MemoryManager 할당 해제
	* @param pObject MemoryManager 메모리 주소
 	* @date 2024-05-21
 	* @version 0.21
 	*
 	*/
	void operator delete(void* pObject) {
		free(pObject);
	}

	/**
 	*
 	* @brief 메모리 관리 객체 생성자
 	* @details 메모리 공간을 페이지 크기 만큼 나누어 PageIndex배열을 생성하고 초기화한다.
	* @param pBuffer 메모리 시작주소
	* @param sizeBuffer 메모리 크기
	* @param sizePage 한 페이지 크기
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	MemoryManager(char* pBuffer, size_t sizeBuffer, size_t sizePage) :
		pBuffer(pBuffer),
		sizeBuffer(sizeBuffer),
		sizePage(sizePage)
	{
		numPages = (int)(sizeBuffer / sizePage);
		aPageIndex = new PageIndex[numPages];

		char* pBufferCurrent = pBuffer;
		for (int i = 0; i < numPages; i++) {
			aPageIndex[i].setPPage(pBufferCurrent);
			aPageIndex[i].setSizePage(sizePage);
			aPageIndex[i].setNumConsecutivePages(numPages - i);
			pBufferCurrent = pBufferCurrent + sizePage;
		}
	}

	/**
 	*
 	* @brief 메모리 관리 객체 소멸자
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual ~MemoryManager() {
	}

	/**
 	*
 	* @brief 메모리에 객체를 할당하는 함수
 	* @details 객체 크기를 16배수의 slot으로 일반화하고 할당할 PageIndex를 뒤에서부터 찾아 할당한다.
	* @param sizeMemory 할당할 객체 크기
	* @param pName 할당할 객체 이름
	* @return 할당된 객체의 메모리 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void* allocate(size_t sizeMemory, const char* pName) {
		size_t sizeSlot = normalizeSize(sizeMemory);

		PageIndex* pPageIndexFound = nullptr;
		for (int i = 0; i < numPages; i++) {
			if (this->aPageIndex[i].isAllocated()) {
				if (this->aPageIndex[i].getSizeSlot() == sizeSlot) {
					pPageIndexFound = &(this->aPageIndex[i]);
					break;
				}
			}
		}

		if (pPageIndexFound == nullptr) {
			pPageIndexFound = allocateNewPages(sizeSlot);
			if (pPageIndexFound == nullptr) {
				throw Exception(Exception::ECode::eOutOfMemory, "allocateNewPages1");
			}
		}

		void* pSlotAllocated = pPageIndexFound->allocate(sizeSlot, pName);
		if (pSlotAllocated == nullptr) {
			pPageIndexFound = allocateNewPages(sizeSlot);
			if (pPageIndexFound == nullptr) {
				throw Exception(Exception::ECode::eOutOfMemory, "allocateNewPages2");
			}
			else {
				pSlotAllocated = pPageIndexFound->allocate(sizeSlot, pName);
			}
		}
		return pSlotAllocated;
	}

	/**
 	*
 	* @brief 객체를 할당 해제하는 함수
 	* @details 객체 주소에 해당하는 PageIndex를 찾아 객체를 할당 해제 후 빈 페이지를 정리한다.
	* @param pObject 할당 해제할 객체 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void dellocate(void* pObject) {
		size_t offset = (size_t)pObject - (size_t)(this->pBuffer);
		int pageIndex = (int)(offset / sizePage);
		bool isEmpty = this->aPageIndex[pageIndex].dellocate(pObject);
		if (isEmpty) {
			// this->aPageIndex[pageIndex].finalize();
			for (int i = 0; i < this->aPageIndex[pageIndex].getNumConsecutivePages(); i++) {
				this->aPageIndex[pageIndex + i].finalize();
			}
			for (int i = 0; i < this->aPageIndex[pageIndex].getNumConsecutivePages(); i++) {
				this->aPageIndex[pageIndex + i].finalize();
			}
		}
		int startConsecutivePages = this->numPages - 1;
		for (int i = pageIndex; i < numPages; i++) {
			if (this->aPageIndex[i].isAllocated()) { 
				startConsecutivePages = i - 1;
				break; 
			}
		}
		int numConsecutivePages = 1;
		for (int i = startConsecutivePages; i >= 0 || this->aPageIndex[pageIndex].isAllocated(); i--) {
			this->aPageIndex[i].setNumConsecutivePages(numConsecutivePages);
			numConsecutivePages++;
		}
		// ===============
		this->collectGarbage();
		// ===============
	}

	/**
 	*
 	* @brief 객체 주소에 해당하는 SlotIndex를 찾는 함수
	* @details 객체 주소에 해당하는 PageIndex를 찾고 PageIndex의 검색함수를 호출해 SlotIndex를 찾고 반환한다.
	* @param pObject 객체 주소
	* @return 객체 주소에 해당하는 SlotIndex
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	SlotIndex* findASlotIndex(void* pObject) {
		size_t offset = (size_t)pObject - (size_t)(this->pBuffer);
		int pageIndex = (int)(offset / sizePage);
		SlotIndex* pSlotIndexFound = this->aPageIndex[pageIndex].findASlotIndex(pObject);
		return pSlotIndexFound;
	}

	/**
 	*
 	* @brief 객체 주소에 해당하는 PageIndex를 찾는 함수
	* @details 객체 주소를 받아 페이지 번호를 찾고 해당하는 PageIndex를 반환한다.
	* @param pObject 객체 주소
	* @return 객체 주소에 해당하는 PageIndex
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	PageIndex findAPageIndex(void* pObject) {
		size_t offset = (size_t)pObject - (size_t)(this->pBuffer);
		int pageIndex = (int)(offset / sizePage);
		return this->aPageIndex[pageIndex];
	}

	/**
 	*
 	* @brief 메모리 할당 상태 출력 함수
	* @details 반복문으로 PageIndex배열의 할당 상태(슬롯 크기, 연결된 페이지)를 출력, 페이지 할당 상태 출력함수 호출.
 	* @date 2024-05-02
 	* @version 0.21
 	*
 	*/
	void showStatus() {
		printf("Start==========================================\n");
		for (int i = 0; i < numPages; i++) {
			for (int j = 0; j < aPageIndex[i].getNumConsecutivePages(); j++) {
				printf("PageIndex%d(SizeSlot=%d, ConsecutivePages=%d)\n", i + j, (int)aPageIndex[i + j].getSizeSlot(), aPageIndex[i + j].getNumConsecutivePages());
			}
			this->aPageIndex[i].showStatus();
			i = i + aPageIndex[i].getNumConsecutivePages() - 1;
		}
		printf("End============================================\n");
	}
};
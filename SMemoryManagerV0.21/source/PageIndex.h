#pragma once

#include "SlotIndex.h"
#include "IObject.h"

	/**
   	*
   	* @brief 페이지 내 Slot 할당, 해제 클래스
	* @details SlotIndex배열에 SlotIndex객체를 할당, 해제 및 할당 상태를 출력할 수 있다.
   	* @date 2024-05-02
   	* @version 0.21
   	*
   	*/
class PageIndex {

private:
	static int s_countId;

	int id;
	char* pPage;
	size_t sizePage;
	int numConsecutivePages;
	bool bAllocated;

	size_t sizeSlot;
	int numMaxSlots;
	SlotIndex* aSlotIndex;
	int numSlotsAvailable;

public:
	/**
 	*
 	* @brief malloc함수를 통해 PageIndex 생성
	* @param size PageIndex 크기
	* @return PageIndex 메모리 주소
 	* @date 2024-05-21
 	* @version 0.21
 	*
 	*/
	void* operator new(size_t size) {
		return malloc(size);
	}
	
	/**
 	*
 	* @brief free함수를 통해 PageIndex 할당 해제
	* @param pObject PageIndex 메모리 주소
 	* @date 2024-05-21
 	* @version 0.21
 	*
 	*/
	void operator delete(void* pObject) {
		free(pObject);
	}

	/**
 	*
 	* @brief 페이지 아이디를 반환하는 함수
	* @return PageIndex 아이디
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	int getId() { return this->id; }

	/**
 	*
 	* @brief PageIndex의 시작주소를 반환하는 함수
	* @return PageIndex 시작주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setPPage(char* pPage) { this->pPage = pPage; }

	/**
 	*
 	* @brief 페이지 크기를 지정하는 함수
	* @param sizePage 페이지 크기
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setSizePage(size_t sizePage) { this->sizePage = sizePage; }

	/**
 	*
 	* @brief 페이지 뒤에 연속된 비어있는 페이지 갯수 값을 지정하는 함수
	* @param numConsecutivePages 페이지 뒤에 연속된 비어있는 페이지 갯수 값
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setNumConsecutivePages(int numConsecutivePages) { this->numConsecutivePages = numConsecutivePages; }

	/**
 	*
 	* @brief 페이지 뒤에 연속된 비어있는 페이지 갯수 값을 반환하는 함수
	* @return 페이지 뒤에 연속된 비어있는 페이지 갯수 값
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	int getNumConsecutivePages() { return this->numConsecutivePages; }

	/**
 	*
 	* @brief 페이지 할당 상태를 반환하는 함수
	* @return 페이지 할당 상태
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	bool isAllocated() { return this->bAllocated; }

	/**
 	*
 	* @brief 페이지 할당 상태를 지정하는 함수
	* @param bAllocated 페이지 할당 상태
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setBAllocated(bool bAllocated) { this->bAllocated = bAllocated; }

	/**
 	*
 	* @brief 페이지의 슬롯 크기를 반환하는 함수
	* @return 페이지의 슬롯 크기
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	size_t getSizeSlot() { return this->sizeSlot; }
	
	/**
 	*
 	* @brief PageIndex 생성자
	* @details 객체 아이디를 설정하고 나머지 값은 정의되지 않은 값으로 초기화한다.
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	PageIndex() :
		id(s_countId++),
		pPage(nullptr),
		sizePage(NOT_DEFINED),
		numConsecutivePages(NOT_DEFINED),
		bAllocated(false),

		sizeSlot(NOT_DEFINED),
		numMaxSlots(NOT_DEFINED),
		aSlotIndex(nullptr),
		numSlotsAvailable(NOT_DEFINED)
	{
	}

	/**
 	*
 	* @brief 페이지 소멸자
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	~PageIndex() {}

	/**
 	*
 	* @brief 페이지 초기화 함수
	* @details 페이지 내 슬롯의 크기를 설정하고 슬롯 인덱스 배열을 할당한다.
	* @param sizeSlot 슬롯 크기
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void initialize(size_t sizeSlot) {
		this->sizeSlot = sizeSlot;
		this->numMaxSlots = (int)(sizePage < sizeSlot ? 1 : sizePage / sizeSlot);
		this->numSlotsAvailable = numMaxSlots;
		this->aSlotIndex = new SlotIndex[numMaxSlots];
		char* pCurrent = this->pPage;
		for (int i = 0; i < numMaxSlots; i++) {
			aSlotIndex[i].setPMemory(pCurrent);
			pCurrent = pCurrent + sizeSlot;
		}
		this->setBAllocated(true);
	}

	/**
 	*
 	* @brief 페이지 할당 해제 함수
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void finalize() {
		this->setBAllocated(false);
	}

	/**
 	*
 	* @brief 슬롯 할당 함수
 	* @details 할당 가능한 슬롯을 찾아 객체 이름을 설정하고 할당 상태를 변경한다.
	* @param size 할당할 슬롯 크기
	* @param pNameObject 할당할 객체 이름
	* @return 할당된 슬롯의 메모리 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void* allocate(size_t size, const char* pNameObject) {
		void* pMemoryAllocated = nullptr;
		for (int i = 0; i < this->numMaxSlots; i++) {
			if (!this->aSlotIndex[i].isAllocated()) {
				this->aSlotIndex[i].setNameObject(pNameObject);
				this->aSlotIndex[i].setBAllocated(true);
				pMemoryAllocated = this->aSlotIndex[i].getPMemory();
				this->numSlotsAvailable--;
				break;
			}
		}
		return pMemoryAllocated;
	}

	/**
 	*
 	* @brief 슬롯 할당 해제 함수
 	* @details Slot메모리 주소를 받아 해당 SlotIndex 할당 상태를 변경하고 할당 가능한 슬롯의 개수를 증가시킨다.
	* @param pMemory 할당 해제할 Slot의 메모리 주소
	* @return 페이지 내 모든 슬롯이 비어있는지 여부
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	bool dellocate(void* pMemory) {
		size_t offset = (char*)pMemory - pPage;
		int indexSlot = (int)(offset / sizeSlot);
		this->aSlotIndex[indexSlot].setBAllocated(false);
		this->numSlotsAvailable++;
		bool isEmpty = false;
		if (this->numSlotsAvailable == this->numMaxSlots) {
			isEmpty = true;
		}
		return isEmpty;
	}

	/**
 	*
 	* @brief 메모리 주소에 해당하는 SlotIndex를 찾는 함수
	* @details 메모리 주소를 받아 Slot 번호를 찾고 해당하는 SlotIndex를 반환한다.
	* @param pMemory 메모리 주소
	* @return 메모리 주소에 해당하는 SlotIndex
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	SlotIndex* findASlotIndex(void* pMemory) {
		size_t offset = (char*)pMemory - pPage;
		int indexSlot = (int)(offset / sizeSlot);
		return &(this->aSlotIndex[indexSlot]);
	}

	/**
 	*
 	* @brief 페이지 내부 할당 상태 출력 함수
	* @details 반복문으로 SlotIndex배열의 할당 상태(클래스 및 객체 이름, 객체 아이디)를 출력
 	* @date 2024-05-02
 	* @version 0.21
 	*
 	*/
	void showStatus() {
		printf("-----------------------------------------------\n");
		if (!bAllocated) {
			printf("|  EMPTY SLOT\n");
		}
		else {
			for (int i = 0; i < numMaxSlots; i++) {
				if (this->aSlotIndex[i].isAllocated()) {
					IObject* pObject = (IObject*)(this->aSlotIndex[i].getPMemory());
					printf("|  %s::%s(%d)\n", pObject->getNameClass(), aSlotIndex[i].getNameObject(), pObject->getId());
				}
				else {
					printf("|  EMPTY SLOT\n");
				}
			}
		}
		printf("-----------------------------------------------\n\n");
	}
};
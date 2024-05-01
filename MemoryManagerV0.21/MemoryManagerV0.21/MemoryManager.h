#pragma once

#include "IMemoryManager.h"
#include "PageIndex.h"
#include "Exception.h"
#include "ExceptionManager.h"

class MemoryManager : public IMemoryManager {
private:

	char* pBuffer;
	size_t sizeBuffer;
	size_t sizePage;

	int numPages;
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
	void* operator new(size_t size) {
		return malloc(size);
	}
	void operator delete(void* pObject) {
		free(pObject);
	}

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
			aPageIndex[i].setNumConsecutivePages(numPages-i);
			pBufferCurrent = pBufferCurrent + sizePage;
		}
	}
	virtual ~MemoryManager() {
	}


	void* allocate(size_t sizeMemory, const char *pName) {
		// multiple x
		size_t sizeSlot = normalizeSize(sizeMemory);

		// search for allocated PageIndex s
		PageIndex* pPageIndexFound = nullptr;
		for (int i = 0; i < numPages; i++) {
			if (this->aPageIndex[i].isAllocated()) {
				if (this->aPageIndex[i].getSizeSlot() == sizeSlot) {
					// found
					pPageIndexFound = &(this->aPageIndex[i]);
					break;
				}
			}
		}

		// not found
		if (pPageIndexFound == nullptr) {
			pPageIndexFound = allocateNewPages(sizeSlot);
			if (pPageIndexFound == nullptr) {
				// out of memory
				Exception ex(Exception::ECode::eOutOfMemory, "allocateNewPages1");
				ExceptionManager::logException(ex);
				throw ex;
			}
		}

		// allocate a slot
		void* pSlotAllocated = pPageIndexFound->allocate(sizeSlot, pName);
		// no more slots
		if (pSlotAllocated == nullptr) {
			pPageIndexFound = allocateNewPages(sizeSlot);
			if (pPageIndexFound == nullptr) {
				// out of memory
				Exception ex(Exception::ECode::eOutOfMemory, "allocateNewPages2");
				ExceptionManager::logException(ex);
				throw ex;
			} else {
				pSlotAllocated = pPageIndexFound->allocate(sizeSlot, pName);
			}
		}
		return pSlotAllocated;
	}

	void dellocate(void* pObject) {
		size_t offset = (size_t)pObject - (size_t)(this->pBuffer);
		int pageIndex = (int)(offset/sizePage);
		bool isEmpty = this->aPageIndex[pageIndex].dellocate(pObject);
		if (isEmpty) {
			// this->aPageIndex[pageIndex].finalize();
			for (int i = 0; i < this->aPageIndex[pageIndex].getNumConsecutivePages(); i++) {
				this->aPageIndex[pageIndex + i].finalize();
			}
		}
		// ===============
		this->collectGarbage();
		// ===============
	}

	SlotIndex* findASlotIndex(void* pObject) {
		size_t offset = (size_t)pObject - (size_t)(this->pBuffer);
		int pageIndex = (int)(offset / sizePage);
		SlotIndex* pSlotIndexFound = this->aPageIndex[pageIndex].findASlotIndex(pObject);
		return pSlotIndexFound;
	}

	void showStatus() {
		printf("Start==========================================\n");
		for (int i = 0; i < numPages; i++) {
			if (this->aPageIndex[i].isAllocated()) {
				printf("PageIndex%d(SizeSlot=%zu, ConsecutivePages=%d)\n", i, aPageIndex[i].getSizeSlot(), aPageIndex[i].getNumConsecutivePages());
				this->aPageIndex[i].showStatus();
			}
		}
		printf("End==========================================\n");
	}
};


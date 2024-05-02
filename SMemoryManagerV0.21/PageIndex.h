#pragma once

#include "SlotIndex.h"
#include "IObject.h"

class PageIndex {

private:
	static int s_countId;
	// memory allocated
	int id;
	char* pPage;
	size_t sizePage;
	int numConsecutivePages;
	bool bAllocated;

	// slots
	size_t sizeSlot;
	int numMaxSlots;
	SlotIndex* aSlotIndex;
	int numSlotsAvailable;

public:
	// static
	void* operator new(size_t size) {
		return malloc(size);
	}
	void operator delete(void* pObject) {
		free(pObject);
	}
	// getters and setters
	int getId() { return this->id; }

	void setPPage(char* pPage) { this->pPage = pPage; }
	void setSizePage(size_t sizePage) { this->sizePage = sizePage; }
	void setNumConsecutivePages(int numConsecutivePages) { this->numConsecutivePages = numConsecutivePages; }
	int getNumConsecutivePages() { return this->numConsecutivePages; }
	bool isAllocated() { return this->bAllocated; }
	void setBAllocated(bool bAllocated) { this->bAllocated = bAllocated; }

	size_t getSizeSlot() { return this->sizeSlot; }
	//	void setSizeSlot(size_t sizeSlot) { this->sizeSlot = sizeSlot; }

		// constructors
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
	~PageIndex() {}

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
	void finalize() {
		this->setBAllocated(false);
	}

	// methods
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

	SlotIndex* findASlotIndex(void* pMemory) {
		size_t offset = (char*)pMemory - pPage;
		int indexSlot = (int)(offset / sizeSlot);
		return &(this->aSlotIndex[indexSlot]);
	}

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

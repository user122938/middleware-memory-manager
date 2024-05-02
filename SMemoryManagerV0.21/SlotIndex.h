#pragma once

#include "ISlotIndex.h"
#include "Type.h"

class SlotIndex : public ISlotIndex {
private:
	void* pMemory;
	char* pNameObject;
	bool bAllocated;
public:
	SlotIndex() :
		pMemory(nullptr),
		pNameObject(nullptr),
		bAllocated(false)
	{
	}
	~SlotIndex() {}

	void setPMemory(void* pMemory) { this->pMemory = pMemory; }
	void* getPMemory() { return this->pMemory; }
	void setNameObject(const char* pNameObject) {
		this->pNameObject = strcpy(pNameObject);
	}
	char* getNameObject() { return this->pNameObject; }
	void setBAllocated(bool bAllocated) { this->bAllocated = bAllocated; }
	bool isAllocated() { return this->bAllocated; }
};


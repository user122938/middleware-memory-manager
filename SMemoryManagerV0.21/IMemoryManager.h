#pragma once

#include "ISlotIndex.h"
#include "PageIndex.h"

class IMemoryManager
{
public:
	virtual void* allocate(size_t sizeSlot, const char* pName) = 0;
	virtual void dellocate(void* pObject) = 0;
	virtual ISlotIndex* findASlotIndex(void* pObject) = 0;
	virtual PageIndex findAPageIndex(void* pObject) = 0;
	virtual void showStatus() = 0;
};


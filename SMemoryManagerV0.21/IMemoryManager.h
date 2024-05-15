#pragma once

#include "ISlotIndex.h"
#include "PageIndex.h"

/**
   *
   * @brief Memory Manager Interface
   * @date 2024-05-02
   * @version 0.21
   *
   */
class IMemoryManager
{
public:
	virtual void* allocate(size_t sizeSlot, const char* pName) = 0;
	virtual void dellocate(void* pObject) = 0;
	virtual ISlotIndex* findASlotIndex(void* pObject) = 0;
	virtual PageIndex findAPageIndex(void* pObject) = 0;
	virtual void showStatus() = 0;
};


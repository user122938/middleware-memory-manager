#pragma once
#include "../SMemoryManagerV0.21/Type.h"
#include "../SMemoryManagerV0.21/Object.h"
#include "../SMemoryManagerV0.21/IMemoryManager.h"
#include "../SMemoryManagerV0.21/ISlotIndex.h"

class TestObject : public Object
{
private:
	int id;
	char* pNameClass;

public:

	void* operator new (size_t size, size_t objectSize, const char* pName) {
		void* pAllocated = s_pMemoryManager->allocate(objectSize, pName);
		return pAllocated;
	}
	void operator delete(void* pAllocated) {
		s_pMemoryManager->dellocate(pAllocated);
	}
	void operator delete(void* pObject, const char* pName) {
		s_pMemoryManager->dellocate(pObject);
	}

};


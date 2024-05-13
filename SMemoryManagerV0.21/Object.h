#pragma once

#include "Type.h"
#include "IObject.h"
#include "IMemoryManager.h"
#include "ISlotIndex.h"

/**
   *
   * @brief Object's superclass
   * @details Superclass of all object. It provides new, delete operators and getter for id, nameClass, nameObject, sizeSlot.
   * @date 2024-05-02
   * @version 0.21
   *
   */
class Object: public IObject
{
private:
	int id;
	char *pNameClass;

public:
	static int s_counterId;
	static IMemoryManager* s_pMemoryManager;

	void* operator new (size_t size, const char* pName) {
		void* pAllocated = s_pMemoryManager->allocate(size, pName);
		return pAllocated;
	}
	void operator delete(void* pAllocated) {
		s_pMemoryManager->dellocate(pAllocated);
	}
	void operator delete(void* pObject, const char* pName) {
		s_pMemoryManager->dellocate(pObject);
	}

	int getId() { return this->id; }
	char* getNameClass() { return this->pNameClass; }
	char* getNameObject() {
		ISlotIndex* pSlotIndex = s_pMemoryManager->findASlotIndex(this);
		return pSlotIndex->getNameObject();
	}
	size_t getSizeSlot() {
		PageIndex pSlotIndex = s_pMemoryManager->findAPageIndex(this);
		return pSlotIndex.getSizeSlot();
	}

	Object(const char* pClassName = "Object") :
		id(s_counterId++)
	{
		this->pNameClass = strcpy(pClassName);
	}
	virtual ~Object() {
	}
};


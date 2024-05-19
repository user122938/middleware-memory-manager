#pragma once

#include "Type.h"
#include "IObject.h"
#include "IMemoryManager.h"
#include "ISlotIndex.h"

	/**
   	*
   	* @brief 메모리에 할당되는 객체를 만드는 클래스의 부모 클래스
	* @details 객체의 생성과 소멸, 객체의 정보를 반환하는 함수를 가지고 있다.
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class Object: public IObject
{
private:
	int id;
	char* pNameClass;

public:
	static int s_counterId;
	static IMemoryManager* s_pMemoryManager;

	/**
	* @brief 객체 생성시 메모리에 할당하는 함수
	* @details 객체를 생성할 때 메모리매니저에게 이름과 크기를 주면서 할당한다.
	* @param size 할당할 객체의 크기
	* @param pName 할당할 객체의 이름
	* @return 할당된 메모리의 포인터
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
	void* operator new (size_t size, const char* pName) {
		void* pAllocated = s_pMemoryManager->allocate(size, pName);
		return pAllocated;
	}

	/**
	* @brief 객체 삭제시 할당 해제하는 함수
	* @details 객체 주소를 메모리매니저에게 주면서 할당 해제한다.
	* @param pAllocated 할당 해제할 객체의 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void operator delete(void* pAllocated) {
		s_pMemoryManager->dellocate(pAllocated);
	}

	/**
	* @brief 객체 삭제시 할당 해제하는 함수
	* @details 객체 주소를 메모리매니저에게 주면서 할당 해제한다.
	* @param pAllocated 할당 해제할 객체의 주소
	* @param pName 할당 해제할 객체의 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void operator delete(void* pObject, const char* pName) {
		s_pMemoryManager->dellocate(pObject);
	}

	/**
	* @brief 객체 생성자
	* @details 객체 이름을 받아서 저장하고, 아이디를 부여한다.
	* @param pClassName 객체 이름(기본값: "Object")
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	Object(const char* pClassName = "Object") :
		id(s_counterId++)
	{
		this->pNameClass = strcpy(pClassName);
	}

	/**
	* @brief 객체 소멸자
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual ~Object() {
	}

	/**
	* @brief 객체 아이디를 반환하는 함수
	* @return 객체 아이디
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	int getId() { return this->id; }

	/**
	* @brief 객체를 생성할 때 사용한 클래스 이름을 반환하는 함수
	* @return 객체를 생성할 때 사용한 클래스 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	char* getNameClass() { return this->pNameClass; }

	/**
	* @brief 객체 이름을 반환하는 함수
	* @return 객체 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	char* getNameObject() {
		ISlotIndex* pSlotIndex = s_pMemoryManager->findASlotIndex(this);
		return pSlotIndex->getNameObject();
	}

	/**
	* @brief 객체가 할당된 Slot의 크기를 반환하는 함수
	* @return 객체가	할당된 Slot의 크기
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	size_t getSizeSlot() {
		PageIndex pSlotIndex = s_pMemoryManager->findAPageIndex(this);
		return pSlotIndex.getSizeSlot();
	}
};
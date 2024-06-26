#pragma once

#include "ISlotIndex.h"
#include "Type.h"

	/**
   	*
   	* @brief 페이지 내부에 할당되는 슬롯의 정보를 저장하는 클래스
	* @details 슬롯의 주소, 이름, 할당 상태를 저장하고 반환한다.
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class SlotIndex : public ISlotIndex {
private:
	void* pMemory;
	char* pNameObject;
	bool bAllocated;
public:
	/**
 	*
 	* @brief 슬롯 생성자
	* @details 슬롯의 주소, 이름, 할당 상태를 값이 없는 상태로 초기화한다.
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	SlotIndex() :
		pMemory(nullptr),
		pNameObject(nullptr),
		bAllocated(false)
	{
	}

	/**
 	*
 	* @brief 슬롯 소멸자
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	~SlotIndex() {}

	/**
 	*
 	* @brief 슬롯의 시작 주소를 설정하는 함수
	* @param pMemory 슬롯의 시작 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setPMemory(void* pMemory) { this->pMemory = pMemory; }

	/**
 	*
 	* @brief 슬롯의 시작 주소를 반환하는 함수
	* @return 슬롯의 시작 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void* getPMemory() { return this->pMemory; }

	/**
 	*
 	* @brief 슬롯의 할당된 객체의 이름을 설정하는 함수
	* @param pNameObject 슬롯의 할당된 객체의 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setNameObject(const char* pNameObject) {
		this->pNameObject = strcpy(pNameObject);
	}

	/**
 	*
 	* @brief 슬롯에 할당된 객체의 이름을 반환하는 함수
	* @return 슬롯에 할당된 객체의 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	char* getNameObject() { return this->pNameObject; }

	/**
 	*
 	* @brief 슬롯의 할당여부를 설정하는 함수
	* @param bAllocated 슬롯의 할당여부
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	void setBAllocated(bool bAllocated) { this->bAllocated = bAllocated; }

	/**
 	*
 	* @brief 슬롯의 할당여부를 반환하는 함수
	* @return 슬롯의 할당여부
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	bool isAllocated() { return this->bAllocated; }
};
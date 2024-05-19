#pragma once

#include "ISlotIndex.h"
#include "PageIndex.h"

	/**
   	*
   	* @brief 메모리 매니저 인터페이스
	* @details 메모리 할당/해제, slot 및 pageIndex 검색, 상태 출력을 위한 인터페이스
   	* @date 2024-05-02
   	* @version 0.21
   	*
   	*/
class IMemoryManager
{
public:
	/**
   	*
   	* @brief 메모리 할당
	* @details 슬롯크기, 이름을 받아 메모리 할당
	* @param sizeSlot 슬롯 크기
	* @param pName 할당할 객체 이름
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
	virtual void* allocate(size_t sizeSlot, const char* pName) = 0;

	/**
 	*
 	* @brief 메모리 해제
	* @details 할당 해제할 객체의 포인터를 받아 메모리 해제
	* @param pObject 할당 해제할 객체의 포인터
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual void dellocate(void* pObject) = 0;

	/**
 	*
 	* @brief SlotIndex 검색
	* @details 검색할 객체의 주소를 받아 SlotIndex 검색
	* @param pObject 검색할 객체의 주소
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual ISlotIndex* findASlotIndex(void* pObject) = 0;

	/**
 	*
 	* @brief PageIndex 검색
	* @details 검색할 객체의 포인터를 받아 PageIndex 검색
	* @param pObject 검색할 객체의 포인터
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual PageIndex findAPageIndex(void* pObject) = 0;

	/**
 	*
 	* @brief 메모리 할당 상태 출력
	* @details 현재 메모리 할당 상태를 콘솔에 출력
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual void showStatus() = 0;
};


#pragma once

	/**
   	*
   	* @brief SlotIndex 클래스의 인터페이스 클래스
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class ISlotIndex
{
public:
	/**
 	*
 	* @brief 슬롯에 할당된 객체의 이름을 반환하는 함수
	* @return 슬롯에 할당된 객체의 이름
 	* @date 2024-05-19
 	* @version 0.21
 	*
 	*/
	virtual char* getNameObject() = 0;
};


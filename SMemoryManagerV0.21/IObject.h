#pragma once

	/**
   	*
   	* @brief Object 클래스의 인터페이스 클래스
	* @details 객체의 아이디, 이름, 객체 이름을 반환한다.
   	* @date 2024-05-02
   	* @version 0.21
   	*
   	*/
class IObject
{
public:
	/**
 	*
 	* @brief 객체의 인터페이스 클래스
 	* @date 2024-05-02
 	* @version 0.21
 	*
 	*/
	virtual int getId() = 0;
	/**
 	*
 	* @brief 객체의 인터페이스 클래스
 	* @date 2024-05-02
 	* @version 0.21
 	*
 	*/
	virtual char* getNameClass() = 0;
	/**
 	*
 	* @brief 객체의 인터페이스 클래스
 	* @date 2024-05-02
 	* @version 0.21
 	*
 	*/
	virtual char* getNameObject() = 0;
};


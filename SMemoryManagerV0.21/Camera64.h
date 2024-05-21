#pragma once
#include "Object.h"

#define NUM_CAMERAS 5

	/**
   	*
   	* @brief 크기가 64인 테스트용 클래스
	* @details 생성자로 이름 저장, 배열 0~4까지의 값을 저장하고 출력
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class Camera64 : public Object {
private:
	int data[NUM_CAMERAS] = {};
	int id1;
	int id2;
	int id3;
	int id4;
public:
	/**
   	*
   	* @brief Camera64 생성자
	* @details 부모 클래스 생성자에 이름("Camera64") 전달, id 값 입력
   	* @date 2024-05-21
   	* @version 0.21
   	*
   	*/
	Camera64(const char* pName = "Camera64") :
		Object(pName),
		id1(1),
		id2(2),
		id3(3),
		id4(4)
	{
	}

	/**
	* 
 	* @brief Camera64 소멸자
 	* @date 2024-05-21
 	* @version 0.21
 	*
	*/
	virtual ~Camera64() {
	}

	/**
   	*
   	* @brief Camera64 실행 함수
	* @details data배열에 0~4까지(NUM_CAMERAS만큼)의 값을 저장하고 합계 출력
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
	void run() {
		for (int i = 0; i < NUM_CAMERAS; i++) {
			this->data[i] = i;
		}
		int sum = 0;
		for (int i = 0; i < NUM_CAMERAS; i++) {
			sum = sum + this->data[i];
		}
		printf("%s::%s(%d)::run()=%d\n", this->getNameClass(), this->getNameObject(), this->getId(), sum);
	}
};


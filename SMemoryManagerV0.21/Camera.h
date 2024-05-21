#pragma once
#include "Object.h"

#define NUM_CAMERAS 5

	/**
   	*
   	* @brief 크기가 48인 테스트용 클래스 
	* @details 생성자로 이름 저장, 배열에 0~4까지의 값을 저장하고 출력
   	* @date 2024-05-19
   	* @version 0.21
   	*
    */
class Camera : public Object {
private:
	int data[NUM_CAMERAS] = {};
public:
	/**
	* 
	*
    * @brief Camera 생성자
    * @datails 부모 생성자에 이름("Camera") 전달
    * @date 2024-05-19
    * @version 0.21
    *
	*/
	Camera(const char* pName = "Camera") :
		Object(pName)
	{
	}
	virtual ~Camera() {
	}

	/**
   	*
   	* @brief Camera 실행 함수
	* @datails data배열에 0~4까지(NUM_CAMERAS만큼)의 값을 저장하고 합계 출력
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


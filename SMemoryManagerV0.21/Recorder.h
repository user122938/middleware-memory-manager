#pragma once

#include "Object.h"

#define NUM_RECORDERS 20

	/**
   	*
   	* @brief 크기가 104인 테스트용 클래스
	* @details 생성자로 이름 저장, 배열에 0~20까지의 값을 저장하고 출력
   	* @date 2024-05-19
   	* @version 0.21
   	*
   	*/
class Recorder : public Object {
private:
	int data[NUM_RECORDERS] = {};
public:
	/**
	*
	*
 	* @brief 카메라 생성자
	* @datails 부모 생성자에 이름("Recorder") 전달
 	* @date 2024-05-19
 	* @version 0.21
 	*
	*/
	Recorder(const char* pName = "Recorder") :
		Object(pName)
	{
	}
	virtual ~Recorder() {
	}

	/**
	*
	*
 	* @brief Recorder 실행 함수
	* @datails data배열에 0~19까지(NUM_RECORDERS만큼)의 값을 저장하고 합계 출력
 	* @date 2024-05-19
 	* @version 0.21
 	*
	*/
	void run() {
		for (int i = 0; i < NUM_RECORDERS; i++) {
			this->data[i] = i;
		}
		int sum = 0;
		for (int i = 0; i < NUM_RECORDERS; i++) {
			sum = sum + this->data[i];
		}
		printf("%s::%s(%d)::run()=%d\n", this->getNameClass(), this->getNameObject(), this->getId(), sum);
	}
};
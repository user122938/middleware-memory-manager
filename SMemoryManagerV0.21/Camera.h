#pragma once
#include "Object.h"

#define NUM_CAMERAS 5

/**
   *
   * @brief Test Object: Camera
   * @details object size=48
   * @date 2024-05-02
   * @version 0.21
   *
   */
class Camera : public Object {
private:
	int data[NUM_CAMERAS] = {};
public:
	Camera(const char* pName = "Camera") :
		Object(pName)
	{
	}
	virtual ~Camera() {
	}

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


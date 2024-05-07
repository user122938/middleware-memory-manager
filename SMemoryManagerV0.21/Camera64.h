#pragma once
#include "Object.h"

#define NUM_CAMERAS 5

class Camera64 : public Object {
private:
	int data[NUM_CAMERAS] = {};
	int id1;
	int id2;
	int id3;
	int id4;
public:
	Camera64(const char* pName = "Camera64") :
		Object(pName),
		id1(1),
		id2(2),
		id3(3),
		id4(4)
	{
	}
	virtual ~Camera64() {
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


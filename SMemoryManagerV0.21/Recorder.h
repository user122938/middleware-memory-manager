#pragma once

#include "Object.h"

#define NUM_RECORDERS 20

/**
   *
   * @brief Test Object: Recorder
   * @details object size=104
   * @date 2024-05-02
   * @version 0.21
   *
   */
class Recorder : public Object {
private:
	int data[NUM_RECORDERS] = {};
public:
	Recorder(const char* pName = "Recorder") :
		Object(pName)
	{
	}
	virtual ~Recorder() {
	}

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
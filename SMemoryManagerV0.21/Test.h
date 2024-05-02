#pragma once
#include "Camera.h"
#include "Camera64.h"
#include "Recorder.h"

class Test{
private:
	int memorySpace;
public:
	Test(int memorySpace) :
		memorySpace(memorySpace)
	{
	}
	virtual ~Test() {
	}
	void smallSlotTest() {
		int objectNumber = memorySpace / 64;
		printf("small Slot Test [objectNumber: %d]\n", objectNumber);
		Camera** paCamera = new Camera * [objectNumber];
		for (int i = 0; i < objectNumber; i++) {
			char* pName = to_pchar(i);
			paCamera[i] = new(pName) Camera();
			paCamera[i]->run();
		}
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < objectNumber; i++) {
			delete paCamera[i];
		}
		Object::s_pMemoryManager->showStatus();
	}
	void equalSlotTest() {
		int objectNumber = memorySpace / 64;
		printf("equal Slot Test [objectNumber: %d]\n", objectNumber);
		Camera64** paCamera64 = new Camera64 * [objectNumber];
		for (int i = 0; i < objectNumber; i++) {
			char* pName = to_pchar(i);
			paCamera64[i] = new(pName) Camera64();
			paCamera64[i]->run();
		}
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < objectNumber; i++) {
			delete paCamera64[i];
		}
		Object::s_pMemoryManager->showStatus();
	}
	void bigSlotTest() {
		int objectNumber = memorySpace / 128;
		printf("big Slot Test [objectNumber: %d]\n", objectNumber);
		Recorder** paRecorder = new Recorder * [objectNumber];
		for (int i = 0; i < objectNumber; i++) {
			char* pName = to_pchar(i);
			paRecorder[i] = new(pName) Recorder();
			paRecorder[i]->run();
		}
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < objectNumber; i++) {
			delete paRecorder[i];
		}
		Object::s_pMemoryManager->showStatus();
	}
	void run() {
		
	}
};
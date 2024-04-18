#pragma once
#include "Object.h"

#include "Camera.h"
#include "Recorder.h"

// test1

class Main : public Object
{
public:
	Main(const char* pName = "Main") : Object(pName)	{
	}
	void initialize() {
	}
	void finalize() {
	}
	~Main() {
	}

	void run() {
		int numCameras = 5;
		int numRecorders = 5;
		Camera** paCamera = new Camera * [numCameras];
		Recorder** paRecorder = new Recorder * [numRecorders];
		
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < numCameras; i++) {
			char* pName = to_pchar(i);
			paCamera[i] = new(pName) Camera();
			paCamera[i]->run();

			paRecorder[i] = new(pName) Recorder();
			paRecorder[i]->run();
		}
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < numCameras; i++) {
			delete paCamera[i];
		}
		Object::s_pMemoryManager->showStatus();
		for (int i = 0; i < numRecorders; i++) {
			delete paRecorder[i];
		}
		Object::s_pMemoryManager->showStatus();
	}
};


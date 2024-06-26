#pragma once
#include "Object.h"

#include "Camera.h"
#include "Recorder.h"

	/**
   	*
   	* @brief 메인 클래스
   	* @date 2024-05-02
   	* @version 0.21
   	*
   	*/
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
	}
};
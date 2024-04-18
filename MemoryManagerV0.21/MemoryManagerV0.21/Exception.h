#pragma once

#include "Object.h"

class Exception: public Object
{
public:
	enum class ECode {
		eOutOfMemory,
		eLengthECode
	};

private:
	ECode eCode;
	char *pNameObject;
	char *pNameClass;

	char** pNameECode;

public:
	Exception(ECode eCode, const char* pNameObject, const char* pNameClass = "Exception") :
		eCode(eCode)
	{
		this->pNameECode = new char* [(int)ECode::eLengthECode];
		this->pNameECode[(int)ECode::eOutOfMemory] = strcpy("Out Of Memory");

		this->pNameObject = strcpy(pNameObject);
		this->pNameClass = strcpy(pNameClass);
	}
	virtual ~Exception() {
	}

	ECode getECode() { return this->eCode; }
	char* getNameObject() { return this->pNameObject; }
	char* getNameClass() { return this->pNameClass; }

	void println() {
		printf("Exception: %s(%s, %s)\n", pNameECode[(int)ECode::eOutOfMemory], pNameObject, pNameClass); }
};


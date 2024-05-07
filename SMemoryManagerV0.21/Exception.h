#pragma once

#include "Object.h"
#include <cstring>
#include <string>

class Exception : public Object {
public:
    enum class ECode {
        eOutOfMemory,
        eLengthECode
    };

private:
    ECode eCode;
    char* pNameObject;
    char* pNameClass;

public:
    Exception(ECode eCode, const char* pNameObject, const char* pNameClass = "Exception")
        : eCode(eCode), pNameObject(_strdup(pNameObject)), pNameClass(_strdup(pNameClass)) {}

    virtual ~Exception() {
        delete[] pNameObject;
        delete[] pNameClass;
    }

    ECode getECode() const { return eCode; }
    const char* getNameObject() const { return pNameObject; }
    const char* getNameClass() const { return pNameClass; }

    const char* getECodeAsString() const {
        switch (eCode) {
        case ECode::eOutOfMemory: return "Out Of Memory";
        default: return "Unknown Error";
        }
    }

    void println() {
        printf("Exception.h : %s(%s, %s)\n", getECodeAsString(), pNameObject, pNameClass);
    }
};
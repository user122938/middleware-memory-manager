#pragma once

#include "Object.h"
#include <cstring>
#include <string>

    /**
    *
    * @brief 예외 클래스
    * @details 예외 정보 저장 및 출력 클래스
    * @date 2024-05-19
    * @version 0.21
    *
    */
class Exception : public Object {
public:
    /**
    *
    * @brief 예외 코드 집합
    * @details 예외 종류를 모아놓은 상수 집합
    * @date 2024-05-19
    * @version 0.21
    *
    */
    enum class ECode {
        eOutOfMemory,
        eLengthECode
    };

private:
    ECode eCode;
    char* pNameObject;
    char* pNameClass;

public:
    /**
    *
    * @brief 예외 생성자
    * @details 
    * @param eCode 예외 코드
    * @param pNameObject 예외가 발생한 객체 이름
    * @param pNameClass ??? (기본값: "Exception")
    * @date 2024-05-19
    * @version 0.21
    *
    */
    Exception(ECode eCode, const char* pNameObject, const char* pNameClass = "Exception")
        : eCode(eCode), pNameObject(_strdup(pNameObject)), pNameClass(_strdup(pNameClass)) {}

    /**
    *
    * @brief 소멸자
    * @details 문자열 배열 삭제
    * @date 2024-05-19
    * @version 0.21
    *
    */
    virtual ~Exception() {
        delete[] pNameObject;
        delete[] pNameClass;
    }

    /**
    *
    * @brief 예외 코드 반환
    * @return 예외 코드
    * @date 2024-05-19
    * @version 0.21
    *
    */
    ECode getECode() const { return eCode; }

    /**
    *
    * @brief 오류가 발생한 객체 이름 반환
    * @return 객체 이름 문자열
    * @date 2024-05-19
    * @version 0.21
    *
    */
    const char* getNameObject() const { return pNameObject; }
    /**
    *
    * @brief 예외 클래스 이름 반환
    * @return 클래스 이름 문자열
    * @date 2024-05-19
    * @version 0.21
    *
    */
    const char* getNameClass() const { return pNameClass; }

    /**
    *
    * @brief 예외 코드를 문자열로 변환
    * @details 예외 코드를 switch문을 이용해 문자열로 변환
    * @return 예외 메시지 문자열
    * @date 2024-05-19
    * @version 0.21
    *
    */
    const char* getECodeAsString() const {
        switch (eCode) {
        case ECode::eOutOfMemory: return "Out Of Memory";
        default: return "Unknown Error";
        }
    }

    /**
    *
    * @brief 예외 정보를 콘솔에 출력
    * @date 2024-05-19
    * @version 0.21
    *
    */
    void println() {
        printf("Exception.h : %s(%s, %s)\n", getECodeAsString(), pNameObject, pNameClass);
    }
};
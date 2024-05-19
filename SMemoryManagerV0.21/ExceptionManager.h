#pragma once

#include "Exception.h"
#include <vector>
#include <iostream>

    /**
    *
    * @brief 예외처리 매니저 클래스
    * @details 예외를 배열에 저장하고 출력
    * @date 2024-05-19
    * @version 0.21
    *
    */
class ExceptionManager {
private:
    static std::vector<std::string> exceptionLogs;

public:
    /**
    *
    * @brief 예외를 배열에 저장 및 출력
    * @details 예외 객체의 정보를 문자열로 만들어 배열에 저장 및 콘솔에 출력
    * @param ex 예외 객체
    * @date 2024-05-19
    * @version 0.21
    *
    */
    static void logException(const Exception& ex) {
        std::string log = "ExceptionManager-Exception: " + std::string(ex.getECodeAsString()) +
            "(" + std::string(ex.getNameObject()) + ", " + std::string(ex.getNameClass()) + ")";
        exceptionLogs.push_back(log);
        std::cout << log << std::endl;
    }
    /**
    *
    * @brief 배열에 저장된 예외 출력
    * @details 배열에 저장된 예외를 하나씩 꺼내서 출력
    * @date 2024-05-19
    * @version 0.21
    *
    */
    static void printAllExceptions() {
        std::cout << "ExceptionManager-Logged Exceptions:" << std::endl;
        for (const auto& log : exceptionLogs) {
            std::cout << log << std::endl;
        }
    }
};


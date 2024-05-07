#pragma once

#include "Exception.h"
#include <vector>
#include <iostream>

class ExceptionManager {
private:
    static std::vector<std::string> exceptionLogs;

public:
    static void logException(const Exception& ex) {
        std::string log = "ExceptionManager-Exception: " + std::string(ex.getECodeAsString()) +
            "(" + std::string(ex.getNameObject()) + ", " + std::string(ex.getNameClass()) + ")";
        exceptionLogs.push_back(log);
        std::cout << log << std::endl;
    }

    static void printAllExceptions() {
        std::cout << "ExceptionManager-Logged Exceptions:" << std::endl;
        for (const auto& log : exceptionLogs) {
            std::cout << log << std::endl;
        }
    }
<<<<<<< HEAD:MemoryManagerV0.21/MemoryManagerV0.21/ExceptionManager.h
};
=======
};
>>>>>>> 844389d308651d6f3bd85d2c9b91026c12f3d45e:SMemoryManagerV0.21/ExceptionManager.h

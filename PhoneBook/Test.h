#ifndef TEST_
#define TEST_

#include <iostream>
#include <string>
#include "PresonalInfo.h"

class Test {
    public:
        int creatingPersonalInfo(std::string name, std::string other);
        int settingPersonalInfo(std::string name, std::string other);
        int comparisonPersonalInfo();
        int printingPI(std::string name, std::string other);
        int printingPI2(std::string name, std::string other);
};

#endif //TEST_

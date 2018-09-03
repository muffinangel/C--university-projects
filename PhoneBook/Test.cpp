#include "Test.h"
#include <assert.h>

int Test::creatingPersonalInfo(std::string name, std::string other) {
    PersonalInfo x(name, other);
    assert((x.getFullName() == name));
    assert((x.getAddress() == other));
    return 0;
}

int Test::settingPersonalInfo(std::string name, std::string other) {
    PersonalInfo x;
    x.setAddress(other);
    x.setFullName(name);
    assert((x.getFullName() == name));
    assert((x.getAddress() == other));
    return 0;
}

int Test::comparisonPersonalInfo() {
    PersonalInfo a ("Boryczko Alicja", "Nowoslaska 3/154");
    PersonalInfo b ("Boryczko Alicja", "Gornoslaska 3/154");
    PersonalInfo c ("Boryczko Karolina", "Nowoslaska 3/154");
    PersonalInfo d ("Zoryczko Karolina", "Nowoslaska 3/154");

    assert(a>b);
    assert(c>a);
    assert(d>c);
    assert(c>b);
    return 0;
}

int Test::printingPI(std::string name, std::string other) {
    PersonalInfo a ("Boryczko Alicja", "Nowoslaska 3/154");
    std::cout << a <<std::endl;
    return 0;
}

int Test::printingPI2(std::string name, std::string other) {
    return 0;
}

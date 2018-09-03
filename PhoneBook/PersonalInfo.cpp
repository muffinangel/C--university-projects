#include "PresonalInfo.h"

std::string PersonalInfo::getFullName() {
return fullName_;
}

std::string PersonalInfo::getAddress() {
return address_;
}

void PersonalInfo::setFullName(std::string name) {
    fullName_ = name;
}
void PersonalInfo::setAddress(std::string address) {
    address_ = address;
}

bool PersonalInfo::operator>(PersonalInfo x) {
    bool the_same = false;
    std::string str1 = this->fullName_;
    the_same = (str1 == x.getFullName());
    if(the_same) return this->address_ > x.getAddress();
    return this->fullName_ > x.getFullName();
}

bool PersonalInfo::operator==(PersonalInfo &x) {
    return (fullName_ == x.getFullName()) && (address_ == x.getAddress());
}

std::ostream & operator<<(std::ostream &s, PersonalInfo &x) {
    s << x.getFullName() << std::endl;
    s << x.getAddress() << std::endl;
    return s;
}

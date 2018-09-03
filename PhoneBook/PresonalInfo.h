#ifndef PERSONALINFO_
#define PERSONALINFO_

#include <iostream>
#include <string>

class PersonalInfo {
    private:
    std::string fullName_;
    std::string address_;
    public:
    PersonalInfo() {fullName_ = ""; address_ = "";};
    PersonalInfo(std::string name, std::string address): fullName_(name), address_(address) {};
    std::string getFullName();
    std::string getAddress();
    void setFullName(std::string name);
    void setAddress(std::string address);
    bool operator>(PersonalInfo x);
    bool operator==(PersonalInfo &x);

};

std::ostream & operator<<(std::ostream &s, PersonalInfo &x);

#endif //PERSONALINFO_

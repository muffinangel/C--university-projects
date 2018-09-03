#include "ClassCar.h"
int Car::uniqueNumber = 1;
const char* Car::conditionNames_[3] = {"onTheRoad", "readyToUse", "inService"};

void Car::setnSendings(unsigned int number) {
    nSendings_ = number;
}
int Car::getnSendings() {
    return nSendings_;
}
void Car::setMileage(unsigned int number) {
    mileage_ = number;
}
int Car::getMileage() {
    return mileage_;
}
int Car::getTankCapacity() {
    return tankCapacity_;
}
int Car::getCondition() {
    return condition_;
}
void Car::setCondition(Condition condition) {
    condition_ = condition;
}
void Car::setIsBroken(bool isBroken) {
    isBroken_ = isBroken;
}
bool Car::getIsBroken() {
    return isBroken_;
}
void Car::setNeedsRefueling(bool needsRefueling) {
    needsRefueling_ = needsRefueling;
}
bool Car::getNeedsRefueling() {
    return needsRefueling_;
}
int Car::getNr() {
    return nr_;
}
void Car::getInfo() {
    std::cout << "Car nr: " << nr_ << std::endl;
    std::cout << "Mileage: " << mileage_ << std::endl;
    std::cout << "Tank capacity: " << tankCapacity_ << std::endl;
    std::cout << "Nr of sendings: " << nSendings_ << std::endl;
    std::cout << "Is broken: " << (isBroken_ ? "Yes" : "No") << std::endl;
    std::cout << "Needs refueling: " << (needsRefueling_ ? "Yes" : "No") << std::endl;
    std::cout << "Current condition: " << conditionNames_[condition_] << std::endl;

}

int Car::operator==(Car x) {
    if(nr_ == x.nr_) return 1;
    return 0;
}

Car::Car(int nSendings, int mileage, int tankCapacity, Car::Condition condition, bool isBroken, bool needsRefueling) {
        nSendings_ = nSendings;
        mileage_ = mileage;
        tankCapacity_ = tankCapacity;
        condition_ = condition;
        isBroken_ = isBroken;
        needsRefueling_ = needsRefueling;
        nr_ = uniqueNumber++;
    }

Car::Car() {
       mileage_ =  nSendings_ = tankCapacity_ = 0;
       isBroken_ = needsRefueling_ = 0;
       condition_ = Car::readyToUse;
       nr_ = uniqueNumber++;
    }

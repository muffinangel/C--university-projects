#include <cstring>
#include <iostream>



class Car {
public:
    enum Condition {
        onTheRoad = 0,
        readyToUse = 1,
        inService = 2
    };

private:
    static int uniqueNumber;
    unsigned int nr_;
    unsigned int nSendings_;
    unsigned int mileage_;
    int tankCapacity_;
    Condition condition_;
    bool isBroken_;
    bool needsRefueling_;
    static const char* conditionNames_[3];

public:
    void setnSendings(unsigned int number);
    int getnSendings();
    void setMileage(unsigned int number);
    int getMileage();
    int getTankCapacity();
    int getCondition();
    void setCondition(Condition condition);
    void setIsBroken(bool isBroken);
    bool getIsBroken();
    void setNeedsRefueling(bool needsRefueling);
    bool getNeedsRefueling();
    int getNr();
    void getInfo();
    int operator==(Car x);

    Car(int nSendings, int mileage, int tankCapacity, Condition condition, bool isBroken = false, bool needsRefueling = false);

    Car();
};

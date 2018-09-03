#include "ClassCar.cpp"

class CarCompany {
public:
    typedef struct CarList{
        Car *car;
        CarList *next;
        CarList *prev;
    }CarList;

    CarCompany() {companyCars = NULL;}

    void printAllCars();
    void printBrokenCars();
    void printCars(Car::Condition condition);
    void printCarsToRefuel();

    void operator+(Car *x);
    void operator-(CarList *x);
    CarList* findCar(int nr);

    void sendCaronTheRoad(Car *x){x->setCondition(Car::onTheRoad);}
    void sendCarToTheService(Car *x) {x->setCondition(Car::inService);}
    void getCarFromTheService(Car *x) {x->setCondition(Car::readyToUse); x->setIsBroken(false);}
    void getCarFromTheRoad(Car *x) {x->setCondition(Car::readyToUse);}
    void RefuelaCar(Car *x) {x->setNeedsRefueling(false);}
    void changeRefuel(Car *x) {x->setNeedsRefueling(!(x->getNeedsRefueling()));}
    void changeNSendings(Car *x, int nr) {x->setnSendings(nr);}
    void changeMileage(Car *x, int nr) {x->setMileage(nr);}

    void ClearCarCompany();


private:
    CarList *companyCars;
};


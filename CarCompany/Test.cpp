#include "Test.h"
#include <assert.h>

void CarCompanyTests::Test1() {
    Car car;
    car.setMileage(12);
    assert (car.getMileage() == 12);
}

void CarCompanyTests::Test2() {
    CarCompany x;
    Car car1;
    x + &car1;
    assert(x.findCar(car1.getNr()) != NULL);
}

void CarCompanyTests::Test3() {
    CarCompany x;
    Car car1;
    x + &car1;
    assert(x.findCar(car1.getNr()) != NULL);
}

void CarCompanyTests::Test4() {
    CarCompany x;
    Car car1;
    x + &car1;
    x.changeNSendings(x.findCar(car1.getNr())->car, 120);
    assert(x.findCar(car1.getNr())->car->getnSendings() == 120);
}

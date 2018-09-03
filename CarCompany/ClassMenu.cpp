#include "ClassMenu.h"
#include <stdio.h>
#include <cstdlib>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

void Menu::printMainMenu() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to show cars" << std::endl;
    std::cout << "2 to create new car" << std::endl;
    std::cout << "3 to delete a car" << std::endl;
    std::cout << "4 to change a car" << std::endl;
    std::cout << "5 to send a car on the road" << std::endl;
    std::cout << "6 to send a car to service" << std::endl;
    std::cout << "7 to get a car back from the service" << std::endl;
    std::cout << "8 to get a car back from the road"<< std::endl;
    std::cout << "9 to refuel a car" << std::endl;
    std::cout << "0 to exit" << std::endl;
}

void Menu::printInfoMenu() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to print information about all cars" << std::endl;
    std::cout << "2 to find broken cars" << std::endl;
    std::cout << "3 to find cars on the road" << std::endl;
    std::cout << "4 to find cars in service" << std::endl;
    std::cout << "5 to find cars that are ready to use" << std::endl;
    std::cout << "6 to find cars that needs refuelling" << std::endl;
    std::cout << "0 to return to main menu" << std::endl;
}

void Menu::printChangeMenu() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to change number of packages" << std::endl;
    std::cout << "2 to change mileage" << std::endl;
    std::cout << "3 to change need to refuel a car" << std::endl;
    std::cout << "4 to get a car from the service" << std::endl;
    std::cout << "0 to return to main menu" << std::endl;
}

// gets an usigned int from the user, if error return -1
int Menu::enterNr() {
    int i = 0;
     char n[30];
     int finalnumber = 0;
     int multiplier = 1;
     fgets(n, 30, stdin);
     for(i = 0; i<30; i++) {
        if(n[i] == '\n') break;
        else if(n[i] < '0' || n[i] >'9') return -1;
     }
     for(i = i-1; i>=0; i--) {
        finalnumber += (n[i] - '0')*multiplier;
        multiplier *= 10;
     }
     return finalnumber;
}

//Waits for user to press ENTER
void Menu::pressEnter() {
    int c;
    std::cout << "Press enter to continue ";
    c = getchar();
    while(c != '\n') c = getchar();
}

//return first acceptable char from tab that the user enters
int Menu::returnChar(char *tab, int maximum) {
    int i;
    int c;
    while(1) {
        c = getchar();
        for(i = 0; i < maximum; i++) if(tab[i] == c) return c;
    }
}

//gets informations from the user to create a new car - if an error occurred, the creation is stopped
void Menu::createNewCar() {
    int mileage, nSend, tankCapacity, nofCondition;
    std::cout << "Enter mileage: "; mileage = enterNr(); std::system(CLEAR);
    std::cout << "Enter number of packages in this car: "; nSend = enterNr(); std::system(CLEAR);
    std::cout << "Enter tank capacity: "; tankCapacity = enterNr(); std::system(CLEAR);
    std::cout << "Enter car's condition: \n0) on the road\n1) ready to use\n2) in the service\n"; nofCondition = enterNr(); std::system(CLEAR);
    if(mileage == -1 || nSend == -1 || tankCapacity == -1 || nofCondition < 0 || nofCondition > 2) {
        std::cout << "There was an error. Creating new car was stopped" << std::endl;
        Menu::pressEnter();
        std::system(CLEAR);
        return;
    }
    Car::Condition condition = (Car::Condition)nofCondition;
    Car *wsk = new Car(nSend, mileage, tankCapacity, condition);
    current_ + wsk;
    std::cout << "Car created succesfully" << std::endl;
    Menu::pressEnter();
    std::system(CLEAR);
}

void Menu::SelectMainMenu() {
    int user_char;
    char tab[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    int lenght = 10;
    int carNr;
    CarCompany::CarList *x = NULL;

    while(1) {
        std::system(CLEAR);
        Menu::printMainMenu();
        user_char = Menu::returnChar(tab, lenght);
        getchar(); // clean '\n' from the buffer
        x = NULL;
        std::system(CLEAR);
        switch(user_char) {
            case '1':
                Menu::SelectInfoMenu();
                break;
            case '2':
                Menu::createNewCar();
                break;
            case '3':
               if( (x = Menu::getaCarNr()) ) { current_ - x; }
                break;
            case '4':
                Menu::SelectChangeMenu(Menu::getNrWithComunicat("Please enter car number:"));
                break;
            case '5':
                if( x = Menu::getaCarNr()) { current_.sendCaronTheRoad((x->car)); }
                break;
            case '6':
               if( x = Menu::getaCarNr())
                    { if(x->car->getIsBroken() == true) current_.sendCarToTheService((x->car));
                        else std::cout << "Car is not broken. There is no need to send it to the service" << std::endl;
                     }
                break;
            case '7':
                if( x = Menu::getaCarNr())
                {
                    if(x->car->getCondition() != Car::inService) current_.getCarFromTheService((x->car));
                    else std::cout << "Car is not in the service" << std::endl;
                }
                break;
            case '8':
               if( x = Menu::getaCarNr()) {
                   if(x->car->getCondition() != Car::onTheRoad) current_.getCarFromTheRoad((x->car));
                   else std::cout << "Car is not on the road" << std::endl;
                }
                break;
            case '9':
               if( x = Menu::getaCarNr()) {
                  current_.RefuelaCar((x->car));
                }
                break;
            case '0':
                //free allocated memory
                current_.ClearCarCompany();
                return;
                break;
        }
        std::system(CLEAR);
    }
}

void Menu::SelectInfoMenu() {
    int user_char;
    char tab[] = {'1', '2', '3', '4', '5', '6', '0'};
    int lenght = 7;
    std::system(CLEAR);
    Menu::printInfoMenu();
    user_char = Menu::returnChar(tab, lenght);
    getchar(); // clean '\n' from the buffer
    std::system(CLEAR);

    switch(user_char) {
        case '1':
            current_.printAllCars();
            break;
        case '2':
            current_.printBrokenCars();
            break;
        case '3':
            current_.printCars(Car::onTheRoad);
            break;
        case '4':
            current_.printCars(Car::inService);
            break;
        case '5':
            current_.printCars(Car::readyToUse);
            break;
        case '6':
            current_.printCarsToRefuel();
            break;
        case '0':
            return;
    }
    Menu::pressEnter();
}

void Menu::SelectChangeMenu(int carNr) {
    if(carNr < 0) {
        std::cout << "There was en error in entering a car number" << std::endl;
        pressEnter();
        return;
    }
    CarCompany::CarList *temp = current_.findCar(carNr);
    if(!temp) {
        std::cout << "A car with a nr " << carNr << "doesn't exist" << std::endl;
        pressEnter();
        return;
    }
    Car changed = *(temp->car);

    std::cout << "A car to change:\n " << std::endl;
    changed.getInfo();
    pressEnter();

    int user_char, nr;
    char tab[] = {'1', '2', '3', '4', '0'};
    int lenght = 5;
    std::system(CLEAR);
    Menu::printChangeMenu();
    user_char = Menu::returnChar(tab, lenght);
    getchar(); // clean '\n' from the buffer
    std::system(CLEAR);

    switch(user_char) {
        case '1':
            nr = getNrWithComunicat("Please enter a number of packages:");
            if(nr < 0) return;
            current_.changeNSendings(temp->car, nr);
            break;
        case '2':
            nr = getNrWithComunicat("Please enter a mileage number:");
            if(nr < 0) return;
            current_.changeMileage(temp->car, nr);
            break;
        case '3':
            current_.RefuelaCar(temp->car);
            break;
        case '4':
            if(changed.getCondition() != Car::inService) return;
            current_.getCarFromTheService(temp->car);
            break;
        case '0':
            return;
    }
    Menu::pressEnter();
}

int Menu::getNrWithComunicat(const char *s) {
    std::system(CLEAR);
    int aNr;
    std::cout << s;
    aNr = enterNr();
    std::system(CLEAR);
    return aNr;
}

CarCompany::CarList* Menu::getaCarNr() {
    int carNr = getNrWithComunicat("Please enter a car's number:");
    CarCompany::CarList *x = current_.findCar(carNr);
    if(!x) {
        std::cout << "There was an error or a car " << carNr << "doesn't exist" << std::endl;
        pressEnter();
        x = NULL;
    }
    return x;
}

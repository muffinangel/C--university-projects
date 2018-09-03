#include "ClassMenu.cpp"
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    CarCompany company;
    Menu menu(company);
    menu.SelectMainMenu();
    return 0;
}

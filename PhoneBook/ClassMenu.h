#ifndef MENU_
#define MENU_

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <cstdlib>
#include "MyMap.h"
#include "Phonebook.h"


class Menu {
public:
    void printMainMenu();
    int enterNr();
    void pressEnter();
    void createNewPhoneNr();
    void selectMainMenu();
    int returnChar(char *tab, int maximum);
    int getNrWithComunicat(const char *s);
    void viewPhoneNumbers();
    void deletePhoneNumber();
    void editPhoneNumber();
    int getLenght(int i);
    PersonalInfo gettingData(const char *add = "");
    void getFromFile();
    void saveInFile();

private:
    Phonebook phonebook_;

};
#endif // MENU_

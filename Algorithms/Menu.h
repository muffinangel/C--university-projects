#ifndef MENU_
#define MENU_

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define VIGENERE 1
#define CEZAR 2
#define FENCE 3
#define RSACODE 4


#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include "ALgorithmsAgregator.h"

class Menu {
public:
    Menu () {
      whichAlgoritm_ = 0;
    }
    void setWhichAlgorithm(int i) {
        whichAlgoritm_ = i;
    }
    int getWhichAlgorithm() {
        return whichAlgoritm_;
    }
    void printMainMenu();
    int enterNr();
    void pressEnter();

    void selectMainMenu();
    int returnChar(char *tab, int maximum);
    int getNrWithComunicat(const char *s);

    void selectAlgorithm();
    void printPossibleAlgorithms();
    void viewKey();
    void changeKey();
    void encryptMessage();
    void decryptMessage();
    std::string getFileName(const char *add);
    void printInfo();

private:
    int whichAlgoritm_;
    AlgorithmsAgregator agregator_;

};
#endif // MENU_

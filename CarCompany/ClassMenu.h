#include "ClassCarCompany.cpp"

class Menu {
public:
    Menu(CarCompany x) { current_ = x;}
    void printMainMenu();
    void printInfoMenu();
    void printChangeMenu();
    int enterNr();
    void pressEnter();
    void createNewCar();
    void SelectMainMenu();
    void SelectInfoMenu();
    void SelectChangeMenu(int carNr);
    int returnChar(char *tab, int maximum);
    int getNrWithComunicat(const char *s);
    CarCompany::CarList *getaCarNr();

private:
    CarCompany current_;

};

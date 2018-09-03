#include "ClassMenu.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>

void Menu::printMainMenu() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to view phone book" << std::endl;
    std::cout << "2 to add new phone nr" << std::endl;
    std::cout << "3 to delete phone nr" << std::endl;
    std::cout << "4 to change phone nr" << std::endl;
    std::cout << "5 to get a phonebook from file" << std::endl;
    std::cout << "6 to save a phonebook" << std::endl;
    std::cout << "0 to exit" << std::endl;
}

// gets an usigned int from the user, if error returns -1, if nothing is entered returns 0
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

PersonalInfo Menu::gettingData(const char *add) {
  char fullName[200];
  char address[200];
  std::cout << "Please enter fullname " << add;
  fgets(fullName, 119, stdin);
  std::system(CLEAR);
  std::cout << "Please enter address: " << add;
  fgets(address, 119, stdin);
  std::system(CLEAR);
  PersonalInfo x(fullName, address);
  return x;
}

//gets informations from the user to create a new car - if an error occurred, the creation is stopped
void Menu::createNewPhoneNr() {
  PersonalInfo x = gettingData("");
  int phonenr = getNrWithComunicat("Please enter phone number:");
  //for checking phone number length
  int length = getLenght(phonenr);
  if(phonenr == 0 || length != 9) {
    std::system(CLEAR);
    std::cout << "Phone number must have 9 digits" << std::endl;
    pressEnter();
    return;
  }
  //all the data now is correct

  Node<PersonalInfo, int> *y = new Node<PersonalInfo, int>(x, phonenr);
  Node<PersonalInfo, int> *found = phonebook_.findNode(phonebook_.getHead(), x);
  if(found) {
    std::cout << "This data has been added earlier" << std::endl;
    pressEnter();
    return;
  }
  //data can be added to phonebook
  phonebook_.insertNode(y);
}

void Menu::viewPhoneNumbers() {
  if(phonebook_.getHead() == NULL) {
    std::cout << "There is no data" << std::endl;
    return;
  }
  phonebook_.inorder(std::cout, phonebook_.getHead());
  pressEnter();
}

void Menu::deletePhoneNumber() {
  PersonalInfo x = gettingData("");
  Node<PersonalInfo, int> *found = phonebook_.findNode(phonebook_.getHead(), x);
  if(!found) {
    std::cout << "This data doessn't exist and can't be delated" << std::endl;
    pressEnter();
    return;
  }
  // deleting
  phonebook_.setHead(phonebook_.deleteNode(phonebook_.getHead(), x));
  std::cout << "Data deleted succesfully" << std::endl;
  pressEnter();
}

void Menu::editPhoneNumber() {
  PersonalInfo x = gettingData();
  Node<PersonalInfo, int> *found = phonebook_.findNode(phonebook_.getHead(), x);
  if(!found) {
    std::cout << "This data doessn't exist and can't be changed" << std::endl;
    pressEnter();
    return;
  }
  PersonalInfo y = gettingData("or ENTER if no change is needed: ");
  int  phonenr = getNrWithComunicat("Please enter phone number or ENTER if no change is needed:");
  std::system(CLEAR);
  if((phonenr == 0 || getLenght(phonenr)!= 9) && y.getFullName()[0] == '\n' && y.getAddress()[0] == '\n') return;
  //something is changed
  if(y.getFullName()[0] == '\n' && y.getAddress()[0] == '\n' && phonenr != 0 && getLenght(phonenr) == 9) {
    //only phone number is changed
    found->setContent(phonenr);
    return;
  }
  std::string fN = y.getFullName();
  std::string aD = y.getAddress();
  if(fN[0] == '\n') fN = x.getFullName();
  if(aD[0] == '\n') aD = x.getAddress();
  if(phonenr == 0 || getLenght(phonenr)!= 9) phonenr = found->getContent();
  PersonalInfo a(fN, aD);
  Node<PersonalInfo, int> *newfound = phonebook_.findNode(phonebook_.getHead(), a);
  if(newfound) {
    std::cout << "This data exist and can't be doubled" << std::endl;
    pressEnter();
    return;
  }
  newfound = new Node<PersonalInfo, int>(a, phonenr);
  // deleting old version
  phonebook_.setHead(phonebook_.deleteNode(phonebook_.getHead(), x));
  // adding new version
  phonebook_.insertNode(newfound);

}



void Menu::selectMainMenu() {
    int user_char;
    char tab[] = {'1', '2', '3', '4', '5', '6', '0'};
    int lenght = 7;

    while(1) {
        std::system(CLEAR);
        Menu::printMainMenu();
        user_char = Menu::returnChar(tab, lenght);
        getchar(); // clean '\n' from the buffer
        std::system(CLEAR);
        switch(user_char) {
            case '1':
                Menu::viewPhoneNumbers();
                break;
            case '2':
                Menu::createNewPhoneNr();
                break;
            case '3':
                Menu::deletePhoneNumber();
                break;
            case '4':
                Menu::editPhoneNumber();
                break;
            case '5':
                Menu::getFromFile();
                break;
            case '6':
                Menu::saveInFile();
                break;
            case '0':
                phonebook_.freeMemory(phonebook_.getHead());
                return;
                break;
        }
        pressEnter();
    }
}


int Menu::getNrWithComunicat(const char *s) {
    std::system(CLEAR);
    int aNr;
    std::cout << s;
    aNr = enterNr();
    std::system(CLEAR);
    return aNr;
}

void Menu::getFromFile() {
    std::string file;
    std::ifstream myfile;
    int result;

    std::cout << "Enter filename: ";
    std::cin >> file;

    myfile.open(file.c_str());
    if (myfile.is_open()) {
        result = phonebook_.readFile(myfile);
         myfile.close();
         if(result) std::cout << "An error occured during reading file" << std::endl;
         else std::cout << "Phonebook read successfully" << std::endl;
    }
    else std::cout << "This file doesn't exist or can't be opened" << std::endl;
    pressEnter();
}

void Menu::saveInFile() {
    std::string file;
    std::ofstream myfile;

    std::cout << "Enter filename: ";
    std::cin >> file;

    myfile.open(file.c_str());
    if (myfile.is_open()) {
        phonebook_.fillFile(myfile, phonebook_.getHead());
        std::cout << "File saved successfully" << std::endl;
    }
    else std::cout << "This file doesn't exist or can't be opened" << std::endl;
    pressEnter();
}

int Menu::getLenght(int i) {
    // the "length" of 0 is 1:
    int len = 1;
    if (i > 0) {
        for (len = 0; i > 0; len++) i = i/10;
    }
    return len;
}



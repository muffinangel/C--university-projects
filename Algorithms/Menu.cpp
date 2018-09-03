#include "Menu.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

void Menu::printMainMenu() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to select Algorithm" << std::endl;
    std::cout << "2 to view key" << std::endl;
    std::cout << "3 to change key" << std::endl;
    std::cout << "4 to encrypt a message" << std::endl;
    std::cout << "5 to decrypt a message" << std::endl;
    std::cout << "6 to view info about algorithms" << std::endl;
    std::cout << "0 to exit" << std::endl;
}

void Menu::selectAlgorithm() {
    char tab[] = {'1', '2', '3', '4'};
    int lenght = 4;

    std::system(CLEAR);
    Menu::printPossibleAlgorithms();
    int user_char = Menu::returnChar(tab, lenght);
    getchar(); // clean '\n' from the buffer
    std::system(CLEAR);
    switch(user_char) {
        case '1':
            setWhichAlgorithm(1);
            agregator_.setAlgorithm(Vigenere::getSingleton());
            break;
        case '2':
            setWhichAlgorithm(2);
            agregator_.setAlgorithm(Cezar::getSingleton());
            break;
        case '3':
            setWhichAlgorithm(3);
            agregator_.setAlgorithm(FenceCode::getSingleton());
            break;
        case '4':
            setWhichAlgorithm(4);
            agregator_.setAlgorithm(RSA::getSingleton());
            break;
    }
    std::cout << "Algorithm selected" << std::endl;
    pressEnter();
}

void Menu::printPossibleAlgorithms() {
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to select Vigenere's algorithms" << std::endl;
    std::cout << "2 to select Caesar shiffer" << std::endl;
    std::cout << "3 to select Fence code" << std::endl;
    std::cout << "4 to select RSA" << std::endl;
}

void Menu::printInfo() {
    std::cout << "VIGENERE CIPHER" << std::endl;
    std::cout << "The Vigenere cipher is a method of encrypting alphabetic text by using a series of interwoven Caesar ciphers based on the letters of a keyword. " << std::endl;
    std::cout << "It is a form of polyalphabetic substitution." << std::endl << std::endl;

    std::cout << "CAESAR CIPHER" << std::endl;
    std::cout << "It is a type of substitution cipher in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet. " << std::endl;
    std::cout << "For example, with a left shift of 3, D would be replaced by A, E would become B, and so on." << std::endl << std::endl;


    std::cout << "FENCE CODE" << std::endl;
    std::cout << "Letters are arranged in the shape of a fence and then read line by line" << std::endl << std::endl;

    std::cout << "RSA" << std::endl;
    std::cout << "RSA is one of the first practical public-key cryptosystems and is widely used for secure data transmission. " << std::endl;
    std::cout << "In such a cryptosystem, the encryption key is public and differs from the decryption key which is kept secret." << std::endl << std::endl;
}

void Menu::viewKey() {
    if(!agregator_.getAlgorithm()) {
        std::cout << "None algoritmh is selected!" << std::endl;
        pressEnter();
        return;
    }
    std::string key = agregator_.getAlgorithm()->getKey();
    if(getWhichAlgorithm() == RSACODE) std::cout << "(public / mod / private)" << std::endl;
    std::cout << "Key is " << key << std::endl;
    pressEnter();
}

void Menu::changeKey() {
    if(!agregator_.getAlgorithm()) {
        std::cout << "None algoritmh is selected!" << std::endl;
        pressEnter();
        return;
    }
    if(getWhichAlgorithm() == RSACODE) {
        agregator_.setAlgorithm(RSA::getSingleton());
        std::cout << "Key is already generated" << std::endl;
        return;
    }
    std::cout << "Enter new key :";
    int Ckey = -1;
    std::string Vkey = "";
    if(getWhichAlgorithm() == CEZAR || getWhichAlgorithm() == FENCE) {
      std::cout << "a number: ";
      if(getWhichAlgorithm() == CEZAR) std::cout << "<0; 25>";
      Ckey = enterNr();
      if(Ckey == 0) {
        std::cout << "0 will be the key" << std::endl;
        pressEnter();
      }

    std::stringstream ss;
    ss << Ckey;
    std::string sKey = ss.str();
    agregator_.getAlgorithm()->setKey(sKey);
    }
    else if(getWhichAlgorithm() == VIGENERE) {
      std::cout << "(only letters)";
      std::cin >> Vkey;
      bool contains_non_alpha
        = Vkey.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPRSTUWXYZ") != std::string::npos;
        if(contains_non_alpha) {
            std::cout << "Key is invalid" << std::endl;
            pressEnter();
            return;
        }
        agregator_.getAlgorithm()->setKey(Vkey);
    }
}

std::string Menu::getFileName(const char *add) {
    std::string file;
    std::cout << add;
    std::cin >> file;
    return file;
}

void Menu::encryptMessage() {
    std::ifstream imyfile;
    imyfile.open(getFileName("Enter filename to get message to encrypt: ").c_str());
    if (!imyfile.is_open()) {
        std::cout << "File can't be opened" << std::endl;
        pressEnter();
        return;
    }

    std::ofstream omyfile;
    omyfile.open(getFileName("Enter filename to write encrypted message: ").c_str());
    if (!omyfile.is_open()) {
        std::cout << "File can't be opened" << std::endl;
        pressEnter();
        imyfile.close();
        return;
    }
    int result = agregator_.encrypt(imyfile, omyfile);
    if(result) std::cout << "None algorithm was selected" << std::endl;

    imyfile.close();
    omyfile.close();
}

void Menu::decryptMessage() {
    std::ifstream imyfile;
    imyfile.open(getFileName("Enter filename to get message to decrypt: ").c_str());
    if (!imyfile.is_open()) {
        std::cout << "File can't be opened" << std::endl;
        pressEnter();
        return;
    }

    std::ofstream omyfile;
    omyfile.open(getFileName("Enter filename to write decrypted message: ").c_str());
    if (!omyfile.is_open()) {
        std::cout << "File can't be opened" << std::endl;
        pressEnter();
        imyfile.close();
        return;
    }

    int result = agregator_.decrypt(imyfile, omyfile);
    if(result) std::cout << "None algorithm was selected" << std::endl;

    imyfile.close();
    omyfile.close();
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
                selectAlgorithm();
                break;
            case '2':
                viewKey();
                break;
            case '3':
                changeKey();
                break;
            case '4':
                encryptMessage();
                break;
            case '5':
                decryptMessage();
                break;
            case '6':
                printInfo();
                break;
            case '0':
                return;
                break;
        }
        pressEnter();
    }
}





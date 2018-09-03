#ifndef VIGENERE_
#define VIGENERE_

#include "Algorithm.h"
#include <cstring>
#include <iostream>
#include <string>
#include <cmath>

class Vigenere :public Algorithm {
    public:
        virtual int encrypt(std::ifstream &iffile, std::ofstream &offile);
        virtual int decrypt(std::ifstream &iffile, std::ofstream &offile);
        std::string getKey() {
            return key_;
        }
        void setKey(std::string key) {
            key_ = key;
        }
        static Algorithm * getSingleton() {
            static Vigenere s;
            return &s;
        }
    private:
        Vigenere ()  {};
        Vigenere(Vigenere &c) {
            std::memcpy(c.ASCIItable_, ASCIItable_, 200);
            key_ = c.key_;
        }
        void setASCIItable();
        int ASCIItable_[200];
};

#endif // VIGENERE_

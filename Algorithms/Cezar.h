#ifndef CEZAR_
#define CEZAR_

#include "Algorithm.h"
#include <iostream>
#include <string>
#include <cmath>

class Cezar : public Algorithm {
    public:
    virtual int encrypt(std::ifstream &iffile, std::ofstream &offile);
    virtual int decrypt(std::ifstream &iffile, std::ofstream &offile);
    static Algorithm * getSingleton() {
        static Cezar s;
        return &s;
    }
    private:
    Cezar (): intkey_(0) {};
    Cezar (Cezar &c) {
        intkey_ = c.intkey_;
        key_ = c.key_;
    }
    int intkey_;
    void checkKey();
};

#endif // CEZAR_

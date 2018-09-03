#ifndef FENCE_
#define FENCE_

#include "Algorithm.h"
#include <iostream>
#include <string>
#include <cmath>

class FenceCode :public Algorithm {
    public:
    virtual int encrypt(std::ifstream &iffile, std::ofstream &offile);
    virtual int decrypt(std::ifstream &iffile, std::ofstream &offile);
    static Algorithm * getSingleton() {
        static FenceCode s;
        return &s;
    }
    private:
    FenceCode (): intkey_(0) {};
    FenceCode (FenceCode &c) {
        intkey_ = c.intkey_;
        key_ = c.key_;
    }
    int intkey_;
};

#endif // FENCE_


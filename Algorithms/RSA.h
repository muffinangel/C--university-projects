#ifndef RSA_
#define RSA_

#include "Algorithm.h"
#include <cwchar>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

class RSA : public Algorithm {
    public:
    virtual int encrypt(std::ifstream &iffile, std::ofstream &offile);
    virtual int decrypt(std::ifstream &iffile, std::ofstream &offile);
    static Algorithm * getSingleton() {
        static RSA s;
        return &s;
    }
    void generateKeys();


    private:
    int NWD(int a, int n);
    int modInverse(int a, int n);
    int modPower(int a, int w, int n);
    void setKeyInfo() {
        std::stringstream ss;
        ss << publicKey_; ss << " "; ss << mod_; ss << " "; ss << privateKey_;
        key_= ss.str();
    }
    RSA () {generateKeys();};
    RSA (RSA &c) {
        key_ = c.key_;
        mod_ = c.mod_;
        privateKey_ = c.privateKey_;
        publicKey_ = c.publicKey_;
    }
    int privateKey_;
    int publicKey_;
    int mod_;
    static const int prime[10];
};


#endif //RSA_

#ifndef ALGORITHMSAGREGATOR_
#define ALGORITHMSAGREGATOR_


#include "Algorithm.h"
#include "Vigenere.h"
#include "Cezar.h"
#include "FenceCode.h"
#include "RSA.h"
#include <iostream>
#include <string>
#include <cmath>

class AlgorithmsAgregator {
private:
    Algorithm *ptr_;
public:
    void setAlgorithm(Algorithm *ptr) {
        ptr_ = ptr;
    }
    int encrypt(std::ifstream &iffile, std::ofstream &offile) {
        if(ptr_ == NULL) return 1;
        ptr_->encrypt(iffile, offile); return 0;
    }
    int decrypt(std::ifstream &iffile, std::ofstream &offile) {
        if(ptr_ == NULL) return 1;
        ptr_->decrypt(iffile, offile); return 0;
    }
    Algorithm *getAlgorithm() {
        return ptr_;
    }
    AlgorithmsAgregator () {
        ptr_ = NULL;
    }
};

#endif // ALGORITHMSAGREGATOR_

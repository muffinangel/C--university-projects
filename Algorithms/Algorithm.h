#ifndef ALGORITHM_
#define ALGORITHM_

#include <fstream>
#include <cstdlib>


class Algorithm {
    public:
        virtual int encrypt(std::ifstream &iffile, std::ofstream &offile) = 0;
        virtual int decrypt(std::ifstream &iffile, std::ofstream &offile) = 0;
        std::string getKey() {
            return key_;
        }
        void setKey(std::string key) {
            key_ = key;
        }
    protected:
    std::string key_;

};

#endif // ALGORITHM_

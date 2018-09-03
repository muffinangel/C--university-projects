#include "Cezar.h"

int Cezar::encrypt(std::ifstream &iffile, std::ofstream &offile) {
    intkey_ = atoi(getKey().c_str());
    checkKey();
    int shift = intkey_;
    int ch; //from file
    while ( (ch = iffile.get()) != EOF ) {
        if ((ch>=65)&&(ch<=90)) {
            ch-=65;
            ch+=shift;
            ch=fmod(ch,26);
            ch+=65;
        }
        else if ((ch>=97)&&(ch<=122)) {
            ch-=97;
            ch+=shift;
            ch=fmod(ch,26);
            ch+=97;
        }
        else if ((ch>=48)&&(ch<=57)) {
        ch-=48;
        ch+=shift;
        ch=fmod(ch,10);
        ch+=48;
        }
        offile.put(ch);
    }
    return 0;
}
int Cezar::decrypt(std::ifstream &iffile, std::ofstream &offile) {
    intkey_ = atoi(getKey().c_str());
    checkKey();
    int shift = intkey_;
    int ch; //from file
    while ( (ch = iffile.get()) != EOF ) {
            if ((ch>=65)&&(ch<=90)) {
                ch-=65;
                ch-=shift;
                if(ch < 0) ch=26-fabs(ch);
                ch+=65;
            }
            else if ((ch>=97)&&(ch<=122)) {
                ch-=97;
                ch-=shift;
                if(ch < 0) ch=26-fabs(ch);
                ch+=97;
            }
            else if ((ch>=48)&&(ch<=57)) {
            ch-=48;
            if(shift >  10) {
                if(shift <= 20 ) ch +=10;
                else ch += 20;
            }
            ch -= shift;
            if(ch < 0) ch = 10 - fabs(ch);
            ch += 48;
            }
            offile.put(ch);
    }

    return 0;
}

void Cezar::checkKey() {
    int n = intkey_;
    if( n >= 0 && n <= 25) return;
    if(n < 0) n *= (-1);
    n = n % 26;
    intkey_ = n;

}

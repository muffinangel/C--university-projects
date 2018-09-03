#include "RSA.h"
#include "Menu.h"
const int RSA::prime[10] = {11,13,17,19,23,29,31,37};

int RSA::encrypt(std::ifstream &iffile, std::ofstream &offile) {
    int ch1;
    Menu menu;
    while ( (ch1 = iffile.get()) != EOF) {
        int enc = modPower(publicKey_, ch1, mod_);
        offile.put(enc);
    }
    menu.pressEnter();
    return 0;
}

int RSA::decrypt(std::ifstream &iffile, std::ofstream &offile) {
    int ch1;
    Menu menu;
    while ( (ch1 = iffile.get()) != EOF ) {
        int enc = modPower(privateKey_, ch1, mod_);
        offile.put(enc);
    }
    menu.pressEnter();
    return 0;
}


int RSA::modPower(int a, int w, int n) {
    int res = 0;
    long int pocz = w;
    int i;
    for( i = 1; i < a; i++) {
        pocz *= w;
        res = pocz % n;
        pocz = res;
    }
    return res;
}
void RSA::generateKeys() {
  int p,q,phi,n,e,d;

// generating 2 different prime nr
  do
  {
    p = prime[rand() % 10];
    q = prime[rand() % 10];
  } while (p == q);

  phi = (p - 1) * (q - 1);
  n   = p * q;

// wyznaczamy wyk³adniki e i d

    for(e = 3; RSA::NWD(e,phi) != 1; e += 2);
    d = RSA::modInverse(e,phi);

    publicKey_ = e;
    mod_ = n;
    privateKey_ = d;
    setKeyInfo();
}



int RSA::NWD(int a, int b) {
    int t;
    while(b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    };
    return a;
}

int RSA::modInverse(int a, int n) {
  int a0,n0,p0,p1,q,r,t;

  p0 = 0; p1 = 1; a0 = a; n0 = n;
  q  = n0 / a0;
  r  = n0 % a0;
  while(r > 0)
  {
    t = p0 - q * p1;
    if(t >= 0)
      t = t % n;
    else
      t = n - ((-t) % n);
    p0 = p1; p1 = t;
    n0 = a0; a0 = r;
    q  = n0 / a0;
    r  = n0 % a0;
  }
  return p1;
}

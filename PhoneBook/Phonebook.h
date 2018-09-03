#ifndef PHONEBOOK_
#define PHONEBOOK_

#include <fstream>
#include "MyMap.h"
#include <cstdlib>

class Phonebook : public MyMap<PersonalInfo, int> {
    public:
        std::ostream & inorder(std::ostream &s, Node<PersonalInfo, int> *root);
        void fillFile(std::ofstream &file, Node<PersonalInfo, int> *root);
        int readFile(std::ifstream &file);
        int getLenght(int i);
};


#endif

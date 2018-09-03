#include "Phonebook.h"

std::ostream & Phonebook::inorder(std::ostream &s, Node<PersonalInfo, int> *root){
    if (root != NULL){
        inorder(s, root->getLeft());
        PersonalInfo a = root->getKey();
        s << a.getFullName();
        s << a.getAddress();
        s << root->getContent() << std::endl << std::endl;
        inorder(s, root->getRight());
    }
    return s;
}

void Phonebook::fillFile(std::ofstream &file, Node<PersonalInfo, int>* root) {
    if(root) {
        file << root->getKey().getFullName();
        file << root->getKey().getAddress();
        file << root->getContent();
        file << std::endl;
        fillFile(file, root->getLeft());
        fillFile(file, root->getRight());
    }
}
int Phonebook::readFile(std::ifstream &file) {
    std::string line;
    std::string fullName;
    std::string address;
    int phoneNr;
    int i = 0;
    while ( getline (file,line) ) {
        if( i == 0 ) fullName = line + '\n';
        if( i == 1 ) address = line + '\n';
        if( i == 2 ){
            phoneNr = std::atoi(line.c_str());
            if(phoneNr <= 0 || getLenght(phoneNr) != 9) return 1; //error
            PersonalInfo x(fullName, address);

            Node<PersonalInfo, int> *found = findNode(getHead(), x);
            if(!found) {
                Node<PersonalInfo, int> *a = new Node<PersonalInfo, int>(x, phoneNr);
                insertNode(a);
            }
        }
        i++; i = i%3;
    }
    if(i) return 1; //end of data in the middle of structure
    return 0;
}

int Phonebook::getLenght(int i) {
    // the "length" of 0 is 1:
    int len = 1;
    if (i > 0) {
        for (len = 0; i > 0; len++) i = i/10;
    }
    return len;
}


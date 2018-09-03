#include "FenceCode.h"


int FenceCode::encrypt(std::ifstream &iffile, std::ofstream &offile) {
    intkey_ = atoi(getKey().c_str());
      std::string str((std::istreambuf_iterator<char>(iffile)), std::istreambuf_iterator<char>());
      if(intkey_ < 2) {
        offile << str;
        return 0;
      }
      //creating two-dimensional table
      int dim = ((str.length() - intkey_ + 1)/(intkey_ - 1)) + 1;
      dim ++;
      char table[intkey_][dim];
      for (int i = 0; i < intkey_; i++)
        for(int j = 0; j < dim; j++)
        table[i][j] = '\0';
      //wpisywanie liter z str do table

      bool up = false;
      int row = 0;
      int col = 0;
      for(unsigned int i = 0; i < str.length(); i++) {
        table[row][col] = str[i];
        if(row == intkey_ - 1 && up== false) {
            row = intkey_ - 2;
            col++;
            up = true;
        }
        else if (row == 0 && up == true) {
            row = 1;
            col ++;
            up = false;
        }
        else if(up == true) row--;
        else if(up == false) row++;
      }
      //creating a string from letters in a table
      std::string enc ="";

      for (int i = 0; i < intkey_; i++) {
      for(int j = 0; j < dim; j++) {
        if(table[i][j] != '\0') enc += table[i][j];
      } }
      enc += '\0';
      offile << enc;
      return 0;
}



int FenceCode::decrypt(std::ifstream &iffile, std::ofstream &offile) {
    std::string str((std::istreambuf_iterator<char>(iffile)), std::istreambuf_iterator<char>());
    if(str.length() == 0) return 1;
    intkey_ = atoi(getKey().c_str());
    if(intkey_ < 2) {
        offile << str;
        return 0;
    }
    char dec[str.length()];
    for(unsigned i = 0; i < str.length(); i++) dec[i] = '\0';
    int interspace = 2*intkey_ -2;

    unsigned int j = 0;
    int pos = 0;
    while(j < str.length()) {
            dec[j] = str[pos++];
            j += interspace;
    }

    interspace -= 2;
    j = 0;
    for(unsigned i = pos; i < str.length() - 1; i++) {
        if(j >= (str.length() - 1)) {
            j = 0;
            interspace -= 2;
            i--;
        }
        else {
            if(dec[j] != '\0') {
                while(j < str.length() -1 && dec[j] != '\0') j++;
                if(j < str.length() -1) {
                    dec[j] = str[i];
                    j+= interspace;
                }
                else i--;
            }
            else dec[j++] = str[i];

        }
    }
    offile << dec;
    return 0;
}

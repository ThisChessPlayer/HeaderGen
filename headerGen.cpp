/*******************************************************************************

                                                          Author: Jason Ma
                                                          Date:   May 08, 2017
                                    headerGen

 File Name:     headerGen.cpp
 Description:   Generates appropriate README files and headers for files.
*******************************************************************************/

#include <fstream>
#include <iostream>
#include "headerGen.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------------*
 Method Name: main
 File:        headerGen.cpp
  
 Description: Drives program.
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 argc               argument count
 argv               argument vector
 *----------------------------------------------------------------------------*/
int main(int argc, char * argv[]) {
  headerGen hg;
  const char * filepath = "./chars.txt";
  hg.loadChars(filepath);
  hg.genHeader("HI");
  return 0;
}

void headerGen::genHeader(const char * message) {
  //have array of strings for each row
  vector<string> rows;

  //init rows
  for(int i = 0; i < this->height; i++) {
    string str = "";
    rows.push_back(str);
  }

  
  int i = 0;

  //for each char in message
  while(message[i] != NULL) {
    //find alphabet index
    int alphabetInd = message[i] - 'A';
    for(int j = 0; j < this->height; j++) {
      rows[j] = rows[j] + this->alphabet[alphabetInd][j];
    }
    i++;
  }

  for(i = 0; i < this->height; i++) {
    cout << rows[i] << endl;
  }
  //see how long string is, warn user if > 80 characters, may not be possible with char *

  //keep array of last chars in each row
  
  //if either last chars in each row exists or first char in new loaded char is 
  //not space, then write a char there.

  //if last char, just write out last chars in each row
}

headerGen::headerGen() {
  this->height = 0;
  this->width = 0;
}

void headerGen::setSize(int h, int w) {
  this->height = h;
  this->width = w;
}

int headerGen::getWidth() {
  return this->width;
}

int headerGen::getHeight() {
  return this->height;
}

void headerGen::loadChars(const char * filepath) {

  std::ifstream infile(filepath);
  string tempStr;

  //read in width and height
  infile >> this->width >> this->height;
  //cout << this->width << " " << this->height << endl;
  getline(infile, tempStr);
  getline(infile, tempStr);

  for(char c = 'A'; c <= 'Z'; c++) {
    vector<string> v;
    //cout << "starting " << c << endl;
    for(int i = 0; i < this->height; i++) {
      getline(infile, tempStr);
      v.push_back(tempStr);
      //cout << tempStr << endl;
    }

    this->alphabet.push_back(v);
    getline(infile, tempStr);
  }

  //alphabet.push_back();
}
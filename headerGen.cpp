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
using std::ofstream;

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
  vector<string> header;
  headerGen hg;
  const char * filepath = "./chars.txt";
  hg.loadChars(filepath);
  header = hg.genHeader("HEADERGEN");
  hg.write("README", header);
  return 0;
}

vector<string> headerGen::genHeader(const char * message) {
  //have array of strings for each row
  vector<string> rows;

  int i, j;

  //init rows
  for(i = 0; i < this->height; i++) {
    rows.push_back("");
  }

  
  i = 0;

  //for each char in message
  while(message[i] != '\0') {
    //find alphabet index
    int alphabetInd = message[i] - 'A';
    for(j = 0; j < this->height; j++) {
      //get current last char
      char lastChar = rows[j].back();

      //last char
      if(rows[j].length() > 0)
        rows[j].pop_back();

      rows[j] = rows[j] + this->alphabet[alphabetInd][j];

      if(lastChar != '\0' && lastChar != ' ')
        rows[j][rows[j].length() - this->width] = lastChar;
    }
    i++;
  }

  if(rows[0].length() < 80) {
    int spaces = (80 - rows[0].length()) / 2;
    for(i = 0; i < spaces; i++) {
      for(j = 0; j < this->height; j++) {
        rows[j] = ' ' + rows[j] + ' ';
      }
    }
  }

  if(rows[0].length() < 80) {
    for(i = 0; i < this->height; i++)
      rows[i] = rows[i] + ' ';
  }

  return rows;

  //TODO write to file instead of stdout
  //TODO implement last char in each char thing
  //TODO set up command line args

  //see how long string is, warn user if > 80 characters, may not be possible with char *

  //keep array of last chars in each row
  
  //if either last chars in each row exists or first char in new loaded char is 
  //not space, then write a char there.

  //if last char, just write out last chars in each row
}

void headerGen::write(const char * filepath, vector<string> header) {
  
  ofstream outfile;
  outfile.open(filepath, std::ofstream::out);

  int i;
  outfile << "--------------------------------------------------------------------------------" << endl;
  for(i = 0; i < this->height; i++) {
    outfile << header[i] << endl;
  }
  outfile << "--------------------------------------------------------------------------------" << endl;

  outfile.close();
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

  infile.close();
  //alphabet.push_back();
}
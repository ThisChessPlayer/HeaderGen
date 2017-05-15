/*******************************************************************************

                                                          Author: Jason Ma
                                                          Date:   May 08, 2017
                                    headerGen

 File Name:     headerGen.cpp
 Description:   Generates appropriate README files and headers for files.
*******************************************************************************/

#include <fstream>
#include <iostream>
#include <getopt.h>
#include <ctype.h>
#include "headerGen.h"

using std::cout;
using std::cerr;
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
  char const * alphabetPath = "chars.txt";
  char const * filepath = "README";
  char const * message = "HEADERGEN";

  int opt;
  while((opt = getopt(argc, argv, "a:f:m:h")) != -1) {
    switch(opt) {
      case 'a': // alphabet location
        alphabetPath = optarg;
      case 'f': // filename
        filepath = optarg;
        break;
      case 'm': // message
        message = optarg;
        break;
      case 'h': // display long usage
        cout << "Usage: " << argv[0] << " [-a alphabet] [-f filename] [-m message] [-h]" << endl;
        cout << "  -a   specify alphabet location (chars.txt)" << endl;
        cout << "  -f   file to write header to" << endl;
        cout << "  -m   message to write in header" << endl;
        cout << "  -h   display long usage" << endl;
        return 0;
        break;
      default: /* '?' */
        cerr << "Usage: " << argv[0] << " [-a alphabet] [-f filename] [-m message] [-h]" << endl;
        return -1;
    }
  }

  if(optind < argc) {
    cerr << "Invalid options" << endl;
    return -1;
  }

  int i = 0;
  while(message[i]) {
    if(!isupper(message[i])) {
      cerr << "Invalid characters in message (Must use uppercase characters)." << endl;
      return -1;
    }
    i++;
  }

  hg.loadChars(alphabetPath);
  header = hg.genHeader(message);
  hg.write(filepath, header);
  return 0;
}

/*----------------------------------------------------------------------------*
 Method Name: genHeader
 File:        headerGen.cpp
  
 Description: Creates vector of strings to represent the message given
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 message            message to represent using ASCII text
 <return>           vector of strings representing message
 *----------------------------------------------------------------------------*/
vector<string> headerGen::genHeader(const char * message) {
  //vector of strings representing each row of header
  vector<string> rows;

  int i, j;

  //init rows
  for(i = 0; i < this->height; i++)
    rows.push_back("");
  
  i = 0;

  //for each char in message
  while(message[i] != '\0') {
    //find alphabet index with matching letter
    int alphabetInd = message[i] - 'A';
    for(j = 0; j < this->height; j++) {
      //get current last char
      char lastChar = rows[j].back();

      //pop last char
      if(rows[j].length() > 0)
        rows[j].pop_back();

      //add in new letter
      rows[j] = rows[j] + this->alphabet[alphabetInd][j];

      //substitute the old last char in before new letter if it isn't space
      if(lastChar != '\0' && lastChar != ' ')
        rows[j][rows[j].length() - this->width] = lastChar;
    }
    i++;
  }

  //space the message within 80 characters
  //TODO make this variable
  if(rows[0].length() < 80) {
    int spaces = (80 - rows[0].length()) / 2;
    for(i = 0; i < spaces; i++) {
      for(j = 0; j < this->height; j++) {
        rows[j] = ' ' + rows[j] + ' ';
      }
    }
  }

  //add in remaining character if the division comes out even and odd
  if(rows[0].length() < 80) {
    for(i = 0; i < this->height; i++)
      rows[i] = rows[i] + ' ';
  }

  return rows;
}

/*----------------------------------------------------------------------------*
 Method Name: write
 File:        headerGen.cpp
  
 Description: Opens file and overwrites it with header
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 filepath           location to write header
 header             vector of strings to write to file
 *----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*
 Method Name: headerGen
 File:        headerGen.cpp
  
 Description: Instantiates headerGen object.
 *----------------------------------------------------------------------------*/
headerGen::headerGen() {
  this->height = 0;
  this->width = 0;
}

/*----------------------------------------------------------------------------*
 Method Name: setSize
 File:        headerGen.cpp
  
 Description: Set size of header, affects way alphabet is read in and header is
              printed.
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 h                  height of header
 w                  width of header
 *----------------------------------------------------------------------------*/
void headerGen::setSize(int h, int w) {
  this->height = h;
  this->width = w;
}

/*----------------------------------------------------------------------------*
 Method Name: getWidth
 File:        headerGen.cpp
  
 Description: Returns width of header
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 <return>           width of header
 *----------------------------------------------------------------------------*/
int headerGen::getWidth() {
  return this->width;
}

/*----------------------------------------------------------------------------*
 Method Name: getHeight
 File:        headerGen.cpp
  
 Description: Returns height of header
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 <return>           height of header
 *----------------------------------------------------------------------------*/
int headerGen::getHeight() {
  return this->height;
}

/*----------------------------------------------------------------------------*
 Method Name: loadChars
 File:        headerGen.cpp
  
 Description: Loads alphabet into 2D vector of strings from given filepath.
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 filepath           path to file where alphabet is located
 *----------------------------------------------------------------------------*/
void headerGen::loadChars(const char * filepath) {

  std::ifstream infile(filepath);
  string tempStr;

  //read in width and height
  infile >> this->width >> this->height;

  //newlines between these and beginning of alphabet
  getline(infile, tempStr);
  getline(infile, tempStr);

  //read in alphabet using width and height.
  for(char c = 'A'; c <= 'Z'; c++) {
    vector<string> v;
    for(int i = 0; i < this->height; i++) {
      getline(infile, tempStr);
      v.push_back(tempStr);
    }

    this->alphabet.push_back(v);
    getline(infile, tempStr);
  }

  infile.close();
}
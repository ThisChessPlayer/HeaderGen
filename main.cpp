/*******************************************************************************

                                                          Author: Jason Ma
                                                          Date:   May 08, 2017
                                    headerGen

 File Name:     main.cpp
 Description:   Drives program, does arg parsing and delegates to headerGen.
*******************************************************************************/

#include <iostream>
#include <getopt.h>
#include <ctype.h>
#include "headerGen.h"

using std::cout;
using std::cerr;
using std::endl;

//TODO config mode, default arguments stored in txt file
char const * alphabetPath = "chars.txt";
char const * filepath = "README";
char const * message = "HEADERGEN";

bool messageSet = false;

/*----------------------------------------------------------------------------*
 Method Name: parseArgs
 File:        main.cpp
  
 Description: Parses arguments using getopt.
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 argc               argument count
 argv               argument vector
 <return>           0 on successful execution, -1 on errors
 *----------------------------------------------------------------------------*/
int parseArgs(int argc, char * argv[]) {
  int opt;
  while((opt = getopt(argc, argv, "a:f:m:h")) != -1) {
    switch(opt) {
      case 'a': //alphabet location
        alphabetPath = optarg;
        break;
      case 'f': //filename
        filepath = optarg;
        break;
      case 'm': //message
        message = optarg;
        messageSet = true;
        break;
      case 'h': //display long usage
        cout << "Usage: " << argv[0] << " [-a alphabet] [-f filename] [-m message] [-h]" << endl;
        cout << "  -a   specify alphabet location (chars.txt)" << endl;
        cout << "  -f   file to write header to" << endl;
        cout << "  -m   message to write in header" << endl;
        cout << "  -h   display long usage" << endl;
        return 0;
        break;
      default: // ?
        cerr << "Usage: " << argv[0] << " [-a alphabet] [-f filename] [-m message] [-h]" << endl;
        return -1;
    }
  }

  //extra arguments
  if(optind < argc) {
    cerr << "  Invalid options" << endl;
    return -1;
  }

  return 0;
}

/*----------------------------------------------------------------------------*
 Method Name: main
 File:        main.cpp
  
 Description: Takes in command line args, performs validity checks, and
              delegates to headerGen for processing.
  
 Parameter Descriptions:
 name               description
 ------------------ -----------------------------------------------
 argc               argument count
 argv               argument vector
 <return>           0 on successful execution of program
 *----------------------------------------------------------------------------*/
int main(int argc, char * argv[]) {
  vector<string> header;
  headerGen hg;

  int i, result;

  result = parseArgs(argc, argv);

  //unsuccessful arg parsing check
  if(result == -1)
    return -1;

  //check for non-uppercase characters in message
  i = 0;
  while(message[i]) {
    if(!isupper(message[i])) {
      cerr << "  Invalid characters in message (Must use uppercase characters)." << endl;
      return -1;
    }
    i++;
  }

  //print out info on what is happening
  cout << "  Alphabet: " << alphabetPath << endl;
  cout << "  Filepath: " << filepath << endl;
  cout << "  Message : " << message << endl;

  if(!messageSet) {
    cout << "  Set your own message using [-m MESSAGE]" << endl;
  }
  cout << endl;

  //load characters into 2D vector of strings so they can be used in message
  hg.loadChars(alphabetPath);

  //generate vector of strings representing message using loaded alphabet
  header = hg.genHeader(message);

  //check if something went wrong, likely with loading alphabet
  if(header.size() == 0) {
    cerr << "  Failed to write header to file." << endl;
    return -1;
  }

  //write header to outfile
  hg.write(filepath, header);

  cout << "  Successfully wrote header to file!" << endl;
  return 0;
}
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

/*----------------------------------------------------------------------------*
 Method Name: main
 File:        main.cpp
  
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
  bool messageSet = false;

  int opt;
  while((opt = getopt(argc, argv, "a:f:m:h")) != -1) {
    switch(opt) {
      case 'a': // alphabet location
        alphabetPath = optarg;
        break;
      case 'f': // filename
        filepath = optarg;
        break;
      case 'm': // message
        message = optarg;
        messageSet = true;
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
    cerr << "  Invalid options" << endl;
    return -1;
  }

  int i = 0;
  while(message[i]) {
    if(!isupper(message[i])) {
      cerr << "  Invalid characters in message (Must use uppercase characters)." << endl;
      return -1;
    }
    i++;
  }

  cout << "  Alphabet: " << alphabetPath << endl;
  cout << "  Filepath: " << filepath << endl;
  cout << "  Message : " << message << endl;

  if(!messageSet) {
    cout << "  Set your own message using [-m MESSAGE]" << endl;
  }
  cout << endl;

  hg.loadChars(alphabetPath);
  header = hg.genHeader(message);

  if(header.size() == 0) {
    cerr << "  Failed to write header to file." << endl;
    return -1;
  }
  hg.write(filepath, header);

  cout << "  Successfully wrote header to file!" << endl;
  return 0;
}
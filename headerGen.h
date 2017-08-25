/*******************************************************************************

                                                          Author: Jason Ma
                                                          Date:   May 08, 2017
                                    headerGen

 File Name:     headerGen.h
 Description:   Generates appropriate README files and headers for files.
*******************************************************************************/

#include <string>
#include <vector>

using std::string;
using std::vector;

#ifndef HEADERGEN_H
#define HEADERGEN_H

class headerGen{
  public:
    headerGen();
    void setSize(int h, int w);
    int getHeight();
    int getWidth();
    void loadChars(const char * filepath);
    vector<string> genHeader(const char * message);
    bool checkEmpty(const char * filepath);
    void write(const char * filepath, vector<string> header);
    void writeLines(const char * filepath, int lines);

  private:
    int width;
    int height;
    vector<vector<string>> alphabet;
};

#endif /* HEADERGEN_H */

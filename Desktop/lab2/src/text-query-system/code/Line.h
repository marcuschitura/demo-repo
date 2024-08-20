
#ifndef LINE_H
#define LINE_H

#include "Word.h"
#include <string>
#include <vector>
using namespace std;

class Line
{
public:
    // Constructor to initialize the Line object with a string
    Line(const string& line);
    
    // Returns true if the search word is found in the line; false otherwise
    bool contains(const Word& search_word) const;

private:
    vector<Word> WordsStorage; // Vector to store individual Word objects
};

#endif

#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <vector>
#include <tuple>
#include "Word.h"
#include "Line.h"

using namespace std;

class Paragraph
{
public:
    void addLine(const Line& line);
    tuple<bool, vector<int>> contains(const Word& search_word) const;

private:
    vector<Line> lines_; // Stores lines in the paragraph
};

#endif // PARAGRAPH_H

// -------------------------------------------
//					Paragraph
// -------------------------------------------

#include "Paragraph.h"

#include "Paragraph.h"

void Paragraph::addLine(const Line& line) {
    lines_.push_back(line); // Add the line to the internal storage
}

tuple<bool, vector<int>> Paragraph::contains(const Word& search_word) const {
    bool found = false;
    vector<int> line_indices;

    for (size_t i = 0; i < lines_.size(); ++i) {
        if (lines_[i].contains(search_word)) {
            found = true;
            line_indices.push_back(static_cast<int>(i)); // Record the line index
        }
    }

    return {found, line_indices}; // Return the result
}




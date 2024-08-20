#include "Line.h"
#include <sstream>

Line::Line(const string& line)
{
    // Create a stringstream from the input line
    stringstream ss(line);
    string temp_word;
    
    // Extract words separated by spaces
    while (ss >> temp_word) {
        Word newWord(temp_word); // Create a Word object for each extracted word
        
        if (newWord.isQueryable()) { // Check if the word can be queried
            WordsStorage.push_back(newWord); // Add the word to the collection
        }
    }
}

bool Line::contains(const Word& search_word) const
{
    // Check if the search_word is present in WordsInLine
    for (const auto& word : WordsStorage) {
        if (word == search_word) {
            return true; // Word is found
        }
    }
    return false; // Word is not found
}


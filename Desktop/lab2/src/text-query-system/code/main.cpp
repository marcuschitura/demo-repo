#include <iostream>
#include <string>
#include "Paragraph.h"
#include "FileReader.h"
#include "Word.h"

using namespace std;

int main() {
    string file_name;
    string search_word_str;
    
    // Prompt for file name
    cout << "Please enter file name: ";
    getline(cin, file_name);

    // Create FileReader and Paragraph objects
    FileReader file_reader(file_name);
    Paragraph paragraph;

    // Read the file into the Paragraph object
    file_reader.readFileInto(paragraph);

    while (true) {
        // Prompt for word to search for or "." to quit
        cout << "Please enter a word to search for or \".\" to quit: ";
        getline(cin, search_word_str);

        // Quit if the user inputs "."
        if (search_word_str == ".") {
            break;
        }

        // Create a Word object with the search term
        Word search_word(search_word_str);

        // Search for the word in the paragraph
        auto [found, line_numbers] = paragraph.contains(search_word);

        // Output the result
        if (found) {
            cout << "Word found:" << endl;
            for (int line_number : line_numbers) {
                cout << "line " << line_number << endl;
            }
        } else {
            cout << "Word not found" << endl;
        }
    }

    return 0;
}

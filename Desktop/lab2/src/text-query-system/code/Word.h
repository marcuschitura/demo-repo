#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

// empty classes to represent different exceptions
class WordContainsNoLetters {};
class WordContainsSpace {};


class Word
{
public:
	// DO NOT MODIFY THE PUBLIC INTERFACE OF THIS CLASS

	// constructor
	Word(const string& word);
	// overloads is-equal-to (or equivalence) operator - this is very useful for testing,
	// as we can compare words directly
	bool operator==(const Word& rhs) const;
	// returns true if queryable, false otherwise
	// (according to the brief, words less than 3 characters are not queryable)
	bool isQueryable() const;

private:
	string word_;
	void CheckLowerCase(); // converts all letters in word_ to lower case
	void PunctuatuinFix(); // removes all punctuation from word_
	bool isTherePunctuation() const; // checks if word_ only contains punctuation
	bool isSpaceAvailable() const; // checks if word_ contains a space
	void NewLineEdit(); // remove newline character if file is read in
	void NumbersEdit(); // removes numbers from the word
	static const auto MIN_SIZE_FOR_QUERY = 3u;
};

#endif



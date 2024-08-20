// -------------------------------------------
//					Word
// -------------------------------------------

#include "Word.h"

Word::Word(const string &word) : word_ { word }
{
	// throws an exception (in the form of WordContainsNoLetters object)
	// indicating that the word being constructed contains no letters
	if (word_.empty())
		throw WordContainsNoLetters { };

    CheckLowerCase();

    PunctuatuinFix();
	if (isTherePunctuation())
		throw WordContainsNoLetters { };
	if (isSpaceAvailable())
		throw WordContainsSpace { };

    NewLineEdit();
	NumbersEdit();

	// Note, we will cover exceptions in more detail later on in the course.
}

// overloads the equivalence operator which allows to Words to be compared using ==
bool Word::operator==(const Word &rhs) const
{
	if (word_ == rhs.word_)
		return true;
	else
		return false;
}

bool Word::isQueryable() const
{
	if (word_.length() >= MIN_SIZE_FOR_QUERY)
		return true;

		else

	return false;
}

void Word::CheckLowerCase()
{
	auto temp_word = string {""};

	for (auto i = 0u; i < word_.length(); i++)
    {
        temp_word+=tolower(word_.at(i));
    }
    word_=temp_word;
}

void Word::PunctuatuinFix()
{
	auto temp_word = string {""};
   

	for(char ch : word_)   
	{

  if(!ispunct(ch)){

	temp_word += ch;
  } 

	}

  word_ = move(temp_word);

}

void Word::NumbersEdit()
{
	auto temp_word = string {""};
   

	for(char ch : word_)   
	{

  if(!isdigit(ch)){

	temp_word += ch;
  } 

	}

  word_ = move(temp_word);
}

bool Word::isTherePunctuation() const
{
	for (char ch : word_)
    {
        if (isalpha(ch))
        {
            return false;
        }
    }
    return true;
}

bool Word::isSpaceAvailable() const
{
	for (char ch : word_) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            return true;  
        }
    }
    return false; 
}

void Word::NewLineEdit()
{
	auto temp_word = string {""};
   

	for(char ch : word_)   
	{

  if(!isspace(ch)){

	temp_word += ch;
  } 

	}

  word_ = move(temp_word);

}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//credit for the words.txt file to https://github.com/dwyl/english-words

std::string gIllegalCharactersString = "|\\,./?;:'@#~-_!\"£$%^&*()";
std::string gMisplacedCharacters;
std::string gConfirmedCharacters;
int gMaxWordLength = 0;

#define IF_TRUE_RETURN_FALSE( condition ) if( condition ) { return false; }

bool HasIllegalCharacters(const std::string& word)
{
    for(int i = 0; i < word.size(); ++i)
    {
        for(int j = 0; j < gIllegalCharactersString.size(); ++j)
        {
            if(word.at(i) == gIllegalCharactersString.at(j))
            {
                return true;
            }
        }
    }

    return false;
}

bool DoesNotMeetCharacterCriteria(const std::string& word)
{
    std::string missplacedCharacterCopy = gMisplacedCharacters;
    for(int i = 0; i < word.size(); ++i)
    {
        const char confirmedCharacter = std::tolower(gConfirmedCharacters.at(i));
        const char wordCharacter = std::tolower(word.at(i));

        if(confirmedCharacter != '_' && confirmedCharacter != wordCharacter)
        {
            return true;
        }

        for(int j = 0; j < missplacedCharacterCopy.size(); ++j)
        {
            const char missplacedCopyChar = std::tolower(missplacedCharacterCopy.at(j));
            if(missplacedCopyChar == wordCharacter)
            {
                missplacedCharacterCopy.erase(j, 1);
            }
        }
    }

    if(missplacedCharacterCopy.size() != 0)
    {
        //std::cout << missplacedCharacterCopy << std::endl;
        return true;
    }

    return false;
}

bool IsWordLegal(const std::string& word)
{
    IF_TRUE_RETURN_FALSE(word.size() != gMaxWordLength)
    IF_TRUE_RETURN_FALSE(HasIllegalCharacters(word))
    IF_TRUE_RETURN_FALSE(DoesNotMeetCharacterCriteria(word))

    return true;
}

int main()
{
    std::cout << "Welcome to the WORDLE solver." << std::endl;
    std::cout << "Please enter the length of your word: ";
    std::cin >> gMaxWordLength;

    std::cout << "Please enter all characters which are valid but are missplaced without spacing or punctuation: ";
    std::cin >> gMisplacedCharacters;
    
    std::cout << "Please enter all characters which correctly placed, any character in the word you do NOT know should be an underscore (\"_\") character: ";
    std::cin >> gConfirmedCharacters;

    if(gConfirmedCharacters.size() != gMaxWordLength)
    {
        std::cout << "The Confimred Characters string (" << gConfirmedCharacters.size() << ") must match the given size of the word(" << gMaxWordLength << ").";
        return 1;
    }
    
    std::string line;
    std::ifstream wordListFile("words.txt");

    if(wordListFile)
    {
        while(getline(wordListFile, line))
        {
            if(IsWordLegal(line))
            {
                std::cout << line << std::endl;
            }
        }
    }

    return 0;
}
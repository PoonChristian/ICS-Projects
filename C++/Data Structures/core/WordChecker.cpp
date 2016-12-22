// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"



WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> suggestions;
    swapCharacters(suggestions, word);
    insertAlphabet(suggestions,word);
    deleteCharacters(suggestions,word);
    replaceWithAlphabet(suggestions, word);
    splitWord(suggestions, word);
    std::sort(suggestions.begin(), suggestions.end());
    return suggestions;
}


void WordChecker::swapCharacters(std::vector<std::string>& suggestions,
                                const std::string& word) const
{
    for (int i = 0; i < word.length() - 1; ++i)
    {
        std::string tempWord = word;
        std::swap(tempWord[i], tempWord[i+1]);
        if ((std::find(suggestions.begin(), suggestions.end(), tempWord) == suggestions.end()) && wordExists(tempWord))
        {
            suggestions.push_back(tempWord);
        }
    }
}


void WordChecker::insertAlphabet(std::vector<std::string>& suggestions,
                                const std::string& word) const
{
    for (int i = 0; i < word.length() + 1; ++i)
    {
        for (int j = 65; j < 91; ++j)
        {
            std::string tempWord = word;
            char ascii = j;
            std::ostringstream oss;
            oss << ascii;
            tempWord.insert(i, oss.str());
            if ((std::find(suggestions.begin(), suggestions.end(), tempWord) == suggestions.end()) && wordExists(tempWord))
            {
                suggestions.push_back(tempWord);
            }
        }
    }
}


void WordChecker::deleteCharacters(std::vector<std::string>& suggestions,
                                    const std::string& word) const
{
    for (int i = 0; i < word.length(); ++i)
    {
        std::string tempWord = word;
        tempWord.erase(i, 1);
        if ((std::find(suggestions.begin(), suggestions.end(), tempWord) == suggestions.end()) && wordExists(tempWord))
        {
            suggestions.push_back(tempWord);
        }
    }
}


void WordChecker::replaceWithAlphabet(std::vector<std::string>& suggestions,
                                        const std::string& word) const
{
    for (int i = 0; i < word.length(); ++i)
    {
        for (int j = 65; j < 91; ++j)
        {
            std::string tempWord = word;
            char ascii = j;
            std::ostringstream oss;
            oss << ascii;
            tempWord.replace(i, 1, oss.str());
            if ((std::find(suggestions.begin(), suggestions.end(), tempWord) == suggestions.end()) && wordExists(tempWord))
            {
                suggestions.push_back(tempWord);
            }
        }
    }
}


void WordChecker::splitWord(std::vector<std::string>& suggestions,
                            const std::string& word) const
{
    for (int i = 1; i < word.length(); ++i)
    {
        std::string tempWord = word;
        tempWord.insert(i, " ");
        std::string firstWord = tempWord.substr(0, i);
        std::string secondWord = tempWord.substr(i+1);
        if ((std::find(suggestions.begin(), suggestions.end(), firstWord) == suggestions.end()) && wordExists(firstWord) &&
        (std::find(suggestions.begin(), suggestions.end(), secondWord) == suggestions.end()) && wordExists(secondWord))
        {
            suggestions.push_back(tempWord);
        }
    }
}

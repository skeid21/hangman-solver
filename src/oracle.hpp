

#ifndef oracle_hpp
#define oracle_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Oracle
{
public:
    Oracle(const std::string& word, int max_failures);

    size_t getWordLength();

    std::vector<int> guessLetter(char character);
    int numPositionsOpen();
    bool foundPosition(int position);
    bool didFindEntireWord();

    bool didWin(const std::string& word);
    bool didLoose();
    
    const std::string& getWord();

private:
    std::string m_word;
    std::vector<bool> m_value_found;
    int m_lettersFound;
    int m_current_failures;
    int m_max_failures;
};

#endif /* oracle_hpp */

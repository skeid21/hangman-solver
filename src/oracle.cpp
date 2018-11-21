

#include "oracle.hpp"


Oracle::Oracle(const std::string& word, int max_failures):
    m_word(word),
    m_lettersFound(0),
    m_current_failures(0),
    m_max_failures(max_failures)
{
    m_value_found.resize(word.size());
    for (int scan = 0; scan < word.size(); ++scan)
    {
        m_value_found[scan] = false;
    }
}

size_t Oracle::getWordLength()
{
    return m_word.size();
}

std::vector<int> Oracle::guessLetter( char character)
{
    std::vector<int> indexes;
    for (size_t scan = 0; scan < m_word.size(); ++scan)
    {
        if (m_word[scan] == character)
        {
            indexes.push_back(static_cast<int>(scan));
            m_value_found[scan] = true;
            m_lettersFound++;
        }
    }

    if (indexes.size() == 0)
    {
        m_current_failures++;
    }
    return indexes;
}

int Oracle::numPositionsOpen()
{
    int num_not_found = 0;
    for (const auto& val : m_value_found)
    {
        if (false == val)
        {
            num_not_found++;
        }
    }

    return num_not_found;
}

bool Oracle::foundPosition(int position)
{
    return m_value_found[position];
}

bool Oracle::didFindEntireWord()
{
    return m_lettersFound == m_word.length();
}

bool Oracle::didWin(const std::string& word)
{
    return (word == m_word) && (m_current_failures < m_max_failures);
}

bool Oracle::didLoose()
{
    return m_current_failures >= m_max_failures;
}

const std::string& Oracle::getWord()
{
    return m_word;
}

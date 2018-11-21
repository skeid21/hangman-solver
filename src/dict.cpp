#include "dict.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

static dictionary_container_t s_dict;
const dictionary_container_t& getDictionary()
{
    if (false == s_dict.empty())
    {
        return s_dict;
    }

    std::ifstream dictionary_file ("words.txt");
    if (dictionary_file.is_open())
    {
        std::string line;
        while ( std::getline (dictionary_file,line) )
        {
            s_dict.push_back(std::move(line));
        }
        dictionary_file.close();
    }
    else
    {
        std::cerr << "Error opening dictionary_file";
    }

    std::random_shuffle(s_dict.begin(), s_dict.end());
    return s_dict;
}

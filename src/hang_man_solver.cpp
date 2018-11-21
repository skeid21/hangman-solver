

#include "hang_man_solver.hpp"


std::string HangManSolver::solve(Oracle& oracle, const dictionary_container_t& dictionary)
{
    std::string rval = "";
    size_t word_size = oracle.getWordLength();

    std::vector<const std::string*> potential_words;
    for (auto itr = dictionary.begin(); itr != dictionary.end(); ++itr)
    {
        if (itr->size() == word_size)
        {
            potential_words.push_back(&*itr);
        }
    }

    int current_position = 0;
    std::vector<char> found_letters;
    found_letters.reserve(word_size);
    std::vector<int> indexes;
    while (true)
    {
        char current_character = potential_words[0]->at(current_position);
        indexes = oracle.guessLetter(current_character);
        if (indexes.size() > 0)
        {
            found_letters.push_back(current_character);
            std::vector<const std::string*> new_potential_words;
            new_potential_words.reserve(potential_words.size()/2);
            for (auto itr = potential_words.begin(); itr != potential_words.end(); ++itr)
            {
                size_t find_index = -1;
                int count = 0;
                do
                {
                    find_index = (*itr)->find(current_character, find_index+1);
                    count++;
                    if (find_index == std::string::npos && count > indexes.size())
                    {
                        new_potential_words.push_back(*itr);
                        break;
                    }
                    else if (indexes.end() == std::find(indexes.begin(), indexes.end(), find_index))
                    {
                        break;
                    }
                }while(find_index != std::string::npos);
            }
            potential_words = std::move(new_potential_words);
            if (indexes.end() != std::find(indexes.begin(), indexes.end(), current_position))
            {
                current_position++;
                while(oracle.foundPosition(current_position))
                {
                    current_position++;
                }
            }
        }
        else
        {
            std::vector<const std::string*> new_potential_words;
            new_potential_words.reserve(potential_words.size()/2);
            for (auto itr = potential_words.begin(); itr != potential_words.end(); ++itr)
            {
                if (std::string::npos == (*itr)->find(current_character))
                {
                    new_potential_words.push_back(*itr);
                }
            }
            potential_words = std::move(new_potential_words);
        }


        if (potential_words.size() == 1)
        {
            rval = *potential_words[0];
            break;
        }

    }


    return rval;
}

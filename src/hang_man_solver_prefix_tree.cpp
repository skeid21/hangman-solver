#include <iostream>
#include "hang_man_solver_prefix_tree.hpp"
#include "prefix_tree.hpp"
using namespace std;

string HangManSolverPrefixTree::solve(Oracle& oracle, const dictionary_container_t& dictionary)
{
    auto prefixTree = PrefixTreeNode::build(dictionary, oracle.getWordLength()); 

    int focusSearchIndex = 0;

    string foundWord;
    foundWord.resize(oracle.getWordLength());

    int iteration = 0; 
    while(false == oracle.didFindEntireWord())
    {
        char character;
        if (false == prefixTree->getCharacterForIndex(character, focusSearchIndex)) {
            return "";
        }

        auto guessResult = oracle.guessLetter(character);
        prefixTree->removeAllNodesWithCharacterNotAtIndex(character, guessResult);

        for(const auto index : guessResult)
        {
            foundWord[index] = character;
        }

        for(int scan = 0; scan < oracle.getWordLength(); ++scan) {
            if (false == oracle.foundPosition(scan)){
                focusSearchIndex = scan;
                break;
            }
        }
        iteration++;
    }
    return foundWord;
}

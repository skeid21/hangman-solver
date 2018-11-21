#include "prefix_tree.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

shared_ptr<PrefixTreeNode> PrefixTreeNode::build(
    const dictionary_container_t &words,
    size_t wordLength)
{
    auto root = make_shared<PrefixTreeNode>();
    for (auto word : words)
    {
        if (word.length() != wordLength)
        {
            continue;
        }

        auto currentNode = root;
        for (auto character : word)
        {
            auto findItr = findChildForCharacter(
                character,
                currentNode->children.begin(),
                currentNode->children.end());

            std::shared_ptr<PrefixTreeNode> nextNode;
            if (findItr == currentNode->children.end())
            {
                nextNode = make_shared<PrefixTreeNode>();
                nextNode->character = character;
                currentNode->children.push_back(nextNode);
            }
            else
            {
                nextNode = *findItr;
            }
            nextNode->score++;
            std::sort(
                currentNode->children.begin(),
                currentNode->children.end(),
                [](auto lhv, auto rhv) {
                    return lhv->score > rhv->score;
                });

            currentNode = nextNode;
        }

        //mark the end of the word
        currentNode->isTerminalNode = true;
    }
    return root;
}

bool PrefixTreeNode::getCharacterForIndex(char &outCharacter, int targetIndex)
{
    int currentIndex = -2;
    return _getCharacterForIndex(outCharacter, currentIndex, targetIndex);
}

void PrefixTreeNode::removeAllNodesWithCharacterNotAtIndex(
    const char allowedCharacter,
    const std::vector<int> &validIndexs)
{
    int currentIndex = -2;
    _removeAllNodesWithCharacterNotAtIndex(currentIndex, allowedCharacter, validIndexs);
}

bool PrefixTreeNode::containsWord(const std::string &word)
{
    auto currentNode = this;
    for (const auto &character : word)
    {
        auto findItr = findChildForCharacter(
            character,
            currentNode->children.begin(),
            currentNode->children.end());
        if (findItr == currentNode->children.end())
        {
            return false;
        }
        currentNode = (*findItr).get();
    }
    return currentNode->isTerminalNode;
}

static int printcount = 0;
void PrefixTreeNode::printAllWords()
{
    std::string word;
    _print(this, word);
}

void PrefixTreeNode::_print(PrefixTreeNode *current, std::string &word)
{
    if (current->isTerminalNode)
    {
        cout << word << endl;
    }

    for (const auto child : current->children)
    {
        word.push_back(child->character);
        _print(child.get(), word);
        word.pop_back();
    }
}

bool PrefixTreeNode::_getCharacterForIndex(
    char &outCharacter,
    int &currentIndex,
    const int targetIndex)
{
    currentIndex++;
    if (currentIndex == targetIndex)
    {
        outCharacter = character;
        return true;
    }
    else
    {
        for (const auto child : children)
        {
            if (true == child->_getCharacterForIndex(outCharacter, currentIndex, targetIndex))
            {
                return true;
            }
        }
    }
    currentIndex--;
    return false;
}

bool PrefixTreeNode::_removeAllNodesWithCharacterNotAtIndex(
    int &currentIndex,
    const char allowedCharacter,
    const std::vector<int> &validIndexs)
{
    currentIndex++;
    bool pruneToNextTerminalOrBranchNode = false;
    bool isfocusIndex = find(
                            validIndexs.begin(),
                            validIndexs.end(),
                            currentIndex) != validIndexs.end();

    if (isfocusIndex)
    {
        if (character != allowedCharacter)
        {
            currentIndex--;
            return true;
        }
    }
    else
    {
        if (character == allowedCharacter)
        {
            currentIndex--;
            return true;
        }
    }

    for (auto itr = children.begin(); itr != children.end();)
    {
        if (true == (*itr)->_removeAllNodesWithCharacterNotAtIndex(currentIndex, allowedCharacter, validIndexs))
        {
            itr = children.erase(itr);
        }
        else
        {
            itr++;
        }
    }

    currentIndex--;
    
    return (children.empty() && isTerminalNode == false);
}

PrefixTreeNode::children_map_t::const_iterator PrefixTreeNode::findChildForCharacter(
    char character,
    children_map_t::const_iterator begin,
    children_map_t::const_iterator end)
{
    return find_if(begin, end, [&](auto node) {
        return node->character == character;
    });
}

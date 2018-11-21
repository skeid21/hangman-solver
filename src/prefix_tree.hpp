#pragma once
#include <vector>
#include <memory>
#include <string>
#include "dict.hpp"

class PrefixTreeNode : std::enable_shared_from_this<PrefixTreeNode>
{
    bool isTerminalNode = false;
    unsigned int score = 0;
    char character;
    using children_map_t = std::vector<std::shared_ptr<PrefixTreeNode>>;
    children_map_t children;

  public:
    static std::shared_ptr<PrefixTreeNode> build(const dictionary_container_t &words, size_t max_word_length);

    inline bool getIsTerminalNode() { return isTerminalNode; }

    bool getCharacterForIndex(char &outCharacter, int index);

    void removeAllNodesWithCharacterNotAtIndex(
      const char allowedCharacter, 
      const std::vector<int> &validIndexs);

    bool containsWord(const std::string &word);

    void printAllWords();

  private:
    void _print(
      PrefixTreeNode *current, 
      std::string &word);

    bool _getCharacterForIndex(
      char &outCharacter, 
      int &currentIndex, const int targetIndex);
    
    bool _removeAllNodesWithCharacterNotAtIndex(
      int &currentIndex, 
      const char allowedCharacter, 
      const std::vector<int> &validIndexs);

    static children_map_t::const_iterator findChildForCharacter(
      char character,
      children_map_t::const_iterator begin, 
      children_map_t::const_iterator end);
};

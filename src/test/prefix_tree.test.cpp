#include <gtest/gtest.h>
#include "../prefix_tree.hpp"
TEST(PrefixTree, SingleWordIsEncoded) 
{
    dictionary_container_t words;
    
    std::string testWord = "testingword";
    words.push_back(testWord);
    auto sut = PrefixTreeNode::build(words, testWord.size());
    
    ASSERT_NE(sut, nullptr);
    ASSERT_TRUE(sut->containsWord(testWord));
}

TEST(PrefixTree, MutipleWordsAreEncoded) 
{
    dictionary_container_t words;
    
    words.push_back("testingword");
    words.push_back("jkldsjfklla");
    words.push_back("mckjlsjkew-");
    auto sut = PrefixTreeNode::build(words, 11);
    ASSERT_NE(sut, nullptr);
    for(const auto& word : words)
    {
        EXPECT_TRUE(sut->containsWord(word));
    }
}

TEST(PrefixTree, OverlappingWordsAreEncoded) 
{
    dictionary_container_t words;

    words.push_back("testingword1");
    words.push_back("testingword2");
    auto sut = PrefixTreeNode::build(words, 12);
    ASSERT_NE(sut, nullptr);
    for(const auto& word : words)
    {
        EXPECT_TRUE(sut->containsWord(word));
    }
}

TEST(PrefixTree, OverlappingWordsNotEncodedAreNotFound) 
{
    dictionary_container_t words;
    
    words.push_back("testing");
    auto sut = PrefixTreeNode::build(words, 15);
    ASSERT_NE(sut, nullptr);
    ASSERT_FALSE(sut->containsWord("testingword"));
}
TEST(PrefixTree, GetCharacgterAtIndexReturnsFalseOnEmptyTree)
{
    dictionary_container_t words;
    words.push_back("testingword");
    auto sut = PrefixTreeNode::build(words, 10);
    char character;
    EXPECT_EQ(false, sut->getCharacterForIndex(character, 5));
}

TEST(PrefixTree, GetCharacterAtIndexReturnsExpectedCharacter)
{
    dictionary_container_t words;
    words.push_back("testingword");
    auto sut = PrefixTreeNode::build(words, 11);
    char character;
    EXPECT_EQ(true, sut->getCharacterForIndex(character, 5));
    EXPECT_EQ(character, 'n');
}

TEST(PrefixTree, RemoveAllNodesWithCharacterNotAtIndexWillRemoveEntireWord)
{
    std::string testWord = "Testingword";
    dictionary_container_t words;
    words.push_back(testWord);
    auto sut = PrefixTreeNode::build(words, testWord.size());
    sut->removeAllNodesWithCharacterNotAtIndex('a', {0});
    EXPECT_FALSE(sut->containsWord(testWord));
}

TEST(PrefixTree, RemoveAllNodesWithCharacterNotAtIndexRemovesWordWithCharacterAtWrongIndex) 
{
    std::string testWord = "testingword";
    dictionary_container_t words;
    words.push_back(testWord);
    auto sut = PrefixTreeNode::build(words, testWord.size());
    sut->removeAllNodesWithCharacterNotAtIndex('t', {0});
    EXPECT_FALSE(sut->containsWord(testWord));
}
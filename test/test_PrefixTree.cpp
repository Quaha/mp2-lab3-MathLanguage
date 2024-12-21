#include <gtest.h>

#include "includes.h"
#include "PrefixTree.h"

TEST(PrefixTree, addAndGetData) {
    PrefixTree<string, string, char> tree;

    tree.addWord("apple", "A fruit");
    tree.addWord("banana", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("banana"), "Another fruit");
}

TEST(PrefixTree, wordExists) {
    PrefixTree<string, string, char> tree;

    tree.addWord("apple", "A fruit");

    EXPECT_TRUE(tree.exists("apple"));
    EXPECT_FALSE(tree.exists("banana"));
}

TEST(PrefixTree, nonExistentWordThrowsException) {
    PrefixTree<string, string, char> tree;

    tree.addWord("apple", "A fruit");

    ASSERT_ANY_THROW(tree.getData("banana"));
}

TEST(PrefixTree, emptyWord) {
    PrefixTree<string, string, char> tree;
    tree.addWord("", "An empty word");

    EXPECT_EQ(tree.getData(""), "An empty word");
}

TEST(PrefixTree, addWordsAndCheckOrder) {
    PrefixTree<int, string, char> tree;

    tree.addWord("apple", 1);
    tree.addWord("banana", 2);

    EXPECT_EQ(tree.getData("apple"), 1);
    EXPECT_EQ(tree.getData("banana"), 2);
}

TEST(PrefixTree, LongChainOfWords) {
    PrefixTree<string, string, char> tree;
    tree.addWord("thisisaverylongword", "A very long word");

    EXPECT_EQ(tree.getData("thisisaverylongword"), "A very long word");
}

TEST(PrefixTree, handleMultipleWordsWithCommonPrefix) {
    PrefixTree<string, string, char> tree;
    tree.addWord("apple", "A fruit");
    tree.addWord("apricot", "Another fruit");

    EXPECT_EQ(tree.getData("apple"), "A fruit");
    EXPECT_EQ(tree.getData("apricot"), "Another fruit");
}

TEST(PrefixTree, handleNestedWords) {
    PrefixTree<string, string, char> tree;
    tree.addWord("hello", "A greeting");
    tree.addWord("hell", "A word meaning underworld");

    EXPECT_EQ(tree.getData("hello"), "A greeting");
    EXPECT_EQ(tree.getData("hell"), "A word meaning underworld");
}
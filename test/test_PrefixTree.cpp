#include <gtest.h>

#include "includes.h"

#include "PrefixTree.h"

TEST(PrefixTree, canAddWords) {

	PrefixTree<void, std::string, char> tree;

	ASSERT_NO_THROW(tree.addWord("abcd", nullptr));
	ASSERT_NO_THROW(tree.addWord("abce", nullptr));
	ASSERT_NO_THROW(tree.addWord("f", nullptr));
}

TEST(PrefixTree, canFindWords) {

	PrefixTree<void, std::string, char> tree;

	tree.addWord("abcd", nullptr);
	tree.addWord("abce", nullptr);
	tree.addWord("f", nullptr);

	EXPECT_EQ(tree.exists("abcd"), true);
	EXPECT_EQ(tree.exists("abce"), true);
	EXPECT_EQ(tree.exists("f"), true);
}

TEST(PrefixTree, cantFindWords) {

	PrefixTree<void, std::string, char> tree;

	tree.addWord("abcd", nullptr);
	tree.addWord("abce", nullptr);
	tree.addWord("f", nullptr);

	EXPECT_EQ(tree.exists("a"), false);
	EXPECT_EQ(tree.exists("bfs"), false);
}

TEST(PrefixTree, canGetData) {

	PrefixTree<int, std::string, char> tree;

	int* a = new int;
	int* b = new int;

	*a = 5;
	*b = 3;

	tree.addWord("abcd", a);
	tree.addWord("f", b);

	EXPECT_EQ(*tree.getData("abcd"), 5);
	EXPECT_EQ(*tree.getData("f"), 3);
}

TEST(PrefixTree, cantGetData) {

	PrefixTree<int, std::string, char> tree;

	int* a = new int;
	int* b = new int;

	*a = 5;
	*b = 3;

	tree.addWord("abcd", a);
	tree.addWord("f", b);


	ASSERT_ANY_THROW(tree.getData("123"));
}

TEST(PrefixTree, canCheckExistence) {

	PrefixTree<int, std::string, char> tree;

	int* a = new int;
	int* b = new int;

	*a = 5;
	*b = 3;

	tree.addWord("abcd", a);
	tree.addWord("f", b);

	EXPECT_EQ(*tree.getData("abcd"), 5);
	EXPECT_EQ(*tree.getData("f"), 3);

	ASSERT_ANY_THROW(tree.getData("123"));
	EXPECT_EQ(tree.exists("f"), true);

	EXPECT_EQ(tree.exists("a"), false);
	EXPECT_EQ(tree.exists("bfs"), false);
}

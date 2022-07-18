#define BOOST_TEST_MODULE BST_Tests
#include <C:\boost_1_78_0\boost_1_78_0\boost\test\included\unit_test.hpp>
#include <utility>

// // Uncomment the below macros enable dynamic linking.
// // You will also need to comment-out the `single-header' macros above.
// #define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE BST_Tests
// #include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////

#include "bst.h"

using Dict = BST;

using KeyType = Dict::KeyType;

using ItemType = Dict::ItemType;


////////////////////////////////////////////////////////////////////////////////

// Utility Functions


void isPresent(Dict& dict, KeyType k, ItemType i)
{
	boost::debug::detect_memory_leaks(false); // disables memory leak notices in command line.
	ItemType* p_i = dict.lookup(k);
	BOOST_CHECK_MESSAGE(p_i, std::to_string(k) + " is missing");
	if (p_i)
	{
		BOOST_CHECK_MESSAGE(*p_i == i,
			std::to_string(k) + " should be " + i + ", but found " + *p_i);
	}
}

void isAbsent(Dict& dict, KeyType k)
{
	boost::debug::detect_memory_leaks(false);
	BOOST_CHECK_MESSAGE(dict.lookup(k) == nullptr,
		std::to_string(k) + " should be absent, but is present.");
}

void insertTestData(Dict& dict)
{
	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	dict.insert(0, "Harold");
	dict.insert(9, "Edward");
	dict.insert(37, "Victoria");
	dict.insert(4, "Matilda");
	dict.insert(26, "Oliver");
	dict.insert(42, "Elizabeth");
	dict.insert(19, "Henry");
	dict.insert(4, "Stephen");
	dict.insert(24, "James");
	dict.insert(-1, "Edward");
	dict.insert(31, "Anne");
	dict.insert(23, "Elizabeth");
	dict.insert(1, "William");
	dict.insert(26, "Charles");
}

////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(Display_Tests)

BOOST_AUTO_TEST_CASE(DisplayTree)
{

	using Dict = BST;
	BST dict;

	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	dict.insert(0, "Harold");
	dict.insert(9, "Edward");
	dict.insert(37, "Victoria");
	dict.insert(4, "Matilda");
	dict.insert(26, "Oliver");
	dict.insert(42, "Elizabeth");
	dict.insert(19, "Henry");
	dict.insert(4, "Stephen");
	dict.insert(24, "James");
	dict.insert(-1, "Jamie");
	dict.insert(31, "Anne");
	dict.insert(23, "Elizabeth");
	dict.insert(1, "William");
	dict.insert(26, "Charles");

	std::cout << "Display the full tree in order: " << std::endl;

	dict.displayEntries();

	std::cout << std::endl;


}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////////////
//
BOOST_AUTO_TEST_SUITE(Constructor_Tests)

BOOST_AUTO_TEST_CASE(EmptyConstructor)
{

	new Dict();
}

BOOST_AUTO_TEST_CASE(DestroyEmptyDict)
{
	Dict dict;
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(Lookup_Insert_Tests)

BOOST_AUTO_TEST_CASE(EmptyLookup)
{
	Dict dict;
	isAbsent(dict, 1);
}

BOOST_AUTO_TEST_CASE(SingleInsert)
{
	Dict dict;
	dict.insert(22, "Mary");
}

BOOST_AUTO_TEST_CASE(SingleInsertLookup)
{
	Dict dict;
	dict.insert(22, "Mary");
	isPresent(dict, 22, "Mary");
}

BOOST_AUTO_TEST_CASE(SingleOverwriteLookup)
{
	Dict dict;
	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	isPresent(dict, 22, "Mary");
}

BOOST_AUTO_TEST_CASE(MultipleInsert)
{
	Dict dict;
	insertTestData(dict);
}

BOOST_AUTO_TEST_CASE(MultipleInsertLookupPresent)
{
	Dict dict;
	insertTestData(dict);

	isPresent(dict, 22, "Mary");
	isPresent(dict, 4, "Stephen");
	isPresent(dict, 9, "Edward");
	isPresent(dict, 1, "William");
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 37, "Victoria");
	isPresent(dict, 42, "Elizabeth");
	isPresent(dict, -1, "Edward");
}

BOOST_AUTO_TEST_CASE(MultipleInsertLookupAbsent)
{
	Dict dict;
	insertTestData(dict);

	isAbsent(dict, 2);
	isAbsent(dict, 3);
	isAbsent(dict, -4);
	isAbsent(dict, 56);
	isAbsent(dict, 30);
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(Remove_Tests)

BOOST_AUTO_TEST_CASE(DeleteEmpty)
{
	Dict dict;
	dict.remove(43);
	isAbsent(dict, 43);
}

BOOST_AUTO_TEST_CASE(DeleteChildlessRoot)
{
	Dict dict;
	dict.insert(7, "John");
	dict.remove(7);
	isAbsent(dict, 7);
}

BOOST_AUTO_TEST_CASE(DeleteLeftChildOfRoot)
{
	Dict dict;
	dict.insert(31, "Anne");
	dict.insert(7, "John");
	dict.remove(7);

	isAbsent(dict, 7);
	isPresent(dict, 31, "Anne");
}

BOOST_AUTO_TEST_CASE(DeleteRightChildOfRoot)
{
	Dict dict;
	dict.insert(7, "John");
	dict.insert(31, "Anne");
	dict.remove(31);

	isAbsent(dict, 31);
	isPresent(dict, 7, "John");
}

BOOST_AUTO_TEST_CASE(InsertNodes_DeleteChildlessNodes)
{
	Dict dict;
	insertTestData(dict);

	dict.remove(-1);
	isAbsent(dict, -1);

	dict.remove(1);
	isAbsent(dict, 1);

	dict.remove(19);
	isAbsent(dict, 19);

	dict.remove(23);
	isAbsent(dict, 23);

	dict.remove(31);
	isAbsent(dict, 31);

	dict.remove(42);
	isAbsent(dict, 42);

	dict.remove(4);
	isAbsent(dict, 4);

	isPresent(dict, 22, "Mary");
	isPresent(dict, 9, "Edward");
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 37, "Victoria");
}

BOOST_AUTO_TEST_CASE(OverwriteThenDelete)
{
	Dict dict;
	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	dict.insert(4, "Matilda");
	dict.insert(26, "Oliver");
	dict.insert(4, "Stephen");
	dict.insert(26, "Charles");

	dict.remove(4);
	isAbsent(dict, 4);

	dict.remove(26);
	isAbsent(dict, 26);

	dict.remove(22);
	isAbsent(dict, 22);
}

BOOST_AUTO_TEST_CASE(DeleteRootWithLeftChild)
{
	Dict dict;
	dict.insert(31, "Anne");
	dict.insert(7, "John");
	dict.remove(31);

	isAbsent(dict, 31);
	isPresent(dict, 7, "John");
}

BOOST_AUTO_TEST_CASE(DeleteRootWithRightChild)
{
	Dict dict;
	dict.insert(7, "John");
	dict.insert(31, "Anne");
	dict.remove(31);

	isAbsent(dict, 31);
	isPresent(dict, 7, "John");
}

BOOST_AUTO_TEST_CASE(InseertNodes_DeleteNodesWithOneChild)
{
	Dict dict;
	insertTestData(dict);

	dict.remove(4);
	isAbsent(dict, 4);

	dict.remove(1);
	isAbsent(dict, 1);

	dict.remove(9);
	isAbsent(dict, 9);

	isPresent(dict, 22, "Mary");
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 37, "Victoria");
	isPresent(dict, 42, "Elizabeth");
	isPresent(dict, -1, "Edward");

}

BOOST_AUTO_TEST_CASE(DeleteRootWithChildren)
{
	Dict dict;
	dict.insert(31, "Anne");
	dict.insert(7, "John");
	dict.insert(42, "Elizabeth");
	dict.remove(31);

	isAbsent(dict, 31);
	isPresent(dict, 7, "John");
	isPresent(dict, 42, "Elizabeth");
}

BOOST_AUTO_TEST_CASE(InsertNodes_DeleteNodesWithChildren)
{
	Dict dict;
	insertTestData(dict);

	dict.remove(0);
	isAbsent(dict, 0);

	dict.remove(37);
	isAbsent(dict, 37);

	dict.remove(22);
	isAbsent(dict, 22);

	isPresent(dict, 4, "Stephen");
	isPresent(dict, 9, "Edward");
	isPresent(dict, 1, "William");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 42, "Elizabeth");
	isPresent(dict, -1, "Edward");

}

BOOST_AUTO_TEST_CASE(InsertNodes_DeleteAbsent)
{
	Dict dict;

	insertTestData(dict);

	dict.remove(6);
	isAbsent(dict, 6);

	isPresent(dict, 22, "Mary");
	isPresent(dict, 4, "Stephen");
	isPresent(dict, 9, "Edward");
	isPresent(dict, 1, "William");
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 37, "Victoria");
	isPresent(dict, 42, "Elizabeth");
	isPresent(dict, -1, "Edward");
	
}


BOOST_AUTO_TEST_CASE(InsertNodes_DeleteOdd)
{
	Dict dict;

	insertTestData(dict);

	std::cout << "Displaying full tree: " << std::endl;

	dict.displayTree();

	dict.removeIf(BST::isOdd);

	isPresent(dict, 22, "Mary");
	isPresent(dict, 4, "Stephen");
	isAbsent(dict, 9);
	isAbsent(dict, 1);
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isAbsent(dict, 19);
	isAbsent(dict, 31);
	isAbsent(dict, 23);
	isAbsent(dict, 37);
	isPresent(dict, 42, "Elizabeth");
	isAbsent(dict, -1);

	std::cout << "Display the removal of odd nodes: " << std::endl;

	dict.displayTree();

}

BOOST_AUTO_TEST_CASE(InsertNodes_DeleteEven)
{
	Dict dict;

	insertTestData(dict);

	dict.removeIf(BST::isEven);


	isAbsent(dict, 22);
	isAbsent(dict, 4);
	isPresent(dict, 9, "Edward");
	isPresent(dict, 1, "William");
	isAbsent(dict, 0);
	isAbsent(dict, 24);
	isAbsent(dict, 26);
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 37, "Victoria");
	isAbsent(dict, 42);
	isPresent(dict, -1, "Edward");

	std::cout << "Display the removal of even nodes: " << std::endl;


	dict.displayTree();

}

BOOST_AUTO_TEST_CASE(InsertNodes_DeleteNegative)
{
	Dict dict;

	insertTestData(dict);
	dict.insert(-10, "Jeremy");
	dict.insert(-15, "Robin");
	dict.insert(-7, "Andrew");
	dict.removeIf(BST::isNegative);


	isPresent(dict, 22, "Mary");
	isPresent(dict, 4, "Stephen");
	isPresent(dict, 9, "Edward");
	isPresent(dict, 1, "William");
	isPresent(dict, 0, "Harold");
	isPresent(dict, 24, "James");
	isPresent(dict, 26, "Charles");
	isPresent(dict, 19, "Henry");
	isPresent(dict, 31, "Anne");
	isPresent(dict, 23, "Elizabeth");
	isPresent(dict, 37, "Victoria");
	isPresent(dict, 42, "Elizabeth");

	isAbsent(dict, -1);
	isAbsent(dict, -15);
	isAbsent(dict, -10);
	isAbsent(dict, -7);

	std::cout << "Display the removal of negative nodes: " << std::endl;

	dict.displayTree();

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
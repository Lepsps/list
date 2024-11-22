#include "list.h"
#include <gtest.h>


TEST(list, can_create_list)
{
	ASSERT_NO_THROW(list<int> lst);
}

TEST(list, can_create_list_with_positive_length)
{
	ASSERT_NO_THROW(list<int> l(1));
}

TEST(list, cant_create_list_with_negative_length)
{
	ASSERT_ANY_THROW(list<int> l(-1));
}

TEST(list, can_create_copied_list)
{
	list<int> l1(1);

	ASSERT_NO_THROW(list<int> l(l1));
}

TEST(list, copied_list_has_its_own_memory)
{
	list<int> l1(5);
	list<int> l2(l1);

	EXPECT_NE(l1.begin(), l2.begin());
}

TEST(list, copied_list_is_equal_to_source_one)
{
	list<int> l1(5);

	for (list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
		l1.at(it) = 10;
	list<int> l2(l1);

	for (list<int>::iterator it1 = l1.begin(), it2 = l2.begin(); it1 != l1.end() && it2 != l2.end(); ++it1, ++it2)
		ASSERT_EQ(l1.at(it1), l2.at(it2));
}

TEST(list, can_set_and_get_node)
{
	list<int> l1(5);

	for (list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
		l1.at(it) = 10;

	for (list<int>::iterator it1 = l1.begin(); it1 != l1.end(); ++it1)
		ASSERT_EQ(l1.at(it1), 10);
}

TEST(list, can_assign_lists)
{
	list<int> l1(5), l2(4);

	for (list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
		l1.at(it) = 10;

	l2 = l1;

	for (list<int>::iterator it2 = l2.begin(); it2 != l2.end(); ++it2)
		ASSERT_EQ(l2.at(it2), 10);
}

TEST(list, can_assign_list_to_itself)
{
	list<int> l1(5);

	l1 = l1;
	
	ASSERT_EQ(l1.get_size(),5);
}

TEST(list, list_is_equal_to_moved_one)
{
	list<int> l(5);
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
		l.at(it) = 10;

	list<int> l1;
	l1 = std::move(l);

	for (list<int>::iterator it2 = l1.begin(); it2 != l1.end(); ++it2)
		ASSERT_EQ(l1.at(it2),10);
}

TEST(list, moved_list_is_empty)
{
	list<int> l(5);
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it) 
		l.at(it) = 10;

	list<int> l2(std::move(l));

	ASSERT_EQ(l.begin(), nullptr);

}

TEST(list, can_push_element_back)
{
	list<int> l(1);
	list<int>::iterator it = l.begin();
	l.at(it) = 10;
	
	l.push_back(9);

	ASSERT_EQ(l.at(++it), 9);
}

TEST(list, can_pop_element_from_back)
{
	list<int> l(2);
	int size = 0,size1 = 0;
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
		size++;

	l.pop_back();

	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
		size1++;

	ASSERT_NE(size,size1);
}

TEST(list, can_pop_element_from_zero_list)
{
	list<int> l;

	ASSERT_ANY_THROW(l.pop_back());
}

TEST(list, can_clear_list)
{
	list<int> l(5);

	l.clear();

	ASSERT_EQ(l.begin(),nullptr );
}

TEST(list, check_non_empty_list)
{
	list<int> l(5);

	ASSERT_FALSE(l.empty());
}

TEST(list, check_empty_list)
{
	list<int> l;

	ASSERT_TRUE(l.empty());
}

TEST(list, can_get_size)
{
	list<int> l1(10);
	ASSERT_EQ(10, l1.get_size());
}

TEST(list, can_pop_element_from_front)
{
	list<int> l(5);
	list<int>::iterator it = l.begin();
	l.at(it) = 10;
	l.at(++it) = 9;

	l.pop_front();

	ASSERT_EQ(l.at(l.begin()), 9);
}

TEST(list, can_pop_element_from_empty_list)
{
	list<int> l;

	ASSERT_ANY_THROW(l.pop_front());
}

TEST(list, can_push_elemnt_front)
{
	list<int> l(5);

	l.push_front(10);

	ASSERT_EQ(l.at(l.begin()), 10);
}

TEST(list, can_insert_elemnt)
{
	list<int> l(5);
	list<int>::iterator it = l.begin();

	l.insert(10,it);
	
	ASSERT_EQ(l.at(++it), 10);
}

TEST(list, can_erase_element)
{
	list<int> l;
	l.push_front(3);
	list<int>::iterator it = l.begin();
	it = l.insert(2, it);
	l.insert(4, it);

	l.erase(l.begin());

	ASSERT_EQ(l.at(++l.begin()), 4);
}

TEST(list, can_find_element)
{
	list<int> l(5);
	int i = 0;
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
		l.at(it) = ++i;
	list<int>::iterator it1 = l.begin();
	it1++;

	ASSERT_EQ(l.find(2),it1);
}
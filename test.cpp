#include "pch.h"
#include "BST.h"
#include <exception>

BST global_tree;

TEST(TestCaseTree, Exception) {
	ASSERT_ANY_THROW(global_tree.contains(5));
	ASSERT_ANY_THROW(global_tree.remove(8));
	ASSERT_ANY_THROW(global_tree.create_bft_iterator());
	ASSERT_ANY_THROW(global_tree.create_dft_iterator());
}

TEST(TestCaseTree, Init) {
	ASSERT_ANY_THROW(global_tree.create_dft_iterator()); // Итератор выбрасывает исключение , что корень дерева равен nullptr,
	// что значит, что дерево инициализированно
}


TEST(TestCaseTree, Insert) {
	BST local_tree;  
	int elems[14] = { 13,9,16,5,10,14,20,4,6,12,15,19,11,18 };
	for (size_t i = 0; i < 14; i++) {
		local_tree.insert(elems[i]);
	}
	Iterator* iter = local_tree.create_bft_iterator();
	for (size_t i = 0; i < 14; i++) {
		ASSERT_TRUE(elems[i] == iter->next());
	}
	delete iter;
}

TEST(TestCaseTree, Contains){
	int sample_elems_in_tree[200];
	for (size_t i = 0; i < 200; i++) {
		sample_elems_in_tree[i] = rand() % 256;
		global_tree.insert(sample_elems_in_tree[i]);
	}
	for (size_t i = 0; i < 200; i++) {
		ASSERT_TRUE(global_tree.contains(sample_elems_in_tree[i]));
	}
	ASSERT_FALSE(global_tree.contains(300));
}


TEST(TestCaseTree, Remove) {
	// Рассмотрим все 3 случая: удаляемый элемент - лист; имеет одного потомка; имеет двух потомков
	BST local_tree;
	local_tree.insert(10);
	local_tree.insert(12);
	local_tree.insert(11);
	local_tree.insert(5);
	local_tree.insert(13);
	local_tree.insert(4);
	local_tree.insert(6);
	local_tree.remove(4); // случай один
	
	Iterator* iter = local_tree.create_bft_iterator();
	int elems_in_new_tree[6] = { 10,5,12,6,11,13 };
	for (size_t i = 0; i < 6; i++) {
		ASSERT_EQ(elems_in_new_tree[i], iter->next());
	}
	delete iter;

	local_tree.insert(4);
	local_tree.insert(8);
	local_tree.remove(6); // случай 2

	iter = local_tree.create_bft_iterator();
	int elems_in_new_tree_v2[7] = { 10,5,12,4,8,11,13 };
	for (size_t i = 0; i < 7; i++) {
		ASSERT_EQ(elems_in_new_tree_v2[i], iter->next());
	}
	delete iter;

	local_tree.insert(7);
	local_tree.insert(9);
	local_tree.remove(5); // случай 3

	iter = local_tree.create_bft_iterator();
	int elems_in_new_tree_v3[8] = { 10,7,12,4,8,11,13,9 }; 
	for (size_t i = 0; i < 8; i++) {
		ASSERT_EQ(elems_in_new_tree_v3[i], iter->next());
	}
	delete iter;
}




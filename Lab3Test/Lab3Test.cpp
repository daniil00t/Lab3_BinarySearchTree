#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3_BinaryTree/Additional.h"
#include "../Lab3_BinaryTree/BST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MAIN {
	int double_number(int x) {
		return x * 2;
	}
	int (*f_map)(int) = &double_number;

	int isBiggerThan(int x) {
		return x > 57 ? 1 : 0;
	}
	int (*f_where)(int) = &isBiggerThan;


	int Summ(int x1, int x2) {
		return 2 * x1 + x2;
	}
	int (*f_reduce)(int, int) = &Summ;
}


namespace Lab3Test
{
	TEST_CLASS(BinarySearchTree)
	{
	private:
		MAIN::BST<int> GetTree() {
			MAIN::BST<int> tree;
			tree.Insert(50);
			tree.Insert(55);
			tree.Insert(45);
			tree.Insert(77);
			tree.Insert(48);
			tree.Insert(53);
			tree.Insert(90);
			tree.Insert(100);
			tree.Insert(110);
			return tree;
		}
		
	public:
		



		TEST_METHOD(Insert)
		{
            MAIN::BST<int> tree = GetTree();

            Assert::IsTrue(tree.give_root()->key == 50);
            Assert::IsTrue(tree.give_root()->left->key == 45);
            Assert::IsTrue(tree.give_root()->right->key == 55);
            Assert::IsTrue(tree.give_root()->right->right->key == 77);
            Assert::IsTrue(tree.give_root()->right->left->key == 53);

            tree.Insert(60);
            Assert::IsTrue(tree.find_branch(77)->left->key == 60);
		}
		TEST_METHOD(Remove)
		{
			MAIN::BST<int> tree = GetTree();

			tree.Remove(55);
			Assert::IsTrue(tree.give_root()->right->key == 77);
			Assert::IsTrue(tree.give_root()->right->left->key == 53);
		}

		TEST_METHOD(FIND) {
			MAIN::BST<int> tree = GetTree();
			Assert::IsTrue(tree.Find(100) == 1);
			Assert::IsTrue(tree.Find(90) == 1);
			Assert::IsTrue(tree.Find(77) == 1);
			Assert::IsTrue(tree.Find(45) == 1);
		}
		

		TEST_METHOD(MAP) {
			
			//int (*f_map)(int) = &double_number;

			MAIN::BST<int> tree = GetTree();

			MAIN::BST<int> tree1 = tree.Map(MAIN::f_map);
			//Multyplying by 2
			Assert::IsTrue(tree1.find_branch(100));
			Assert::IsTrue(tree1.find_branch(200));
			Assert::IsTrue(tree1.find_branch(90));
			Assert::IsTrue(tree1.find_branch(106));
		}

		TEST_METHOD(WHERE) {
			MAIN::BST<int> tree = GetTree();
			MAIN::BST<int> tree1 = tree.Where(MAIN::f_where);

			//                 110
			//           100
			//      90
			// 77

			Assert::IsTrue(tree1.give_root()->key == 77);
			Assert::IsTrue(tree1.give_root()->right->key == 90);
			Assert::IsTrue(tree1.give_root()->right->right->key == 100);
		}

		TEST_METHOD(REDUCE) {
			MAIN::BST<int> tree = GetTree();
			Assert::IsTrue(tree.Reduce(MAIN::f_reduce, 10) == 1266);
		}
		TEST_METHOD(THREADING_AND_TO_STRING) {
			MAIN::BST<int> tree = GetTree();
			Assert::IsTrue(tree.toString("NLR") == "50 45 48 55 53 77 90 100 110");
			Assert::IsTrue(tree.toString("NRL") == "50 55 77 90 100 110 53 45 48");
			Assert::IsTrue(tree.toString("RNL") == "110 100 90 77 55 53 50 48 45");
			Assert::IsTrue(tree.toString("RLN") == "110 100 90 77 53 55 48 45 50");
			Assert::IsTrue(tree.toString("LNR") == "45 48 50 53 55 77 90 100 110");
			Assert::IsTrue(tree.toString("LRN") == "48 45 53 110 100 90 77 55 50");
		}
		TEST_METHOD(BALANCING) {
			MAIN::BST<int> tree = GetTree();
			Assert::IsTrue(tree.IsBalanced() == 0);
			tree.Balancing();
			Assert::IsTrue(tree.IsBalanced() == 1);
		}
		
		TEST_METHOD(GET_SUB_TREE) {
			MAIN::BST<int> tree = GetTree();
			MAIN::BST<int> tree1 = tree.GetSubTree(55);
			Assert::IsTrue(tree1.give_root()->key == 55);
			Assert::IsTrue(tree1.give_root()->right->key == 77);
			Assert::IsTrue(tree1.give_root()->left->key == 53);
		}
		TEST_METHOD(FIND_SUB_TREE) {
			MAIN::BST<int> tree = GetTree();
			MAIN::BST<int> tree1 = tree.GetSubTree(55);
			MAIN::BST<int> tree2 = tree.GetSubTree(55);
			tree2.Insert(44);
			Assert::IsTrue(tree.FindSubTree(tree1) == 1);
			Assert::IsTrue(tree.FindSubTree(tree2) == 0);
		}


	};
}

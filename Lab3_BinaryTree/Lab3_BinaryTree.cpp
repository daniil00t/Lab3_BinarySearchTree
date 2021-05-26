#include <iostream>

#include "BST.h"

//#include "BinarySearchTree.h"
//#include "Interface.h"

using namespace std;
//using namespace MAIN;

/*
* 
* Global TODO:
* 
* 1. Main class - BinTree                                       | - |
* 2. Console Interface                                          | - |
* 3. Tests                                                      | - |
* 4. Class for view optimisation                                | - |
* 5. WINAPI - Charts and implementation optimise view class     | - |
* 
*/

template <typename T>
T map_func(T x) {
    return x * 2;
}

template <typename T>
int where_func(T x) {
    return x > 20;
}

template <typename T>
T reduce_func(T x, T y) {
    return x + y;
}



int main()
{
    MAIN::BST<int> bst;
    bst.Add(10);
    bst.Add(5);
    bst.Add(8);
    bst.Add(4);

    bst.Print();

    bst.Remove(5);
    bst.Remove(4);
    bst.Remove(10);

    

    cout << bst.Find(4) << bst.Find(8);

    MAIN::BST<int> bst1(bst);

    bst1.Print();

    cout << "===========================================================\n";
    bst.Add(10);
    bst.Add(11);
    bst.Add(12);
    bst.Add(13);

    cout << bst.IsBalanced() << endl;
    bst.newBalancing();
    cout << bst.IsBalanced() << endl;
    bst.Print();

    cout << "===========================================================\n";

    MAIN::BST<int> bst2;
    bst2 = bst.Map(&map_func);

    bst2 = bst2.Where(&where_func);

    bst2.Print();

    cout << bst2.Reduce(&reduce_func, 0);

    cout << "===========================================================\n";

    MAIN::BST<int> bst3;
    bst3 = bst.GetSubTree(10);
    bst3.Print();

    cout << bst.FindSubTree(bst2);
    cout << "===========================================================\n";

    cout << bst.toString("LNR");

    return 0;
}

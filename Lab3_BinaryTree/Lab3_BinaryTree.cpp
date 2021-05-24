#include <iostream>
#include "BinarySearchTree.h"

using namespace std;
using namespace MAIN;

/*
* 
* Global TODO:
* 
* 1. Main class - BinTree                                       | + |
* 2. Tests                                                      |   |
* 3. Class for view optimisation                                |   |
* 4. WINAPI - Charts and implementation optimise view class     |   |
* 
*/

int main()
{

    //BinTree<int> bt(8, 5, 2, 6, 10, 9, 11);
    BinTree<int> bt;


    // Build OP's tree
    bt.insert(8);
    bt.insert(5);
    bt.insert(2);
    bt.insert(6);
    bt.insert(10);
    bt.insert(9);


    cout << "Tree from OP:\n\n";
    //bt.Delete(10);
    bt.Print();

    
    //cout << "Tree from OP:\n\n";
    //bt.Print();

    //cout << bt.isBalanced();



    return 0;
}

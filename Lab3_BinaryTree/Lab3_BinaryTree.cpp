#include <iostream>
#include "BinarySearchTree.h"
#include "BinarySearchTreeUpgrade.h"

using namespace std;
using namespace MAIN;

int main()
{

    BinTree<int> bt;

    bt.insert(8, 100);
    bt.insert(5, 140);
    bt.insert(2, 150);
    bt.insert(6, 170);
    bt.insert(10, 50);
    bt.insert(9, 80);
    bt.insert(11, 73);
    bt.insert(13, 53);
    bt.insert(64, 6);

    // Build OP's tree
    //bt.insert(8, 5, 2, 6, 10, 9, 11);
    cout << "Tree from OP:\n\n";
    bt.Print();

    cout << bt.Find(64);
    cout << "\n\n";


    return 0;
}

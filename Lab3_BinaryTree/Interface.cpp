#include "Interface.h"

// Test data:

// 1. function for map
template<typename T>
T map_func(T x) {
	return x + x;
}

// 2. function for reduce - summ all items
template<typename T>
T reduce_func(T x, T y) {
	return x + y;
}

// 3. frunction for where - checking for alpha
template<typename T>
int where_func(T x) {
	int alpha = 10;
	return x > alpha;
}


template<typename T>
MAIN::BST<T> switchCommand() {
	MAIN::BST<T> bst;

	while (true) {

		// Commands:

		cout << "========================== Switch Command ==========================" << endl;

		cout << "\t print		- printing tree" << endl;
		cout << "\t add		- insert item to tree" << endl;
		cout << "\t delete		- delete item from tree" << endl;
		cout << "\t find		- find item in tree" << endl;
		cout << "\t map		- map method tree" << endl;
		cout << "\t reduce		- reduce method tree" << endl;
		cout << "\t where		- where method tree" << endl;
		cout << "\t getsub		- get subTree in the tree" << endl;
		cout << "\t findsub	- find subTre in the tree" << endl;
		cout << "\t tostring	- tree to string" << endl;
		cout << "\t balance	- balancing tree" << endl;
		cout << "\t balanced?	- checking for balancing tree" << endl;
		cout << "\t changeT	- change type of tree" << endl;
		cout << "\t exit		- exit the menu" << endl;
		
		cout << "====================================================================" << endl;

		string command;

		cout << "insert command: ";
		cin >> command;

		if (command == "exit") {
			break;
		}
		else if (command == "print") {
			bst.Print();
		}
		else if (command == "add") {
			T item;
			cout << "Input value: ";
			cin >> item;
			bst.Insert(item);
		}
		else if (command == "delete") {
			T key;
			cout << "Input key: ";
			cin >> key;
			bst.Remove(key);
		}
		else if (command == "find") {
			T key;
			cout << "Input key: ";
			cin >> key;
			if (bst.Find(key)) cout << "Item has finded! " << endl;
			else cout << "Item hasn't finded " << endl;
		}
		else if (command == "map") {
			bst = bst.Map(&map_func);
		}
		else if (command == "where") {
			cout << "Checking: item of tree > __alpha__" << endl;

			//bst = bst.Where(&where_func);
		}
		else if (command == "reduce") {
			T start_element;
			cout << "Summ all items of the tree" << endl;
			cout << "Input start value: ";
			cin >> start_element;
			cout << bst.Reduce(&reduce_func, start_element) << endl;
		}
		else if (command == "getsub") {
			T key;
			cout << "Input key: ";
			cin >> key;
			bst.GetSubTree(key).Print();
		}
		else if (command == "tostring") {
			string str;
			cout << "Input sequence of elements {N|L|R}";
			cin >> str;
			cout << bst.toString(str) << endl;
		}
		else if (command == "balance") {
			bst.Balancing();
		}
		else if (command == "balanced?") {
			if(bst.IsBalanced()) cout << "Tree is balanced." << endl;
			else cout << "Tree isn't balanced." << endl;
		}
		else if (command == "changeT") {
			Menu();
		}
		else {
			break;
		}
	}
	return bst;
}



void Menu() {
	string type;

	cout << "=========================== Switch Type ==========================" << endl;

	cout << "\t int" << endl;
	cout << "\t double" << endl;
	cout << "\t string" << endl;
	cout << "\t complex" << endl;
	cout << "\t exit" << endl;

	cout << "====================================================================" << endl;

	cout << "Insert type: ";
	cin >> type;
	

	if (type == "exit") exit(0);
	else if (type == "int") switchCommand<int>();
	else if(type == "double") switchCommand<double>();
	else if(type == "string") switchCommand<string>();
	else if(type == "complex") switchCommand<complex<double>>();
	else exit(0);
}
#pragma once

#include <algorithm>
#include <list>
#include <stack>
#include <iterator>
#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include <complex>
#include <sstream>
#include <vector>
#include <fstream>

#include "Additional.h"

using namespace std;

/*
*
* TODO:
* 1. Basic operations: insert, search, delete            | + |
* 2. Load balancing                                      | + |
* 3. map, reduce, where                                  | + |
* 4. Treading                                            | + |
*   4.1. by fixed traversal                              | + |
*   4.2. by specified by the method parameter traversal  | + |
* 5. Saving to a string                                  | + |
*   5.1. by fixed traversal                              | + |
*   5.2. by pecified by the formatting string            | + |
* 6. Extracting the subtree (by the specified root)      | + |
* 7. Search for the occurrence of a subtree              | + |
*
*/



namespace MAIN {
	template <class T>
	class BST {
	private:
        struct Node {
            // main data for node of tree
            T key;
            Node* left, * right;

            // constructor for default values
            Node() : left(nullptr), right(nullptr) {}
            // constructors for key
            Node(const T& key) : key(key), left(nullptr), right(nullptr) {}

            // destructor
            // !- commented because testes returned exceptions -!
            //~Node() { delete left; delete right; }
            int max_depth() const {
                const int left_depth = left ? left->max_depth() : 0;
                const int right_depth = right ? right->max_depth() : 0;
                return (left_depth > right_depth ? left_depth : right_depth) + 1;
            }
        };
        struct cell_display {
            string   valstr;
            bool     present;
            cell_display() : present(false) {}
            cell_display(std::string valstr) : valstr(valstr), present(true) {}
        };

        /*
        * Additional methods for printing the entire tree-calculates all
        * the distances between nodes and displays everything in the desired order
        */

        using display_rows = vector<vector<cell_display>>;
        display_rows get_row_display() const {
            // start off by traversing the tree to
            // build a vector of vectors of Node pointers
            vector<Node*> traversal_stack;
            vector< std::vector<Node*> > rows;
            if (!root) return display_rows();

            Node* p = root;
            const int max_depth = root->max_depth();
            rows.resize(max_depth);
            int depth = 0;
            for (;;) {
                // Max-depth Nodes are always a leaf or null
                // This special case blocks deeper traversal
                if (depth == max_depth - 1) {
                    rows[depth].push_back(p);
                    if (depth == 0) break;
                    --depth;
                    continue;
                }

                // First visit to node?  Go to left child.
                if (traversal_stack.size() == depth) {
                    rows[depth].push_back(p);
                    traversal_stack.push_back(p);
                    if (p) p = p->left;
                    ++depth;
                    continue;
                }

                // Odd child count? Go to right child.
                if (rows[depth + 1].size() % 2) {
                    p = traversal_stack.back();
                    if (p) p = p->right;
                    ++depth;
                    continue;
                }

                // Time to leave if we get here

                // Exit loop if this is the root
                if (depth == 0) break;

                traversal_stack.pop_back();
                p = traversal_stack.back();
                --depth;
            }

            // Use rows of Node pointers to populate rows of cell_display structs.
            // All possible slots in the tree get a cell_display struct,
            // so if there is no actual Node at a struct's location,
            // its boolean "present" field is set to false.
            // The struct also contains a string representation of
            // its Node's key, created using a std::stringstream object.
            display_rows rows_disp;
            std::stringstream ss;
            for (const auto& row : rows) {
                rows_disp.emplace_back();
                for (Node* pn : row) {
                    if (pn) {
                        ss << pn->key;
                        rows_disp.back().push_back(cell_display(ss.str()));
                        ss = std::stringstream();
                    }
                    else {
                        rows_disp.back().push_back(cell_display());
                    }
                }
            }
            return rows_disp;
        }
        vector<string> row_formatter(const display_rows& rows_disp) const {
            using s_t = string::size_type;

            // First find the maximum key string length and put it in cell_width
            s_t cell_width = 0;
            for (const auto& row_disp : rows_disp) {
                for (const auto& cd : row_disp) {
                    if (cd.present && cd.valstr.length() > cell_width) {
                        cell_width = cd.valstr.length();
                    }
                }
            }

            // make sure the cell_width is an odd number
            if (cell_width % 2 == 0) ++cell_width;

            // formatted_rows will hold the results
            vector<string> formatted_rows;

            // some of these counting variables are related,
            // so its should be possible to eliminate some of them.
            s_t row_count = rows_disp.size();

            // this row's element count, a power of two
            s_t row_elem_count = 1 << (row_count - 1);

            // left_pad holds the number of space charactes at the beginning of the bottom row
            s_t left_pad = 0;

            // Work from the level of maximum depth, up to the root
            // ("formatted_rows" will need to be reversed when done) 
            for (s_t r = 0; r < row_count; ++r) {
                const auto& cd_row = rows_disp[row_count - r - 1]; // r reverse-indexes the row
                // "space" will be the number of rows of slashes needed to get
                // from this row to the next.  It is also used to determine other
                // text offsets.
                s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
                // "row" holds the line of text currently being assembled
                string row;
                // iterate over each element in this row
                for (s_t c = 0; c < row_elem_count; ++c) {
                    // add padding, more when this is not the leftmost element
                    row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
                    if (cd_row[c].present) {
                        // This position corresponds to an existing Node
                        const string& valstr = cd_row[c].valstr;
                        // Try to pad the left and right sides of the value string
                        // with the same number of spaces.  If padding requires an
                        // odd number of spaces, right-sided children get the longer
                        // padding on the right side, while left-sided children
                        // get it on the left side.
                        s_t long_padding = cell_width - valstr.length();
                        s_t short_padding = long_padding / 2;
                        long_padding -= short_padding;
                        row += string(c % 2 ? short_padding : long_padding, ' ');
                        row += valstr;
                        row += string(c % 2 ? long_padding : short_padding, ' ');
                    }
                    else {
                        // This position is empty, Nodeless...
                        row += string(cell_width, ' ');
                    }
                }
                // A row of spaced-apart value strings is ready, add it to the result vector
                formatted_rows.push_back(row);

                // The root has been added, so this loop is finsished
                if (row_elem_count == 1) break;

                // Add rows of forward- and back- slash characters, spaced apart
                // to "connect" two rows' Node value strings.
                // The "space" variable counts the number of rows needed here.
                s_t left_space = space + 1;
                s_t right_space = space - 1;
                for (s_t sr = 0; sr < space; ++sr) {
                    string row;
                    for (s_t c = 0; c < row_elem_count; ++c) {
                        if (c % 2 == 0) {
                            row += string(c ? left_space * 2 + 1 : left_space, ' ');
                            row += cd_row[c].present ? '/' : ' ';
                            row += string(right_space + 1, ' ');
                        }
                        else {
                            row += string(right_space, ' ');
                            row += cd_row[c].present ? '\\' : ' ';
                        }
                    }
                    formatted_rows.push_back(row);
                    ++left_space;
                    --right_space;
                }
                left_pad += space + 1;
                row_elem_count /= 2;
            }

            // Reverse the result, placing the root node at the beginning (top)
            std::reverse(formatted_rows.begin(), formatted_rows.end());

            return formatted_rows;
        }
        static void trim_rows_left(vector<string>& rows) {
            if (!rows.size()) return;
            auto min_space = rows.front().length();
            for (const auto& row : rows) {
                auto i = row.find_first_not_of(' ');
                if (i == string::npos) i = row.length();
                if (i == 0) return;
                if (i < min_space) min_space = i;
            }
            for (auto& row : rows) {
                row.erase(0, min_space);
            }
        }

        int get_max_depth() const { return root ? root->max_depth() : 0; }

        // GENERAL ADD FUNCTIONS
        void copy(const Node* s_branch, Node*& _branch) {
            if (!s_branch) return;
            _branch = new Node;
            _branch->key = s_branch->key;
            _branch->left = 0;
            _branch->right = 0;
            copy(s_branch->left, _branch->left);
            copy(s_branch->right, _branch->right);
            return;
        }
        void CPY(Node*& _branch) {
            copy(_branch, root);
        }

        Node* findparent(Node*& node, T key) {
            if (node == NULL) {
                return NULL; // empty
            }

            if (key == GetKey(node->left) || key == GetKey(node->right)) {
                return node;
            }
            else if (key < node->key) {
                findparent(node->left, key);

            }
            else {
                findparent(node->right, key);
            }
        }
        T GetKey(Node* node) {
            if (node) {
                return node->key;
            }
            else {
                return 0;
            }
        }
        Node* ShowParent(T key) {
            if (key == root->key) {
                return NULL;
            }
            else return findparent(root, key);
        }
        

        // MAIN ADD FUNCTIONS
        void add(Node*& node, const T key) {
            if (!node) {
                node = new Node;
                node->key = key;
                node->left = 0;
                node->right = 0;
                return;
            }
            else {
                if (node->key > key) {
                    add(node->left, key);
                }
                else {
                    add(node->right, key);
                }
            }
        }
        void remove(Node*& node, T key) {
            if (node == NULL)
                return;

            if (key == node->key) {

                Node* tempNode;
                if (node->right == NULL) {
                    tempNode = node->left;
                }
                else {
                    Node* ptr = node->right;
                    if (ptr->left == NULL) {
                        ptr->left = node->left;
                        tempNode = ptr;
                    }
                    else {

                        Node* pmin = ptr->left;
                        while (pmin->left != NULL) {
                            ptr = pmin;
                            pmin = ptr->left;
                        }
                        ptr->left = pmin->right;
                        pmin->left = node->left;
                        pmin->right = node->right;
                        tempNode = pmin;
                    }
                }

                delete node;
                node = tempNode;
                return;
            }
            else if (key < node->key)
                remove(node->left, key);
            else
                remove(node->right, key);
            return;
        }
        Node* find(Node*& node, T key) {
            if (node == NULL)
                return NULL; // empty

            if (key == node->key) {
                return node;
            }
            else if (key < node->key)
                find(node->left, key);
            else
                find(node->right, key);
        }
        
        // BALANCING ADD FUNCTIONS
        bool is_balanced(Node* root)
        {
            int lh; /* for height of left subtree */
            int rh; /* for height of right subtree */

            /* If tree is empty then return true */
            if (root == NULL)
                return 1;

            /* Get the height of left and right sub trees */
            lh = height(root->left);
            rh = height(root->right);

            if (abs(lh - rh) <= 1 && is_balanced(root->left) && is_balanced(root->right))
                return 1;

            /* If we reach here then
            tree is not height-balanced */
            return 0;
        }
        int height(Node* node)
        {
            /* base case tree is empty */
            if (node == NULL)
                return 0;

            /* If tree is not empty then
            height = 1 + max of left
                height and right heights */
            return 1 + max(height(node->left),
                height(node->right));
        }
        void toList() {
            Node* parent = this->root;
            while (parent != nullptr) {
                if (parent->left != nullptr) {
                    this->RotateRight(parent);
                    Node* newparent = this->ShowParent(parent->key);
                    parent = newparent;
                }
                else {
                    parent = parent->right;
                }
            }
        }
        void MakeRotations(int count) {
            Node* parent = this->root;
            Node* child = this->root->right;
            for (; count > 0; count--)
            {
                if (child != nullptr)
                {
                    this->RotateLeft(parent);
                    parent = child->right;
                    if (parent == nullptr)
                        break;
                    child = parent->right;
                }
                else
                    break;
            }
        }
        void RotateLeft(Node* parent) {
            Node* right_child = parent->right;
            if (this->ShowParent(parent->key) != nullptr) {
                this->ShowParent(parent->key)->right = right_child;
            }
            else
                this->root = right_child;
            parent->right = right_child->left;
            right_child->left = parent;
        }
        void RotateRight(Node* parent) {
            Node* left_child = parent->left;
            if (this->ShowParent(parent->key) != nullptr) {
                this->ShowParent(parent->key)->right = left_child;
            }
            else
                this->root = left_child;
            parent->left = left_child->right;
            left_child->right = parent;
        }


        // MAP - REDUCE - WHERE
        void Inorder(BST<T>* tree, vector<T> array, int left, int right) {
            if (left > right) return;
            int j = (left + right) / 2;
            tree->Insert(array[j]);
            Inorder(tree, array, left, j - 1);
            Inorder(tree, array, j + 1, right);
        }
        void Preorder(BST<T>* tree, vector<T> array) {
            for (int i = 0; i < array.size(); i++)
                tree->Insert(array[i]);
        }
        void Postorder(BST<T>* tree, vector<T> array) {
            for (int i = array.size() - 1; i >= 0; i--)
                tree->Insert(array[i]);
        }

        // FIND SUBTREE
        bool areIdentical(Node* root1, Node* root2) {
            /* base cases */
            if (root1 == NULL && root2 == NULL)
                return true;

            if (root1 != NULL && root2 != NULL)
                if (root1->key == root2->key && areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right))
                    return true;
            return false;
        }
        bool isSubtree(Node* node, Node* sub_node) {
            /* base cases */
            if (sub_node == NULL) return true;

            if (node == NULL) return false;

            /* Check the tree with root as current node */
            if (areIdentical(node, sub_node)) return true;

            /* If the tree with root as current
            node doesn't match then try left
            and right subtrees one by one */
            return isSubtree(node->left, sub_node) ||
                isSubtree(node->right, sub_node);
        }

        // DATA
        Node* root;

    public:
        ///////////////////////////////////////////////////////////////////////
        // Constructors and destructors
        ///////////////////////////////////////////////////////////////////////

        // empty cosntructor
        BST() : root(nullptr) {}
        BST(const T& key) {
            root = new Node;
            root->key = key;
            root->left = 0;
            root->right = 0;
        }
        BST(const Node* node) {
            copy(node, root);
        }
        BST(const BST<T>& bst): BST() {
            copy(bst.root, root);
        }
        
        ~BST() { delete root; }
        void clear() { delete root; root = nullptr; }

        ///////////////////////////////////////////////////////////////////////
        // Main Functions (scores: 5)
        ///////////////////////////////////////////////////////////////////////

        void Insert(const T key) {
            add(root, key);
        }
        void Remove(T key) {
            if (!root) {
                return;
            }
            remove(root, key);
        }
        bool Find(T key) {
            if (!root) {
                cout << "Tree doesn't exist" << endl;
                return false;
            }
            else {
                Node* temp = find(root, key);
                if (!temp)
                    return false;
                else
                    return true;

            }
        }

        ///////////////////////////////////////////////////////////////////////
        // Balancing (scores: 2)
        ///////////////////////////////////////////////////////////////////////

        bool IsBalanced() {
            return is_balanced(root);
        }
        void Balancing() {
            if (this->IsBalanced() == 1) { return; }
            this->toList();
            int n = 0;
            for (Node* tmp = this->root; tmp != nullptr; tmp = tmp->right)
                n++;
            //m = 2^floor[log2(n+1)]-1
            int m = (1 << int(log2(n + 1))) - 1;
            this->MakeRotations(n - m);
            while (m > 1)
                this->MakeRotations(m /= 2);
        }

        ///////////////////////////////////////////////////////////////////////
        // Map, Reduce, Where (scores: 3)
        ///////////////////////////////////////////////////////////////////////

        Node* map(Node* node, T(*mapper)(T)) {
            if (!node) return NULL;

            node->key = mapper(node->key);
            cout << node->key;
            if (node->left == nullptr && node->right == nullptr) return NULL;
            if (node->left != nullptr) map(node->left, mapper);
            if (node->right != nullptr) map(node->right, mapper);

        }
        BST<T> Map(T(*mapper)(T)) {
            BST<T> bst(root);
            if (!root) return bst;

            map(bst.root, mapper);

            return bst;
        }

        void where(int(*func)(T), Node*& node) {
            if (!func(node->key)) {
                remove(node, node->key);
                if (!node) return;
                where(func, node);
                return;
            }

            if (node->left == nullptr && node->right == nullptr) {
                return;
            }
            if (node->left != nullptr) {
                where(func, node->left);
            }
            if (node->right != nullptr) {
                where(func, node->right);
            }
        }
        BST<T> Where(int (*func)(T)) {
            BST<T> binTree(root);
            if (!root) {
                return binTree;
            }
            where(func, binTree.root);
            return binTree;
        }

        T Reduce(T(*func)(T, T), T start) {
            if (!root) {
                return 0;
            }
            list<Node>* list = this->Threading("LNR");
            T result;
            auto list_front = list->begin();
            result = func(list_front->key, start);
            advance(list_front, 1);
            for (size_t i = 1; i < list->size(); i++) {
                result = func(list_front->key, result);
                advance(list_front, 1);
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////
        // Thread tree (scores: 3 + 4)
        ///////////////////////////////////////////////////////////////////////

        list<Node>* Threading(string method) {
            list<Node>* list = new ::list<Node>;
            if (!root) {
                return list;
            }
            tothread(root, list, method);
            return list;
        }
        void tothread(Node*& node, list<Node>* list, string method) {
            using pair = pair<Node*, bool>;
            stack<pair> stack;
            stack.push(pair{ node, false });
            string round_name = method;
            reverse(round_name.begin(), round_name.end());
            while (!stack.empty()) {
                pair current_node = stack.top();
                stack.pop();
                if (current_node.second)
                    list->push_back(*current_node.first);
                else {
                    if (current_node.first == nullptr)
                        continue;
                    for (auto ch : round_name)
                        switch (ch) {
                        case 'N':
                            stack.push(pair{ current_node.first, true });
                            break;
                        case 'L':
                            stack.push(pair{ current_node.first->left, false });
                            break;
                        case 'R':
                            stack.push(pair{ current_node.first->right, false });
                            break;
                        }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // Get subTree by key (scores: 2)
        ///////////////////////////////////////////////////////////////////////

        BST<T> GetSubTree(T key) {
            BST<T> binTree;
            if (!root) {
                return binTree;
            }
            copy(find(root, key), binTree.root);
            return binTree;
        }

        ///////////////////////////////////////////////////////////////////////
        // Search for the occurrence of a subtree (scores: 3)
        ///////////////////////////////////////////////////////////////////////
       

        bool FindSubTree(BST<T> sub_tree) {
            return isSubtree(root, sub_tree.root);
        }

        ///////////////////////////////////////////////////////////////////////
        // Saving to a string  (scores: 1 + 3)
        ///////////////////////////////////////////////////////////////////////

        string toString(string method) {
            string str;
            if (!root) {
                std::cout << "Tree is empty" << std::endl;
                return str;
            }
            list<Node>* list = this->Threading(method);
            auto list_front = list->begin();
            for (int i = 0; i < list->size(); i++) {
                str += to_string(list_front->key);
                if (i < list->size() - 1) {
                    str += " ";
                }
                advance(list_front, 1);
            }
            return str;
        }

        ///////////////////////////////////////////////////////////////////////
        // Other Functions for more confortable use
        ///////////////////////////////////////////////////////////////////////
        Node* give_root() {
            return root;
        }
        Node* find_branch(T key) {
            return find(root, key);
        }
        // Print the tree to cout
        void Print() const {
            const int d = get_max_depth();

            // If this tree is empty, tell someone
            if (d == 0) {
                cout << " <empty tree>\n";
                return;
            }

            // This tree is not empty, so get a list of node values...
            const auto rows_disp = get_row_display();
            // then format these into a text representation...
            auto formatted_rows = row_formatter(rows_disp);
            // then trim excess space characters from the left sides of the text...
            trim_rows_left(formatted_rows);
            // then dump the text to cout.
            for (const auto& row : formatted_rows) {
                std::cout << ' ' << row << '\n';
            }
        }

        // Overloading operators
        void operator=(BST<T> bst) {
            copy(bst.root, root);
        }
	};
}

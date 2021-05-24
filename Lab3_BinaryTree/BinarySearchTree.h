#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <limits>

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

    template <typename T>
    class BinTree {
    private:
        struct Node {
            // main data for node of tree
            T key;
            Node* left, *right;
            
            // constructor for default values
            Node() : left(nullptr), right(nullptr) {}
            // constructors for key
            Node(const T& key) : key(key), left(nullptr), right(nullptr) {}

            // destructor
            ~Node() { delete left; delete right; }
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

        // Additional private functions for main methods
        void singleRightRotate(Node* parent)
        {
            Node* left_child = parent->left;
            if (this->Parent(parent->key) != nullptr) {
                this->Parent(parent->key)->left = left_child;
            }
            else this->root = left_child;
            parent->left = left_child->right;
            left_child->right = parent;
        }

        void singleLeftRotate(Node* parent)
        {
            Node* right_child = parent->right;
            if (this->Parent(parent->key) != nullptr) {
                this->Parent(parent->key)->right = right_child;
            }
            else this->root = right_child;
            parent->right = right_child->left;
            right_child->left = parent;
        }

        void multiRotate(int count) {
            Node* parent = this->root;
            Node* child = this->root->right;
            for (; count > 0; count--)
            {
                if (child != nullptr)
                {
                    this->singleLeftRotate(parent);
                    parent = child->right;
                    if (parent == nullptr)
                        break;
                    child = parent->right;
                }
                else
                    break;
            }
        }

        Node* findMin(Node* t)
        {
            if (t == NULL)
                return NULL;
            else if (t->left == NULL)
                return t;
            else
                return findMin(t->left);
        }

        Node* findMax(Node* t)
        {
            if (t == NULL)
                return NULL;
            else if (t->right == NULL)
                return t;
            else
                return findMax(t->right);
        }

        Node* getParent(Node*& node, T key) {
            if (node == nullptr) return NULL;
            if (key == node->left->key || key == node->right->key) return node;
            else if (key > node->key) getParent(node->right, key);
            else getParent(node->left, key);
        }
        
        Node Parent(T key) {
            if (key == root->key) return NULL;
            else return getParent(root, key);
        }

        void cpy(const Node* fromNode, Node* toNode) {
            if (!toNode) return;
            Node* node = new Node();
            node->key = root->key;
            node->left = root->left;
            node->right = root->right;
            cpy(fromNode, node->left);
            cpy(fromNode, node->right);
        }

        Node* search(Node* _root, T key) {
            if (!_root)
                return NULL;
            else if (key < _root->key)
                return search(_root->left, key);
            else if (key > _root->key)
                return search(_root->right, key);
            else
                return _root;
        }
        Node* root;

    public:
        // emtpty cosntructor
        BinTree() : root(nullptr) {}

        // construtor for count elements
        template <typename ...Args>
        BinTree(const T& key, Args...more) { this->insert(key, more...); }

        ~BinTree() { delete root; }
        void clear() { delete root; root = nullptr; }

        ///////////////////////////////////////////////////////////////////////
        // Main Functions (scores: 5)
        ///////////////////////////////////////////////////////////////////////

        bool Find(T key) {
            Node* finded = this->search(root, key);
            if (!!finded) return true;
            else false;
        }

        void insert() {}

        template <typename ...Args>
        void insert(const T& key, Args...more) {
            if (!root) {
                root = new Node(key);
            }
            else {
                Node* p = root;
                for (;;) {
                    if (key == p->key) return;
                    Node*& pchild = key < p->key ? p->left : p->right;
                    if (!pchild) {
                        pchild = new Node(key);
                        break;
                    }
                    p = pchild;
                }
            }
            insert(more...);
        }

        /* Given a binary search tree and a key, this function
           deletes the key and returns the new root */
        Node* deleteNode(Node* root, T key)
        {
            // Base case
            if (root == NULL)
                return root;

            // Recursive calls for ancestors of
            // node to be deleted
            if (root->key > key) {
                root->left = deleteNode(root->left, key);
                return root;
            }
            else if (root->key < key) {
                root->right = deleteNode(root->right, key);
                return root;
            }

            // We reach here when root is the node
            // to be deleted.

            // If one of the children is empty
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // If both children exist
            else {

                Node* succParent = root;

                // Find successor
                Node* succ = root->right;
                while (succ->left != NULL) {
                    succParent = succ;
                    succ = succ->left;
                }

                // Delete successor.  Since successor
                // is always left child of its parent
                // we can safely make successor's right
                // right child as left of its parent.
                // If there is no succ, then assign
                // succ->right to succParent->right
                if (succParent != root)
                    succParent->left = succ->right;
                else
                    succParent->right = succ->right;

                // Copy Successor Data to root
                root->key = succ->key;

                // Delete Successor and return root
                delete succ;
                return root;
            }
        }
        void Delete(T key) { this->deleteNode(root, key); }
        

        ///////////////////////////////////////////////////////////////////////
        // Balance (scores: 2)
        ///////////////////////////////////////////////////////////////////////

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

        bool isBalanced(Node* root)
        {
            int lh; 
            int rh; 

            /* If tree is empty then return true */
            if (root == NULL)
                return 1;

            /* Get the height of left and right sub trees */
            lh = height(root->left);
            rh = height(root->right);

            if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
                return 1;

            /* If we reach here then
            tree is not height-balanced */
            return 0;
        }

        bool isBalanced() { return this->isBalanced(root); }

        void Balance() {
            if (this->IsBalanced() == 1) { cout << "Tree is already balanced" << endl; return; }
            this->toThread();
            int n = 0;
            for (Node* tmp = this->root; tmp != nullptr; tmp = tmp->right)
                n++;
            int m = (1 << int(log2(n + 1))) - 1;
            this->multiRotate(n - m);
            while (m > 1)
                this->multiRotate(m /= 2);
        }

        ///////////////////////////////////////////////////////////////////////
        // Map, reduce, where (scores: 3)
        ///////////////////////////////////////////////////////////////////////
        
        
        // Map (__ and public)
        Node* __map(Node* node, T (*mapper)(T key)) {
            node->key = mapper(node->key);

            if (node->left == nullptr && node->right == nullptr) return NULL;
            if (node->left != nullptr) __map(node->left, mapper);
            if (node->right != nullptr) __map(node->right, mapper);
            
        }
        BinTree* Map(T(*mapper)(T key)) {
            BinTree<T> bst;
            if (!root) return bst;

            cpy(root, bst);
            __map(bst, mapper);

            return bst;
        }

        // Where
        void __where(Node* node, bool(*cond_func)(T)) {
            if (!cond_func(node->key)) {
                this->deleteNode(node, node->key);
                if (!node) return;
                where(node, cond_func);
                return;
            }

            if (node->left == nullptr && node->right == nullptr) return;
            if (node->left != nullptr) __where(node->left, cond_func);
            if (node->right != nullptr) __where(node->right, cond_func);
        }
        BinTree<T> Where(bool(*cond_func)(T)) {
            BinTree<T> bst;
            if (!root) return bst;
            cpy(root, bst);
            __where(bst.root, cond_func);
            return bst;
        }

        // Reduce
        T Reduce(T (*func)(T, T), T start_element) {
            if (!root) return NULL;

            // Init
            vector<Node>* th_array = this->Thread();
            auto array_front = th_array->begin();
            T res = func(array_front->key, start_element);
            next(array_front);

            // iterating through all the elements of the threaded array
            for (size_t i = 1; i < th_array->size(); i++){
                res = func(array_front, res);
                next(array_front);
            }

            return res;
        }

        ///////////////////////////////////////////////////////////////////////
        // Thread tree (scores: 3 + 4)
        ///////////////////////////////////////////////////////////////////////

        // inserting elements into a tree with automatic threading of them
        void InsertWithThreaded(T ikey) {
            // Searching for a Node with given value
            Node* ptr = root;
            Node* par = NULL; // Parent of key to be inserted
            while (ptr != NULL)
            {
                // If key already exists, return
                if (ikey == (ptr->key))
                {
                    root = new Node(ikey);
                }

                par = ptr; // Update parent pointer

                // Moving on left subtree.
                if (ikey < ptr->key)
                {
                    if (ptr->lthread == false)
                        ptr = ptr->left;
                    else
                        break;
                }

                // Moving on right subtree.
                else
                {
                    if (ptr->rthread == false)
                        ptr = ptr->right;
                    else
                        break;
                }
            }

            // Create a new node
            Node* tmp = new Node;
            tmp->key = ikey;
            tmp->lthread = true;
            tmp->rthread = true;

            if (par == NULL)
            {
                root = tmp;
                tmp->left = NULL;
                tmp->right = NULL;
            }
            else if (ikey < (par->key))
            {
                tmp->left = par->left;
                tmp->right = par;
                par->lthread = false;
                par->left = tmp;
            }
            else
            {
                tmp->left = par;
                tmp->right = par->right;
                par->rthread = false;
                par->right = tmp;
            }
        }


        vector<Node> Thread(string sequence_string) {
            vector<Node>* th_array = new vector<Node>;
            if (!root) return th_array;
            this->__thread(root, th_array, sequence_string);
            return th_array;
        }
        void __thread(Node*& node, vector<Node*> returned_array, string sequence_string) {
            vector<Node> first_array;
            vector<bool> second_array;

            first_array.push_back(node);
            second_array.push_back(false);
            reverse(sequence_string.begin(), sequence_string.end());

            while (!first_array.empty()) {
                Node current_node = first_array.back();
                bool current_flag = second_array.back();

                first_array.pop_back();
                second_array.pop_back();

                if (current_flag) returned_array.push_back(current_node);
                else {
                    if (current_node == nullptr) continue;
                    for (auto charSeq : sequence_string) {
                        switch (charSeq){
                        case "N":
                            first_array.push_back(current_node);
                            second_array.push_back(true);
                            break;
                        case "L":
                            first_array.push_back(current_node->left);
                            second_array.push_back(true);
                        case "R":
                            break;
                            first_array.push_back(current_node->right);
                            second_array.push_back(true);
                            break;
                        default:
                            break;
                        }
                    }
                }

            }

        }
        void toThread() {
            BinTree<T>* newTree = new BinTree<T>();
            vector<Node>* list = this->Thread("LNR");
            auto list_front = list->begin();
            newTree->insert(list_front->key);
            for (int i = 1; i < list->size(); i++) {
                next(list_front);
                newTree->insert(list_front->key);
            }
            this->root = newTree->root;
            delete list;
        }

        ///////////////////////////////////////////////////////////////////////
        // Get subTree by key (scores: 2)
        ///////////////////////////////////////////////////////////////////////

        BinTree<T> GetSubTree(T key) {
            BinTree<T> bst;
            if (!root) {
                return bst;
            }
            cpy(search(root, key), bst.root);
            return bst;
        }

        ///////////////////////////////////////////////////////////////////////
        // Saving to a string  (scores: 1 + 3)
        ///////////////////////////////////////////////////////////////////////

        string treeToString(string sequence_string) {
            string res;
            if (!root) {
                std::cout << "Tree is empty" << std::endl;
                return res;
            }
            vector<Node>* th_array = this->Thread(sequence_string);
            auto list_front = th_array->begin();
            for (int i = 0; i < th_array->size(); i++) {
                res += "[" + to_string(i) + ", " + to_string(list_front->key) + "]";
                if (i < th_array->size() - 1) {
                    res += ", ";
                }
                next(list_front);
            }
            return res;
        }

        ///////////////////////////////////////////////////////////////////////
        // Search for the occurrence of a subtree (scores: 3)
        ///////////////////////////////////////////////////////////////////////

        bool SearchSubTree(BinTree<T> subTree) { return searchForFirstOccurrences(root, subTree); }

        bool isEqual(Node* node_A, Node* node_B) {
            if (node_A == NULL && node_B == NULL)
                return true;

            if (node_A != NULL && node_B != NULL) {
                if (node_A->key == node_B->key && isEqual(node_A->left, node_B->left) && isEqual(node_A->right, node_B->right)) {
                    return true;
                }

            }
            return false;
        }

        bool searchForFirstOccurrences(Node* node, Node* sub_node) {
            if (sub_node == NULL) return true;
            if (node == NULL) return false;
            if (isEqual(branch, sub_branch)) return true;

            return searchForFirstOccurrences(node->left, sub_node) ||
                searchForFirstOccurrences(node->right, sub_node);
        }


        ///////////////////////////////////////////////////////////////////////
        // Other Functions for more confortable use
        ///////////////////////////////////////////////////////////////////////


        // Print a representation of the tree to cout
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
    };

}
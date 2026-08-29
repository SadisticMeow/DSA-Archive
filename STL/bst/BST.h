#ifndef _CUSTOM_BST
#define _CUSTOM_BST

#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>
#include <functional>

// data type must have equality, comparison, ostrem operators defined.
template <typename Type>
class BST {
private:
	struct Node {
		Type data;
		Node *left, *right, *parent;

		Node(int value, Node* _l = nullptr, Node* _r = nullptr, Node* _p = nullptr) : data(value), left(_l), right(_r), parent(_p) {}
	};

	Node* root;
	
	// declaration for print lambda - used as default argument for tree walk functions; definition at end
	static std::function<void(const Type&)> printL;

	// recursively deletes entire bst - root at r
	static void deleteTree(Node* r) {
		if (!r) return;
		deleteTree(r->left);
		deleteTree(r->right);
		delete r;
	}
	// copies bst - root at r to root at cr
	static void copyTree(Node*& r, Node* cr) {
		if (!cr) return;
		r = new Node(cr->data);
		copyTree(r->left, cr->left);
		copyTree(r->right, cr->right);
	}
	// recursively inserts value at right position
	static void insertR(Node*& r, Node* p, const Type val) {
		if (!r) r = new Node(val, nullptr, nullptr, p);
		else {
			if (val <= r->data) insertR(r->left, r, val);
			else insertR(r->right, r, val);
		}
	}
	// removes given node and replaces it with one of its child nodes
	static void remove(Node*& root, Node*& r) {
		Node* rep = nullptr, * d_r_l = nullptr, * p_r_e = r->left;
		if (r->right) rep = r->right;									// rep is the replacement node; prefered right child
		else rep = r->left;
		if (rep) d_r_l = rep->left;										// save left branch of rep
		if (r->left) p_r_e = getMax(r->left);							// save the right-most(biggest) node in left subtree
																		// p_r_e is where d_r_l will be attached
		if (r == root) root = rep;										// handle if root is to be deleted
		else if (r->parent->right == r) r->parent->right = rep;			// handle if r was right child of its parent
		else r->parent->left = rep;										// handle if r was left child of its parent
		if (rep) {
			rep->parent = r->parent;									// move parentage of replacement node to parent of node to be deleted
			if (rep != r->left) rep->left = r->left;					// set left branch of replacement to left branch of node to be deleted
		}																// now original left branch of replacement is severed but stored in d_r_l
		if (p_r_e && p_r_e != rep) p_r_e->right = d_r_l;				// if p_r_e exists, then thats where d_r_l will be attached
		else if (rep) rep->left = d_r_l; 								// otherwise, means node to be deleted had no left branch
																		// then d_r_l will be made left branch of replacement
																		// d_r_l was bigger than left subtree; p_r_e is max of left subtree	
																		// replacement is bigger than both
		delete r;														// node to be deleted is completely isolated now; delete the bugger
	}
	// returns node with give value if found in bst
	static Node* searchR(Node* r, const Type val) {
		if (!r) return nullptr;
		if (r->data == val) return r;
		
		if (val < r->data) return searchR(r->left, val);
		else searchR(r->right, val);
	}
	
	// ascending order tree walk
	template <typename Lambda>
	static void LNR(Node* r, Lambda&& function) {
		if (!r) return;

		LNR(r->left, std::forward<Lambda>(function));
		function(r->data);
		LNR(r->right, std::forward<Lambda>(function));
	}
	// descending order tree walk
	template <typename Lambda>
	static void RNL(Node* r, Lambda&& function) {
		if (!r) return;

		RNL(r->right, std::forward<Lambda>(function));
		function(r->data);
		RNL(r->left, std::forward<Lambda>(function));
	}
	// depth order tree walk - from root down to leaves
	template <typename Lambda>
	static void NLR(Node* r, Lambda&& function) {
		if (!r) return;

		function(r->data);
		NLR(r->left, std::forward<Lambda>(function));
		NLR(r->right, std::forward<Lambda>(function));
	}
	// reverse depth order tree walk - from leaves up to root
	template <typename Lambda>
	static void LRN(Node* r, Lambda&& function) {
		if (!r) return;

		LRN(r->left, std::forward<Lambda>(function));
		LRN(r->right, std::forward<Lambda>(function));
		function(r->data);
	}
	
	// returns if given node has only one branch
	static bool hasOnlyOneBranch(Node* r) {
		if (!r) return 0;
		if (!r->left && !r->right) return 0;
		if (r->left && r->right) return 0;
		return 1;
	}
	// returns if given bsts roots at r1 and r1 are the same
	static bool isCongruent(Node* r1, Node* r2) {
		if (!r1 && !r2) return 1;
		if (!r1 || !r2) return 0;

		return (r1->data == r2->data) &&
			isCongruent(r1->left, r2->left) &&
			isCongruent(r1->right, r2->right);
	}
	// returns size of bst at root r
	static int size(Node* r) {
		if (!r) return 0;
		return size(r->left) + size(r->right) + 1;
	}
	// calculates height of given bst root at r
	static int height(Node* r) {
		if (!r) return 0;

		int lt = height(r->left);
		int rt = height(r->right);
		int c = 1 + (lt >= rt ? lt : rt);
		return c;
	}
	// returns count of leaf nodes in bst at root r
	static int countLeaves(Node* r) {
		if (!r) return 0;
		return countLeaves(r->left) + countLeaves(r->right) + (!r->left && !r->right);
	}
	// returns count of non-leaf nodes in bst at root r
	static int countNonLeaves(Node* r) {
		if (!r) return 0;
		return countNonLeaves(r->left) + countNonLeaves(r->right) + (r->left || r->right);
	}
	// returns count of branches in bst at root r
	static int countBranches(Node* r) {
		if (!r) return 0;
		return countNonLeaves(r->left) + countNonLeaves(r->right) + hasOnlyOneBranch(r);
	}

	// prints path from root to the given node
	static void printPath(Node* r) {
		if (!r) return;
		printPath(r->parent);
		std::cout << "-> " << r->data;
	}
	// writes bst data to a file specified by given fstream reference
	static void fileWrite(Node* r, std::ofstream& w)  {
		if (!r) return;

		NLR(r, [&w](Type data) {w << data << " "; });
	}
	// reads data into bst from a file specified by given fstream reference
	void fileReadR(Node*& r, std::ifstream& w) {
		if (w.eof()) return;

		Type x;
		if (w >> x) {
			insert(x);
			fileReadR(r, w);
		}
	}
	// fills all bst data into given vector
	static void fillVector(Node* r, std::vector<Type>& vec, const bool rev) {
		if (!r) return;
		if (rev) RNL(r, [&vec](Type data) {vec.push_back(data); });
		else LNR(r, [&vec](Type data) {vec.push_back(data); });
	}

	// returns node with minimum value
	static Node* getMin(Node* r) {
		if (!r) return r;
		if (!r->left) return r;
		getMin(r->left);
	}
	// returns node with maximum value
	static Node* getMax(Node* r) {
		if (!r) return r;
		if (!r->right) return r;
		getMax(r->right);
	}
	// recursively finds the node right next to th given one 
	static Node* successorR(Node* r, Node* t) {
		if (!r) return nullptr;
		if (r->right && r->right != t) return getMin(r->right);			// if right child exists and not to be avoided, min of right branch is successor
		if (r->parent && r->parent->left == r) return r->parent;		// else if this is parent's left child, parent is successor
		return successorR(r->parent, r);								// else this is parent's right child; find parents successor skipping this
	}
	// recursively finds the node right before to th given one 
	static Node* predecessorR(Node* r, Node* t) {
		if (!r) return nullptr;
		if (r->left && r->left != t) return getMax(r->left);			// if left child exists and not to be avoided, max of left branch is predecessor
		if (r->parent && r->parent->right == r) return r->parent;		// else if this is parent's right child, parent is predecessor
		return predecessorR(r->parent, r);								// else this is parent's left child; find parents predecessor skipping this
	}
	// returns minimum node in bst
	static Node* successor(Node* r) { return successorR(r, r); }
	// returns maximum node in bst
	static Node* predecessor(Node* r) { return predecessorR(r, r); }

public:
	// constructor
	BST() : root(nullptr) {}
	// move constructor
	BST(BST&& other) : root(other.root) { other.root = nullptr; }
	// copy constructor
	BST(const BST& other) { copyTree(root, other.root); }
	// initializer list constructor
	BST(std::initializer_list<Type> list) {
		for (auto elem : list) {
			insert(elem);
		}
	}
	// destructor
	~BST() { clear(); }
	
	// assignment operator
	BST& operator=(const BST& other) {
		BST obj(other);
		return obj;
	}
	// equality operator
	bool operator==(const BST& other) { return isCongruent(root, other.root); }

	// inserts given value into bst
	void insert(const Type& value) { insertR(root, nullptr, value); }
	// removes node with given value from bst
	bool remove(const Type& value) {
		Node* p = searchR(root, value);
		if (!p) return 0;
		remove(root, p);
		return 1;
	}
	// returns if value found within bst
	bool search(const Type& value) const {
		Node* p = searchR(root, value);
		if (!p) return 0;
		return 1;
	}
	// clears all data from bst
	void clear() {
		deleteTree(root);
		root = nullptr;
	}

	// returns size of bst
	int size() const { return size(root); }
	// returns height/depth of bst
	int height() { return height(root); }
	// returns number of leaf nodes in bst
	int leafCount() { return countLeaves(root); }
	// returns number of non-leaf nodes in bst
	int nonleafCount() { return countNonLeaves(root); }
	// returns number of branches in bst
	int branchCount() { return countBranches(root); }

	// returns if bst root at r has near same height left, right branches
	bool is_balanced(const Node* r) {
		int h1 = height(r->left);
		int h2 = height(r->right);

		return (std::abs(h1 - h2) <= 1);
	}
	// returns if bst is empty
	bool empty() const { return (!root); }
	// returns root of bst
	Node* getRoot() const { return root; }
	// returns minimum value in bst
	Type get_max(Node* r) {
		auto x = getMax(r);
		if (x) return x->data;
		else return NULL;
	}
	// returns minimum value in bst
	Type get_min(Node* r) {
		auto x = getMin(r);
		if (x) return x->data;
		else return NULL;
	}
	// displays path to given value if exists within bst
	void show_path(const Type& value) {
		Node* p = searchR(root, value);
		if (!p) return;
		printPath(p);
	}

	// inorder traversal applying given lambda function to each node - default is print
	void inorder(std::function<void(const Type&)> func = printL) const { LNR(root, func); }
	// reverse inorder traversal applying given lambda function to each node - default is print
	void outorder(std::function<void(const Type&)> func = printL) const { RNL(root, func); }
	// preorder traversal applying given lambda function to each node - default is print
	void preorder(std::function<void(const Type&)> func = printL) const { NLR(root, func); }
	// postorder traversal applying given lambda function to each node - default is print
	void postorder(std::function<void(const Type&)> func = printL) const { LRN(root, func); }

	// read value from given file into bst
	bool read_from_file(const char* file_name) {
		std::ifstream reader(file_name);
		fileReadR(root, reader);
		reader.close();
		return 1;
	}
	// writes bst values to given file
	bool write_to_file(const char* file_name) const {
		std::ofstream writer(file_name);
		fileWriteR(root, writer);
		writer.close();
		return 1;
	}
	// loads vector data into bst
	void load_vector(const std::vector<int>& vec) {
		clear();
		for (int i = 0; i < vec.size(); i++) {
			insert(vec[i]);
		}
	}
	// returns vector filled with bst data
	std::vector<Type> fill_vector(const bool reverse = 0) { 
		std::vector<Type> vec;
		fillVector(root, vec, reverse); 
		return vec;
	}

};
// definition for print lambda 
template <typename Type>
std::function<void(const Type&)> BST<Type>::printL = [](Type data) {std::cout << data << " "; };
// uses a bst to sort data in a vector
template <typename T>
inline void sort_with_BST(std::vector<T>& vec) {
	BST<T> t;
	std::vector<T> sorted;
	t.load_vector(vec);
	vec.clear();
	sorted = t.fill_vector();
	vec = sorted;
}

#endif
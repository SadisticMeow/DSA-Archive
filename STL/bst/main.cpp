#include "BST.h"
#include <vector>

int main_BST()
{
	BST<int> t;

	t.insert(50);
	t.insert(60);
	t.insert(40);
	t.insert(45);
	t.insert(55);
	t.insert(52);
	t.insert(30);
	t.remove(40);

	t.inorder();
	std::cout << "\n";

	BST<int> t1(t);
	t1.inorder();
	std::cout << "\n";

	BST<int> t2 = t1;
	t2.inorder();
	std::cout << "\n";

	BST<int> t3(static_cast<BST<int>&&>(t2));
	t3.inorder();
	std::cout << "\n";

	t2.inorder();
	std::cout << "\n";

	std::cout << "empty: " << t.empty() << "\n";
	std::cout << "size: " << t.size() << "\n";
	std::cout << "search for 60: " << t.search(60) << "\n";
	std::cout << "height: " << t.height() << "\n";
	std::cout << "balanced: " << t.is_balanced(t.getRoot()) << "\n";
	std::cout << "count leaves: " << t.leafCount() << "\n";
	std::cout << "count non leaves: " << t.nonleafCount() << "\n";
	std::cout << "count branches: " << t.branchCount() << "\n";
	std::cout << "min: " << t.get_min(t.getRoot()) << "\n";
	std::cout << "max: " << t.get_max(t.getRoot()) << "\n";
	std::cout << "t == t1?: " << (t == t1) << "\n";
	t.show_path(52);
	std::cout << "-- path to 52" << "\n";

	std::cout << "\n";
	t.inorder();
	std::cout << "-- LNR" << "\n";
	t.outorder();
	std::cout << "-- RNL" << "\n";
	t.preorder();
	std::cout << "-- NLR" << "\n";
	t.postorder();
	std::cout << "-- LRN" << "\n\n";

	std::vector<int> v = t.fill_vector();
	for (auto it = v.begin(); it != v.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "-- vector translation\n";


	return 0;
}
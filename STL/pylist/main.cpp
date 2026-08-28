#include "Pylist.h"
using namespace std;

int main()
{
	Pylist list1 = { 1, std::string("two"), '3', 4.0f };
	Pylist list2 = { '$', std::string("monkey"), false };
	Pylist copylist, slicelist, concatlist;
	std::size_t s1 = 0, s2 = 0;

	std::cout << "Initialising list 1: " << list1 << "\n";
	std::cout << "Initialising list 2: " << list2 << "\n";

	list1.append(5.55);
	std::cout << "Appending 5.55 to list 1: " << list1 << "\n";

	list1.insert(3, 3.333f);
	std::cout << "Inserting 3.333 at index 3 of list 1: " << list1 << "\n";

	list1.setitem(1, std::string("two and 3/4 quarters"));
	std::cout << "Setting item to \"two and 3/4 quarters\" at index 1 of list 1: " << list1 << "\n";

	list2.append(list1);
	std::cout << "Appending list 1 to list 2 (list within list): " << list2 << "\n";

	list2.pop();
	std::cout << "Popping last item of list 2: " << list2 << "\n";

	list1.extend(list2);
	std::cout << "Extending list 1 with list 2: " << list1 << "\n";

	list1.remove(std::string("monkey"));
	std::cout << "Removing \"monkey\" from list 1: " << list1 << "\n";

	copylist = list1.copy();
	std::cout << "Copying list 1: " << copylist << "\n";

	copylist.clear();
	std::cout << "Clearing The copied list above: " << copylist << "\n";

	std::cout << "Index of \'3\' in list1: " << list1.index('3') << "  Index of \'$\' in list1: " << list1.index('$') << "\n";

	slicelist = list1.slice(2, 6);
	std::cout << "Slicing list 1 from index 2 to 6: " << slicelist << "\n";

	concatlist = slicelist + list2;
	std::cout << "Concatenating (+) sliced list above and list 2: " << concatlist << "\n";

	s1 = slicelist.len();
	std::cout << "Getting length of sliced list: " << s1 << "\n";

	for (LL i = s1 - 1; i > -1; --i) { slicelist.pop(i); }
	std::cout << "Popping all items from sliced list with a loop: " << slicelist << "\n";

	std::cout << "Checking if list 1 contains 5.55: " << list1.contains(5.55) << "\n";

	std::cout << "Getting count of 1 from list 1: " << list1.count(1) << "\n";

	list1.sort();
	std::cout << "Sorting list 1 in ascending type order: " << list1 << "\n";

	list2.sort(true);
	std::cout << "Sorting list 2 in descending type order: " << list2 << "\n";

	list1.reverse();
	std::cout << "Reversing list 1: " << list1 << "\n";

	std::cout << "Printing all elements of list 1 using iterators: ";
	for (auto it = list1.begin(); it != list1.end(); ++it) {
		std::shared_ptr<Box> b = *it;
		b->print();
		std::cout << "  ";
	}
	std::cout << "\n";

	std::cout << "Printing all elements of list 2 using iterators: ";
	for (auto it = list2.rbegin(); it != list2.rend(); ++it) {
		std::shared_ptr<Box> b = *it;
		b->print();
		std::cout << "  ";
	}
	std::cout << "\n";





	return 0;
}
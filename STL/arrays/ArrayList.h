#ifndef _ARRAY_LIST
#define _ARRAY_LIST

#include <iostream>
#include <initializer_list>

template <typename Type>
class ArrayList {
	int cap, size;
	Type* arr;

	// resizes the arraylist to 150% capacity
	void resize(){
		cap = (int)cap * 1.5;
		Type* temp = new Type[cap];
		for (int i = 0; i < size; i++) temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	}
public:
	// constructor
	ArrayList() : cap(2), size(0), arr(new Type[cap]) {}
	// move constructor
	ArrayList(ArrayList<Type>&& obj) : cap(obj.cap), size(obj.size), arr(obj.arr) {
		obj.arr = nullptr;
		obj.cap = 0;
		obj.size = 0;
	}
    // copy constructor
	ArrayList(const ArrayList<Type>& obj) : cap(obj.cap), size(obj.size), arr(new Type[cap]) {
		for (int i = 0; i < size; i++) { arr[i] = obj.arr[i]; }
	}
    // initializer list constructor
	ArrayList(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), arr(new Type[cap]) {
		int i = 0;
		for (const auto& item : list) {
			arr[i] = item;
			i++;
		}
	}
	// destructor
	~ArrayList() { delete[] arr; }
	// inserts given value at end
	void push_back(Type value) {
		if (size == cap) resize();
		arr[size] = value;
		size++;
	}
	// removes the value at the end
	void pop_back() { if (!empty()) size--; }
    // inserts value at given index
	void insert(int index, const Type& value) {
		if (size == cap) resize();
		for (int i = 0; i < size - index; i++) {
			arr[size - i] = arr[size - i - 1];
		}
		arr[index] = value;
		size++;
	}
    // removes value at given index
	void removeAt(int index) {
		for (int i = index; i < size - 1; i++) {
			arr[i] = arr[i + 1];
		}
		size--;
	}
    // wipes the ArrayList clean for new data
	void clear() { size = 0; }
    // returns size - number of elements currently contained
	int Size() { return size; }
    // returns capacity - number of elements that can be contained
	int Capacity() { return cap; }
    // returns if ArrayList is empty
	bool empty() { return size == 0; }
	// setter - returns value at given index, mutable
	Type operator[](const int index) { return arr[index]; }
	// getter - returns value at given index, immutable
	Type& operator[](const int index) const { return arr[index]; }
};

#endif
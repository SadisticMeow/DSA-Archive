#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#include <iostream>
#include <initializer_list>

template <typename Type>
class DynamicArray {
	int cap;
	Type* arr;

	// resizes the vector to double capacity
	void resize() {
		cap = cap + 1;
		Type* temp = new Type[cap];
		for (int i = 0; i < size; i++) temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	};
public:
	// constructor
	DynamicArray() : cap(0), arr(nullptr) {}
	// move constructor
	DynamicArray(DynamicArray<Type>&& obj) : cap(obj.cap), size(obj.size), arr(obj.arr) {
		obj.arr = nullptr;
		obj.cap = 0;
		obj.size = 0;
	}
    // copy constructor
	DynamicArray(const DynamicArray<Type>& obj) : cap(obj.cap), size(obj.size), arr(new Type[cap]) {
		for (int i = 0; i < size; i++) { arr[i] = obj.arr[i]; }
	}
    // initializer list constructor
	DynamicArray(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), arr(new Type[cap]) {
		int i = 0;
		for (const auto& item : list) {
			arr[i] = item;
			i++;
		}
	}
	// destructor
	~DynamicArray() { delete[] arr; }
	// inserts given value at end
	void pushBack(Type value) {
		if (size == cap) resze();
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
    // wipes the DynamicArray clean for new data
	void clear() { size = 0; }
    // returns size - number of elements currently contained
	int Size() { return size; }
    // returns capacity - number of elements that can be contained
	int Capacity() { return cap; }
    // returns if DynamicArray is empty
	bool empty() { return size == 0; }
	// setter - returns value at given index, mutable
	Type operator[](const int index) { return arr[index]; }
	// getter - returns value at given index, immutable
	Type& operator[](const int index) const { return arr[index]; }
};

#endif 
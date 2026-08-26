#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#include <iostream>
#include <initializer_list>

template <typename Type>
class DynamicArray {
	int size;
	Type* arr;

	// resizes the vector to double size
	void resize() {
		Type* temp = new Type[size + 1];
		for (int i = 0; i < size; i++) temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	};
public:
	// constructor
	DynamicArray() : size(0), arr(nullptr) {}
	// move constructor
	DynamicArray(DynamicArray<Type>&& obj) : size(obj.size), arr(obj.arr) {
		obj.arr = nullptr;
		obj.size = 0;
	}
    // copy constructor
	DynamicArray(const DynamicArray<Type>& obj) : size(obj.size), arr(new Type[size]) {
		for (int i = 0; i < size; i++) { arr[i] = obj.arr[i]; }
	}
    // initializer list constructor
	DynamicArray(std::initializer_list<Type> list) : size(list.size()), arr(new Type[size]) {
		int i = 0;
		for (const auto& item : list) {
			arr[i] = item;
			i++;
		}
	}
	// destructor
	~DynamicArray() { delete[] arr; }
	// inserts given value at end
	void push_back(Type value) {
		resize();
		arr[size] = value;
		size++;
	}
	// removes the value at the end
	void pop_back() { if (!empty()) size--; }
    // inserts value at given index
	void insert(int index, const Type& value) {
		resize();
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
    // returns if DynamicArray is empty
	bool empty() { return size == 0; }
	// setter - returns value at given index, mutable
	Type operator[](const int index) { return arr[index]; }
	// getter - returns value at given index, immutable
	Type& operator[](const int index) const { return arr[index]; }
};

#endif 
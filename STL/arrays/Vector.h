#ifndef _CUSTOM_VECTOR
#define _CUSTOM_VECTOR

#include <iostream>
#include <initializer_list>

template <typename Type>
class Vector {
	int cap, size;
	Type* arr;

    // resizes the vector to double capacity
	void resize() {
		cap = cap * 2;
		Type* temp = new Type[cap];
		for (int i = 0; i < size; i++) temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	};
public:
	class iterator {
		friend class Vector;
		Type* ptr;
		iterator(Type* p) : ptr(p) {}
	public:
		bool operator==(const iterator& obj) { return ptr == obj.ptr; }
		bool operator!=(const iterator& obj) { return ptr != obj.ptr; }
		bool operator<(const iterator& obj) { return ptr < obj.ptr; }
		bool operator>(const iterator& obj) { return ptr > obj.ptr; }
		iterator& operator++() {
			++ptr;
			return *this;
		}
		iterator& operator--() {
			--ptr;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = *this;
			++ptr;
			return temp;
		}
        iterator operator--(int) {
			iterator temp = *this;
			--ptr;
			return temp;
		}
		iterator operator-(const int i) {
			iterator temp = *this;
			ptr = ptr - i;
			return temp;
		}
		iterator operator+(const int i) {
			iterator temp = *this;
			ptr = ptr + i;
			return temp;
		}
		Type& operator*() { return *ptr; }
	};

    // constructor
	Vector() : cap(1), size(0), arr(new Type[cap]) {}
    // move constructor
	Vector(Vector<Type>&& obj) : cap(obj.cap), size(obj.size), arr(obj.arr) {
		obj.arr = nullptr;
		obj.cap = 0;
		obj.size = 0;
	}
    // copy constructor
	Vector(const Vector<Type>& obj) : cap(obj.cap), size(obj.size), arr(new Type[cap]) {
		for (int i = 0; i < size; i++) { arr[i] = obj.arr[i]; }
	}
    // initializer list constructor
	Vector(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), arr(new Type[cap]) {
		int i = 0;
		for (const auto& item : list) {
			arr[i] = item;
			i++;
		}
	}
    // destructor
	~Vector() { delete[] arr; }
    // inserts new value at end
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
    // wipes the vector clean for new data
	void clear() { size = 0; }
    // returns size - number of elements currently contained
	int Size() { return size; }
    // returns capacity - number of elements that can be contained
	int Capacity() { return cap; }
    // returns if vector is empty
	bool empty() { return size == 0; }
    // finds the given value if present within vector
	iterator find(Type val) {
		for (auto i = begin(); i != end(); ++i) { if (val == *i) return i; }
		return end();
	}
    // inserts value at given iterator position
	iterator insert(const iterator pos, const Type& value) {
		int index = pos.ptr - arr;
		if (index < 0 || index > size) return end();
		insert(index, value);
		return iterator(begin() + index);
	}
    // inserts the values from a provided range at given iterator position
	iterator insert(const iterator i, const iterator p1, const iterator p2) {
		int index = i.ptr - arr;
		int diff = p2.ptr - p1.ptr;
		int c = index;
		if (index < 0 || index > size) return end();
		while (size + diff > cap) resize();
		for (int i = 0; i <= size - index; i++) {
			arr[size - i + diff] = arr[size - i];
		}
		for (auto i = p1; i != p2; ++i) {
			arr[c] = *i;
			c++;
		}
		size += diff;
		return iterator(begin() + index);
	}
    // removes value at given iterator position
	iterator erase(const iterator pos){
		int index = pos.ptr - arr;
		if (index < 0 || index > size) return end();
		removeAt(index);
		return iterator(begin() + index);
	}
    // removes all values in the provided range of iteratir positions
	iterator erase(const iterator first, const iterator last) {
		int index = first.ptr - arr;
		int diff = last.ptr - first.ptr;
		if (index < 0 || index > size) return end();
		for (int i = index; i < size; i++) {
			if (size == cap) resize();
			arr[i] = arr[i + diff];
			size--;
		}
		return iterator(begin() + index);
	}
    // returns iterator position of first value
	iterator begin() { return iterator(arr); }
    // returns iterator position just beyond last value
	iterator end() { return iterator(arr + size); }
	// returns iterator position of last value
	iterator rbegin() { return iterator(arr + (size - 1)); }
    // returns iterator position just before first value
	iterator rend() { return iterator(arr - 1); }
    // returns index plus the given offset
	iterator index(const int i) { return iterator(arr + i); }
    // setter - returns value at given index, mutable
	Type& operator[](const int index) { return arr[index]; }
    // getter - returns value at given index, immutable
	const Type& operator[](const int index) const{ return arr[index]; }
};

#endif
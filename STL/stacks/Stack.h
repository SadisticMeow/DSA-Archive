#ifndef _CUSTOM_STACK
#define _CUSTOM_STACK

#include <iostream>
#include <exception>

template <typename Type>
class Stack {
	int cap, size;
	Type* elements;

	// resizes to 2x capacity
	void resize() {
		if (cap == 0) cap = 1;
		else cap = size * 2;
		Type* temp = new Type[cap];
		for (int i = 0; i < size; i++) { temp[i] = elements[i]; }
		delete[] elements;
		elements = temp;
	}

public:
    class iterator {
		friend class Stack;
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
	Stack() : cap(0), size(0), elements(nullptr) {}
    // reserve-constructor
	Stack(const int s) : cap(s), size(0), elements(new Type[cap]) {}
    // move constructor
	Stack(Stack<Type>&& obj) : cap(obj.cap), size(obj.size), elements(obj.elements) {
		obj.elements = nullptr;
		obj.cap = 0;
		obj.size = 0;
	}
    // copy constructor
	Stack(const Stack<Type>& obj) : cap(obj.cap), size(obj.size), elements(new Type[cap]) {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
    // initializer list constructor
	Stack(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), elements(new Type[cap]) {
		int i = 0;
		for (const auto& item : list) {
			elements[i] = item;
			i++;
		}
	}
    // destructor
	~Stack() { delete[] elements; }
    // returns if stack is full
	bool isFull() { return cap == size; }
    // returns if stack is empty
	bool isEmpty() { return size == 0; }
    // appends value at top of stack
	void push(Type val) {
		if (isFull()) resize();
		elements[size] = val;
		size++;
	}
    // removes value at top of stack
	void pop() {
		if (isEmpty()) throw std::exception("stack underflow");
		size--;
	}
    // returns value at top of stack - read only
	Type top() const { return elements[size -1]; }
    // returns iterator position of bottom/first value
	iterator begin() { return iterator(elements); }
    // returns iterator position just after top/last value
	iterator end() { return iterator(elements + size); }
	// returns iterator position of top/last value
	iterator rbegin() { return iterator(elements + (size - 1)); }
	// returns iterator position just before bottom/last value
	iterator rend() { return iterator(elements - 1); }

};

#endif
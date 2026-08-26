#ifndef _COMPOSITE_STACKS
#define _COMPOSITE_STACKS

#include <iostream>
#include <exception>
#include <array>
#include <vector>

template <typename Type>
class staticStack {
	int cap, size;
	Type* elements;

public:
	// constructor
	staticStack(const int s) : cap(s), size(0), elements(new Type[cap]) {}
	// move constructor
	staticStack(staticStack<Type>&& obj) : cap(obj.cap), size(obj.size), elements(obj.elements) {
		obj.elements = nullptr;
		obj.cap = 0;
		obj.size = 0;
	}
    // copy constructor
	staticStack(const staticStack<Type>& obj) : cap(obj.cap), size(obj.size), elements(new Type[cap]) {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
    // initializer list constructor
	staticStack(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), elements(new Type[cap]) {
		int i = 0;
		for (const auto& item : list) {
			elements[i] = item;
			i++;
		}
	}
	// destructor
	~staticStack() { delete[] elements; }
	// returns if stack is full
	bool isFull() { return cap == size; }
	// returns if stack is empty
	bool isEmpty() { return size == 0; }
	// appends value at top of stack
	bool push(Type val) {
		if (isFull()) return 0;
		elements[size] = val;
		size++;
		return 1;
	}
	// removes value at top of stack
	bool pop() {
		if (isEmpty()) return 0;
		size--;
		return 1;
	}
	// returns value at top of stack - read only
	Type top() const { return elements[size - 1]; }
	// to help visualise
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << elements[i] << " ";
		}
		std::cout << "\n";
	}
};

template <typename Type, size_t cap>
class arrayStack {
	int size;
	std::array<Type,cap> elements;

public:
	// constructor
	arrayStack() : size(0) {}
	// move constructor
	arrayStack(arrayStack<Type, cap>&& obj) : size(obj.size), elements(obj.elements) {
		obj.elements.fill(0);
		obj.size = 0;
	}
    // copy constructor
	arrayStack(const arrayStack<Type, cap>& obj) : size(obj.size), elements() {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
    // initializer list constructor
	arrayStack(std::initializer_list<Type> list) : size(list.size()), elements() {
		int i = 0;
		for (const auto& item : list) {
			elements[i] = item;
			i++;
		}
	}
	// destructor
	~arrayStack() {}
	// returns if stack is full
	bool isFull() { return elements.size() == size; }
	// returns if stack is empty
	bool isEmpty() { return size == 0; }
	// appends value at top of stack
	bool push(Type val) {
		if (isFull()) return 0;
		elements[size] = val;
		size++;
		return 1;
	}
	// removes value from top of stack
	bool pop() {
		if (isEmpty()) return 0;
		size--;
		return 1;
	}
	// returns value at top of stack - read only
	Type top() { return elements[size - 1]; }
	// to help visualise
	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << elements[i] << " ";
		}
		std::cout << "\n";
	}
};

template <typename Type>
class vectorStack {
	std::vector<Type> elements;

public:
	// constructor
	vectorStack() {}
	// move constructor
	vectorStack(vectorStack<Type>&& obj) : elements(obj.elements) { obj.elements.clear(); }
	// copy constructor
	vectorStack(const vectorStack<Type>& obj) : elements(obj.elements) {}
	// initializer list constructor
	vectorStack(std::initializer_list<Type> list) {
		elements.resize(list.size());
		int i = 0;
		for (const auto& item : list) {
			elements[i] = item;
			i++;
		}
	}
	// destructor
	~vectorStack() {}
	// returns if stack is empty
	bool isEmpty() { return elements.size() == 0; }
	// appends value at top of stack
	void push(Type val) { elements.push_back(val); }
	// removes value from top of stack
	void pop() { 
		if (isEmpty()) throw std::exception("stack underflow");
		elements.pop_back(); 
	}
	// returns value at top of stack - read only
	Type top() { return elements[elements.size() - 1]; }
	// to help visualize
	void print() {
		for (int i = 0; i < elements.size(); i++) {
			std::cout << elements[i] << " ";
		}
		std::cout << "\n";
	}
};

#endif

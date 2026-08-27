#ifndef _CUSTOM_QUEUE
#define _CUSTOM_QUEUE

#include <iostream>
#include <exception>
#include <initializer_list>
#include <array>
#include <vector>

template <typename Type>
class Queue {
	int cap, size, front, rear;
	Type* elements;

	// resizes to 2x capacity
	void resize() {
		if (cap == 0) cap = 1;
		else cap = size * 2;
		Type* temp = new Type[cap];
		int i = front, j = 0;
		do {
			if (!elements) break;
			if (i > cap - 1) i = i % (cap - 1);
			temp[j] = elements[i];
			j++;
			i++;
		} while (i != rear + 1);
		delete[] elements;
		elements = temp;
		front = 0;
		rear = size - 1;
	}
public:
	 class iterator {
		friend class Queue;
		Type* ptr;
		int index, front, size;
		iterator(Type* p, int i, int f, int s) : ptr(p), index(i), front(f), size(s) {}
	public:
		bool operator==(const iterator& obj) { return (ptr == obj.ptr && index == obj.index); }
		bool operator!=(const iterator& obj) { return (ptr != obj.ptr || index != obj.index); }
		bool operator<(const iterator& obj) { return ptr < obj.ptr; }
		bool operator>(const iterator& obj) { return ptr > obj.ptr; }
		iterator& operator++() {
			++index;
			return *this;
		}
		iterator& operator--() {
			--index;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = *this;
			++index;
			return temp;
		}
        iterator operator--(int) {
			iterator temp = *this;
			--index;
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
		Type& operator*() { 
			int jump = (front + index) % size;
			return ptr[jump]; 
		}
	};

	// constructor
	Queue() : cap(0), size(0), front(0), rear(-1), elements(nullptr) {}
	// reserve constructor
	Queue(const int s) : cap(s), size(0), front(0), rear(-1), elements(new Type[cap]) {}
	// move constructor
	Queue(Queue<Type>&& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(obj.elements) {
		obj.size = 0;
		obj.front = 0;
		obj.rear = -1;
		obj.elements = nullptr;
	}
	// copy constructor
	Queue(const Queue<Type>& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(new Type[cap]) {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
	// initializer list constructor
	Queue(std::initializer_list<Type> list) : cap(list.size()), size(0), front(0), rear(-1), elements(new Type[cap]) {
		for (auto elem : list) {
			push(elem); 
		}
	}
	// destructor
	~Queue() { delete[] elements; }

	// returns if queue is empty
	bool isEmpty() const{ return size == 0; }
	// appends value to end of queue
	void push(Type val) {
		if (size == cap) resize();
		rear++;
		if (rear > cap - 1) rear = 0;
		elements[rear] = val;
		size++;
	}
	// removes value from front of queue
	void pop() {
		if (isEmpty()) throw std::exception("UNDERFLOW..");
		front++;
		if (front > cap - 1) front = 0;
		size--;
	}
	// returns value at front of queue - read only
	Type Front() const { return elements[front]; }
	// returns value at rear of queue - read only
	Type Rear() const { return elements[rear]; }
	// returns iterator position of front/first value
	iterator begin() { return iterator(elements, 0, front, size); }
    // returns iterator position just after rear/last value
	iterator end() { return iterator(elements, size, front, size); }
	// returns iterator position of rear/last value
	iterator rbegin() { return iterator(elements, size - 1, front, size); }
	// returns iterator position just before front/last value
	iterator rend() { return iterator(elements, -1, front, size); }

	// to help visualise
	void print() {
		for (int i = 0; i < size; i++) {
			if (i == front) std::cout << "F:";
			if (i == rear) std::cout << "R:";
			std::cout << elements[i] << " ";
		}
		std::cout << "\n";
	}
};

#endif
#ifndef _CUSTOM_DEQUE
#define _CUSTOM_DEQUE

#include <iostream>
#include <exception>
#include <initializer_list>

template <typename Type>
class Deque {
private:
	int cap, size, front, rear;
	Type* elements;

	// resizes to 2x capacity and straightens out the data
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
	class forwardIterator {
		friend class Deque;
		Type* ptr;
		int index, front, size;
		forwardIterator(Type* p, int i, int f, int s) : ptr(p), index(i), front(f), size(s) {}
	public:
		bool operator==(const forwardIterator& obj) { return ptr == obj.ptr; }
		bool operator!=(const forwardIterator& obj) { return ptr != obj.ptr; }
		bool operator<(const forwardIterator& obj) { return ptr < obj.ptr; }
		bool operator>(const forwardIterator& obj) { return ptr > obj.ptr; }
		forwardIterator& operator++() {
			++ptr;
			return *this;
		}
		forwardIterator& operator--() {
			--ptr;
			return *this;
		}
		forwardIterator operator++(int) {
			forwardIterator temp = *this;
			++ptr;
			return temp;
		}
		forwardIterator operator--(int) {
			forwardIterator temp = *this;
			--ptr;
			return temp;
		}
		Type& operator*() { 
			int jump = (front + index) % size;
			return ptr[jump]; 
		}
	};
	class reverseIterator {
		friend class Deque;
		Type* ptr;
		int index, front, size;
		reverseIterator(Type* p, int i, int f, int s) : ptr(p), index(i), front(f), size(s) {}
	public:
		bool operator==(const reverseIterator& obj) { return ptr == obj.ptr; }
		bool operator!=(const reverseIterator& obj) { return ptr != obj.ptr; }
		bool operator<(const reverseIterator& obj) { return ptr < obj.ptr; }
		bool operator>(const reverseIterator& obj) { return ptr > obj.ptr; }
		reverseIterator& operator++() {
			++ptr;
			return *this;
		}
		reverseIterator& operator--() {
			--ptr;
			return *this;
		}
		reverseIterator operator++(int) {
			reverseIterator temp = *this;
			++ptr;
			return temp;
		}
		reverseIterator operator--(int) {
			reverseIterator temp = *this;
			--ptr;
			return temp;
		}
		Type& operator*() { 
			int jump = (front + index) % size;
			return ptr[jump];
		}
	};

	// constructor
	Deque(int c = 2) : cap(c), size(0), front(0), rear(-1), elements(new Type[c]{0}) {}
	// move constructor 
	Deque(Deque<Type>&& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(obj.elements) {
		obj.elements = nullptr;
		obj.cap = 0;
		obj.size = 0;
		obj.front = 0;
		obj.rear = -1;
	}
	// copy constructor
	Deque(const Deque<Type>& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(new Type[cap]) {
		for (int i = 0; i < size; i++) {
			elements[i] = obj.elements[i];
		}
	}
	// intializer list constructor
	Deque(std::initializer_list<Type> list) : cap(list.size()), size(list.size()), front(0), rear(-1), elements(new Type[list.size()]{ 0 }) {
		int i = 0;
		for (auto elem : list) {
			elements[i] = elem;
			i++;
		}
		rear = i - 1;
	}
	// destructor
	~Deque() { delete[] elements; }

	// returns if deque is empty
	bool isEmpty() const { return size == 0; }
	// returns size of deque
	int Size() const { return size; }
	// prepends value at front of deque
	void push_front(const Type& val) {
		if (size == cap) resize();
		front--;
		if (front < 0) front = cap - 1;
		elements[front] = val;
		size++;
	}
	// appends value at end of deque
	void push_back(const Type& val) {
		if (size == cap) resize();
		rear++;
		if (rear > cap - 1) rear = 0;
		elements[rear] = val;
		size++;
	}
	// removes value at front of deque
	Type pop_front() {
		if (isEmpty()) throw std::exception("UNDERFLOW..");
		if (front == cap - 1) front = 0;
		else front++;
		size--;
	}
	// removes value at end of deque
	Type pop_back() {
		if (isEmpty()) throw std::exception("UNDERFLOW..");
		if (rear == 0) rear = cap - 1;
		else rear--;
		size--;
	}
	// returns value at front of deque - read only
	Type peek_front() const { return elements[front]; }
	// returns value at end of deque - read only
	Type peek_back() const { return elements[rear]; }

	forwardIterator begin() const{ return forwardIterator(elements, 0, front, size); }
	forwardIterator end() const{ return forwardIterator(elements, size, front, size); }
	reverseIterator rbegin() const{ return reverseIterator(elements, size -1, front, size); }
	reverseIterator rend() const{ return reverseIterator(elements, -1, front, size); }
};


#endif
#ifndef _QUEUES
#define _QUEUES

#include <iostream>
#include <initializer_list>
#include <exception>
#include <vector>
#include <array>
#include <stack>


template <typename Type>
class staticQueue {
	int cap, size, front, rear;
	Type* elements;

public:
	// constructor
	staticQueue(const int s) : cap(s), size(0), front(0), rear(-1), elements(new Type[cap]) {}
	// move constructor
	staticQueue(staticQueue<Type>&& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(obj.elements) {
		obj.elements = nullptr;
		obj.cap = 0;
		obj.size = 0;
		obj.front = 0;
		obj.rear = -1;
	}
	// copy constructor
	staticQueue(const staticQueue<Type>& obj) : cap(obj.cap), size(obj.size), front(obj.front), rear(obj.rear), elements(new Type[cap]) {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
	// initializer list constructor
	staticQueue(std::initializer_list<Type> initBruv) : cap(initBruv.size()), size(0), 
		front(0), rear(-1), elements(new Type[cap]) {
		for (auto elem : initBruv) { 
			push(elem);
		}
	}
	// destructor
	~staticQueue() { delete[] elements; }

	// returns if queue is full
	bool isFull() const{ return cap == size; }
	// returns if queue is empty
	bool isEmpty() const{ return size == 0; }
	// appends value at end of queue
	bool push(Type val) {
		if (isFull()) return 0;
		rear++;
		if (rear > cap - 1) rear = 0;
		elements[rear] = val;
		size++;
		return 1;
	}
	// removes value from front of queue
	bool pop() {
		if (isEmpty()) return 0;
		front++;
		if (front > cap - 1) front = 0;
		size--;
		return 1;
	}
	// returns value at front of queue - read only
	Type Front() const { return elements[front]; }
	// returns value at rear of queue - read only
	Type Rear() { return elements[rear]; }

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

template <typename Type, size_t cap>
class arrayQueue {
	int size, front, rear;
	std::array<Type, cap> elements;

public:
	// constructor
	arrayQueue() : size(0), front(0), rear(-1) {}
	// move constructor
	arrayQueue(arrayQueue<Type, cap>&& obj) : size(obj.size), front(obj.front), rear(obj.rear), elements(obj.elements) {
		obj.elements.fill(0);
		obj.size = 0;
		obj.front = 0;
		obj.rear = -1;
	}
	// copy constructor
	arrayQueue(const arrayQueue<Type, cap>& obj) : size(obj.size), front(obj.front), rear(obj.rear), elements() {
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
	// initializer list constructor
	arrayQueue(std::initializer_list<Type> list) : size(0), front(0), rear(-1) {
		for (auto elem : list) { push(elem); }
	}
	// destructor
	~arrayQueue() {}
	// returns if queue is full
	bool isFull() const { return size == cap; }
	// returns if queue is empty
	bool isEmpty() const { return size == 0; }
	// appends value at end of queue
	bool push(Type val) {
		if (isFull()) return 0;
		rear++;
		if (rear > cap - 1) rear = 0;
		elements[rear] = val;
		size++;
		return 1;
	}
	// removes value from front of queue
	bool pop() {
		if (isEmpty()) return 0;
		front++;
		if (front > cap - 1) front = 0;
		size--;
		return 1;
	}
	// returns value at front of queue - read only
	Type Front() const { return elements[front]; }
	// returns value at rear of queue - read only
	Type Rear() { return elements[rear]; }

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

template <typename Type>
class vectorQueue {
	int size, front, rear;
	std::vector<Type> elements;

	// straighthens the queue with regards to front and end
	void rearrange() {
		std::vector<Type> temp;
		int i = front;
		do {
			if (i > elements.size() - 1) i = i  % (elements.size());
			temp.push_back(elements[i]);
			i++;
		} while (i != rear + 1);
		elements = temp;
		front = 0;
		rear = elements.size() - 1;
	}

public:
	// constructor
	vectorQueue() : size(0), front(0), rear(-1) {}
	// move constructor
	vectorQueue(vectorQueue<Type>&& obj) : size(obj.size), front(obj.front), rear(obj.rear), elements(obj.elements) {
		obj.elements.clear();
		obj.size = 0;
		obj.front = 0;
		obj.rear = -1;
	}
	// copy constructor
	vectorQueue(const vectorQueue<Type>& obj) : size(obj.size), front(obj.front), rear(obj.rear) {
		elements.resize(size);
		for (int i = 0; i < size; i++) { elements[i] = obj.elements[i]; }
	}
	// initializer list constructor
	vectorQueue(std::initializer_list<Type> list) : size(0), front(0), rear(-1) {
		for (auto elem : list) { 
			elements.push_back(elem); 
			rear++; 
			size++;
		}
	}
	// destructor
	~vectorQueue() {}

	// returns if queue is empty
	bool isEmpty() const { return elements.size() == 0; }
	// appends value to end of queue
	void push(Type val) { 
		bool man = 0;
		if (size > 0 && size == elements.size() && front > rear) rearrange();
		if (rear == elements.size() - 1 && front > 0) {
			rear = -1;
			man = 1;
		}
		if (man) elements[rear + 1] = val;
		else elements.push_back(val);
		rear++;
		size++;
	}
	// removes value from front of queue
	void pop() {
		if (isEmpty()) throw std::exception("UNDERFLOW..");
		front++;
		size--;
	}
	// returns value at front of queue - read only
	Type Front() const { return elements[front]; }
	// returns value at rear of queue - read only
	Type Rear() { return elements[rear]; }

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

template <typename Type>
class stackQueue {
private:
	std::stack<Type> ss, sq; 
	// ss is supposed to be the back half and sq, the front half of queue
	// ss would have its top at rear and sq would have its top at front

	// re-distributes the data from one stack to another for queue operations
	static void shuffle(std::stack<Type>& src, std::stack<Type>& dst) {
		while (!src.empty()) {
			dst.push(src.top());
			src.pop();
		}
	}
public:
	// constructor
	stackQueue() {}
	// move constructor
	stackQueue(stackQueue<Type>&& obj) {
		obj.ss.swap(ss);
		obj.sq.swap(sq);
	}
	// copy constructor
	stackQueue(const stackQueue<Type>& obj) : ss(obj.ss), sq(obj.sq) {}
	// initializer list constructor
	stackQueue(std::initializer_list<Type> list) {
		for (auto elem : list) { ss.push(elem); }
	}
	// destructor
	~stackQueue() {}

	// returns if queue is empty
	bool isEmpty() const { return (ss.empty() && sq.empty()); }
	// returns size of queue
	int size() const { return (ss.size() + sq.size()); }
	// appends value to end of queue
	void push(Type val) { ss.push(val); }
	// removes value from front of stack
	Type pop() {
		if (ss.empty() && sq.empty()) throw std::exception("UNDERFLOW..");
		if (sq.empty()) shuffle(ss, sq);
		int x = sq.top();
		sq.pop();
		return x;
	}
	// returns value at front of queue
	Type front() {
		if (sq.empty()) shuffle(ss, sq);
		return sq.top();
	}
	// returns value at front of queue
	Type rear() {
		if (ss.empty()) shuffle(sq, ss);
		return ss.top();
	}

};


template <typename Type>
class Steue {
	std::stack<Type> sh, sq, ss; 
	// ss is supposed to be the back half and sq, the front half of queue. sh is just an intermediary helper stack
	// ss would have its top at rear and sq would have its top at front

	// re-distributes half the data from one stack to another for queue operations
	static void shuffleHalf(std::stack<Type>& src, std::stack<Type>& dst) {
		int c = src.size() / 2;
		for (int i = 0; i < c; i++) {
			dst.push(src.top());
			src.pop();
		}
	}
	// re-distributes the data from one stack to another for queue operations
	static void shuffleFull(std::stack<Type>& src, std::stack<Type>& dst) {
		int c = src.size();
		for (int i = 0; i < c; i++) {
			dst.push(src.top());
			src.pop();
		}
	}

	// re-distributes lower half of sq into ss
	void shuffleForSS() {
		shuffleHalf(sq, sh);
		shuffleFull(sq, ss);
		shuffleFull(sh, sq);
	}
	// re-distributes lower half of ss into sq
	void shuffleForSQ() {
		shuffleHalf(ss, sh);
		shuffleFull(ss, sq);
		shuffleFull(sh, ss);
	}

public:
	// constructor
	Steue() {}
	// move constructor
	Steue(Steue<Type>&& obj) {
		obj.sh.swap(sh);
		obj.ss.swap(ss);
		obj.sq.swap(sq);
	}
	// copy constructor
	Steue(const Steue<Type>& obj) : sh(obj.sh), ss(obj.ss), sq(obj.sq) {}
	// initializer list constructor
	Steue(std::initializer_list<Type> list) {
		for (auto elem : list) { ss.push(elem); }
	}
	// returns if steue is empty
	bool isEmpty() const { return (ss.empty() && sq.empty()); }
	// returns size of steue
	int size() const { return (ss.size() + sq.size()); }
	// appends value to end of steue
	void push(Type val) { ss.push(val); }
	// removes value at end/top of steue - stack-like
	Type popStack() {
		if (ss.empty() && sq.empty()) throw std::exception("UNDERFLOW..");
		if (ss.empty()) shuffleForSS();
		int x = ss.top();
		ss.pop();
		return x;
	}
	// removes value at front/bottom of steue - queue-like
	Type popQueue() {
		if (ss.empty() && sq.empty()) throw std::exception("UNDERFLOW..");
		if (sq.empty()) shuffleForSQ();
		int x = sq.top();
		sq.pop();
		return x;
	}
	// returns value at end of queue - read only
	Type topStack() const {
		if (ss.empty()) shuffleForSS();
		return ss.top();
	}
	// returns value at front of queue - read only
	Type topQueue() const {
		if (sq.empty()) shuffleForSQ();
		return sq.top();
	}
};


#endif
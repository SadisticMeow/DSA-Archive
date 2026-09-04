#ifndef DOUBLE_LIST
#define DOUBLE_LIST

#include <iostream>
#include <exception>
#include <initializer_list>
#include <functional>



template <typename Type>
class DoubleList {
private:
    struct Node {
        Type  val;
        Node* prev;
        Node* next;

        Node(const Type& value, Node* p = nullptr, Node* n = nullptr) : val(value), prev(p), next(n) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
    
    // declaration of print lambda - used as default argument for traverse method; definition at end
    static std::function<void(const Type&)> printL;

    // inserts value at an offset of 'index' from the given node
    static void insert(const Type& val, Node*& pos, const int offset = 0) {
        Node** curr = &pos, * next = nullptr, * prev = nullptr;
        for (int i = 0; i < offset; i++) {
            if (!(*curr)) break;
            prev = *curr;
            curr = &((*curr)->next);
        }
        next = *curr;
        *curr = new Node(val, prev, next);
        if (prev) prev->next = *curr;
        if (next) next->prev = *curr;
    }
    // removes value at an offset of 'index' from the given node
    static void remove(Node*& pos, const int offset = 0) {
        Node** curr = &pos, * next = nullptr, * prev = pos->prev;
        for (int i = 0; i < offset; i++) {
            if (!(*curr)->next) break;
            prev = *curr;
            curr = &((*curr)->next);
        }
        next = (*curr)->next;
        delete* curr;
        if (next) next->prev = prev;
        else *curr = prev;
        if (prev) prev->next = next;
        else *curr = next;
    }
    // returns node at given offset from given node
    static const Node* const* fetch(const Node* const* pos, const int offset = 0) {
        const Node* const* curr = pos;
        for (int i = 0; i < offset && (*curr)->next; i++) {
            curr = &((*curr)->next);
        }
        return curr;
    }
    // deletes all nodes onwards from given position
    static void clear(Node* pos) {
        Node* curr = pos, * prev = nullptr;
        while (curr) {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    // returns if given value found in list
    static bool find(Node* pos, const Type& val) {
        Node* curr = pos;
        while (curr) {
            if (curr->val == val) return 1;
            curr = curr->next;
        }
        return 0;
    }
    // returns if same chain of values is found in both lists, heads at h1 and h2
    static bool sameas(Node* h1, Node* h2) {
        Node* curr1 = h1, * curr2 = h2;
        while (curr1 && curr2) {
            if (curr1->val != curr2->val) return 0;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return 1;
    }

    // list traversal from head to tail
    template <typename Lambda>
    static void traverse_forward(Node*& h, Lambda&& function) {
        if (!h) return;
        function(h->val);
        traverse_forward(h->next, std::forward<Lambda>(function));
    }
    // list traversal from tail to head
    template <typename Lambda>
    static void traverse_backward(Node*& h, Lambda&& function) {
        if (!h) return;
        function(h->val);
        traverse_backward(h->prev, std::forward<Lambda>(function));
    }
public:
    class Iterator {
    private:
        Node* ptr = nullptr;
       
        Iterator(Node* p) : ptr(p) {}
        friend class DoubleList<Type>;
    public:
        bool operator==(const Iterator& other) const { return (ptr == other.ptr); }
        bool operator!=(const Iterator& other) const { return !(ptr == other.ptr); }
        
        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }
        Iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }
        Iterator operator--(int) {
            Iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }
        Type& operator*() { return ptr->val; }
    };

    // constructor
    DoubleList(Node* h = nullptr, const int s = 0) : head(h), tail(h), size(s) {}
    // move constructor
    DoubleList(DoubleList&& other) : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    // copy constructor
    DoubleList(const DoubleList& other) { // Deep copy. O(n).
        if (!other.head) return;
        head = new Node(other.head->val);
        Node* curr = head, * ocurr = other.head->next;

        while (ocurr) {
            curr->next = new Node(ocurr->val, curr);
            //prev = curr;
            curr = curr->next;
            ocurr = ocurr->next;
        }
        tail = curr;
        size = other.size;
    }
    // initializer list constructor
    DoubleList(std::initializer_list<Type> list) {
        size = list.size();
        for (auto elem : list) { insert(elem, head, size); }
    }
    // destructor
    ~DoubleList() {
        auto ptr = head;
        while (ptr) {
            auto gall = ptr;
            ptr = ptr->next;
            delete gall;
        }
        head = nullptr;
        tail = nullptr;
    }
    // assignment operator
    DoubleList& operator=(const DoubleList& other) { // Copy-assign. O(n).
        if (*this != other) {
            DoubleList obj(other);
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(size, other.size);
        }
        return *this;
    }
    // equality operator
    bool operator==(const DoubleList& other) {
        if (size != other.size) return 0;
        return sameas(head, other.head);
    }
    // inequality operator
    bool operator!=(const DoubleList& other) { return !(*this == other); }
    
    // returns if value found within list
    bool search(const Type& val) { return find(head, val); }
    // returns if list is empty
    bool empty() const { return size == 0; }
    // returns size of list
    int Size() const { return size; }

    // returns front/first value in list
    const Type& front() const { return head->val; }
    // returns back/last value in list
    const Type& back() const { return tail->val; }
    // returns value at given index in list
    const Type& operator[](int index) const {
        const Node* const* node = fetch(&head, index);
        if (!(*node)) throw std::exception("INVALID INDEX.");
        return (*node)->val;
    }

    // prepends given value to front of list
    void push_front(const Type& value) { 
        insert(value, head); 
        size++;
        if (size == 1) tail = head;
    }
    // appends given value to end of list
    void push_back(const Type& value) { 
        insert(value, tail, 1); 
        size++;  
        if (size == 1) head = tail;
        else tail = tail->next;
    }
    // inserts value at given index
    void insert(const Type& value, const int& index) { insert(value, head, index); size++; }

    // removes the value at front of list
    void pop_front() { 
        remove(head); 
        size--;
        if (size == 1) tail = head;
    }
    // removes the value at back of list
    void pop_back() { 
        remove(tail); 
        size--;
        if (size == 1) head = tail;
    }
    // removes value at given index
    void remove(const int& index) { remove(head, index); size--; }
    
    // wipes clear all the data in list
    void clear() {
        clear(head);
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    // traverses through the list, applying the given function in the given direction
    void traverse(const bool& reverse = 0, std::function<void(const Type&)> func = printL) {
        if (reverse) traverse_backward(head, func);
        else traverse_forward(head, func); 
    }
    // prints the list data - to help visualize 
    void print(const bool& reverse = 0) { traverse(reverse); }

    // returns iterator position to front node in list
    Iterator begin() const {  return Iterator(head); }
    // returns iterator position just beyond last node in list
    Iterator end() const { return Iterator(nullptr); }
    // returns iterator position to last node in list
    Iterator rbegin() const { return Iterator(tail); }
    // returns iterator position just before first position in list
    Iterator rend() const{ return Iterator(nullptr); }
};
// definition of print lambda
template <typename Type>
std::function<void(const Type&)> DoubleList<Type>::printL = [](const Type& data) { std::cout << data << "-> "; };


#endif
#ifndef _CUSTOM_LINKED_LIST
#define _CUSTOM_LINKED_LIST

#include <iostream>
#include <exception>
#include <initializer_list>
#include <functional>



template <typename Type>
class ForwardList {
private:
    struct Node {
        Type val;
        Node* next;
        friend class ForwardList<Type>;
        
        Node(const Type _val, Node* _next = nullptr) : val(_val), next(_next) {}
    };
    
    Node* head;
    int size;

    // declaration of print lambda - used as default argument for traverse method; definition at end
    static std::function<void(const Type&)> printL;

    // inserts value at an offest of 'index' from the given node
    static void insert(const Type& val, Node*& pos, const int offset = 0) {
        Node** curr = &pos, ** next = nullptr;
        for (int i = 0; i < offset; i++) {
            if (!(*curr)) break;
            curr = &((*curr)->next);
        }
        next = curr;
        *curr = new Node(val, *next);
    }
    // removes value at an offest of 'index' from the given node
    static void remove(Node*& pos, const int offset = 0) {
        Node** curr = &pos, * next = nullptr;
        for (int i = 0; i < offset; i++) {
            if (!(*curr)->next) break;
            curr = &((*curr)->next);
        }
        next = (*curr)->next;
        delete *curr;
        *curr = next;
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
    
    // list traversal
    template <typename Lambda>
    static void traverse(Node*& h, Lambda&& function) {
        if (!h) return;
        function(h->val);
        traverse(h->next, std::forward<Lambda>(function));
    }

public:
    class Iterator {
    private:
        Node* ptr = nullptr;
        friend class ForwardList<Type>;

        Iterator(Node* p) : ptr(p) {}

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
        int& operator*() { return ptr->val; }
    };
    
    // make copy, move, init constructors and a = operator
    ForwardList(Node* h = nullptr, const int s = 0) : head(h), size(s) {}
    // move constructor
    ForwardList(ForwardList&& other) : head(other.head), size(other.size) { 
        other.head = nullptr;
        other.size = 0;
    }
    // copy constructor
    ForwardList(const ForwardList& other) {
        head = new Node(other.head->val);
        Node* curr = head, *ocurr  = other.head->next;
        while (ocurr) {
            curr->next = new Node(ocurr->val);
            ocurr = ocurr->next;
            curr = curr->next;
        }
        size = other.size;
    }
    // initializer list constructor
    ForwardList(std::initializer_list<Type> list) {
        size = list.size();
        for (auto elem : list) { insert(elem, head, size); }
    }
    // destructor
    ~ForwardList() { clear(); }
    // assignment operator
    ForwardList& operator=(const ForwardList& other) {
        if (*this != other) {
            ForwardList obj(other);
            std::swap(head, other.head);
            std::swap(size, other.size);
        }
        return *this;
    }
    // equality operator
    bool operator==(const ForwardList& other) {
        if (size != other.size) return 0;
        return sameas(head, other.head);
    }
    // inequality operator
    bool operator!=(const ForwardList& other) { return !(*this == other); }

    // returns size of list
    int Size() const { return size; }
    // returns if list is empty
    bool empty() const { return size == 0; }
    // returns if given value found in list
    bool search(const Type& val) { return find(head, val); }

    // appends value to the end of list
    void push_back(const Type& val) { insert(val, head, size); size++; }
    // prepends value to the front of list
    void push_front(const Type& val) { insert(val, head); size++; }
    // inserts value at given index
    void insert(const Type& val, const int index) { insert(val, head, index); size++; }

    // removes the value at front of list
    void pop_front() { remove(head); size--;  }
    // removes value at end of list
    void pop_back() { remove(head, size); size--; }
    // removes value at given index
    void remove(const int index) { remove(head, index); size--; }
    
    // wipes clear all the data in list
    void clear() { 
        clear(head); 
        head = nullptr; 
        size = 0;
    }
    // traverses through the list, applying the given function
    void traverse(std::function<void(const Type&)> func = printL) { traverse(head, func); }
    // prints the list data - to help visualize 
    void print() { traverse(); }

    // returns value at front of list
    const Type& front() const { return head->val; }
    // returns value at end of list
    const Type& back() const {
        const Node* const* end = fetch(&head, size);
        return (*end)->val;
	}
    // returns value at given index
    const Type& operator[](int index) const {
        const Node* const* node = fetch(&head, index);
        if (!(*node)) throw std::exception("INVALID INDEX.");
        return (*node)->val;
    };
    
    // returns iterator to the head(first) node in list
    Iterator begin() { return Iterator(head); }
    // returns iterator to the last node in list
    Iterator end() { return Iterator(nullptr); }
};
// definition of print lambda
template <typename Type>
std::function<void(const Type&)> ForwardList<Type>::printL = [](const Type& data) { std::cout << data << "-> "; };


#endif
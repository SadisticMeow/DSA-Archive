#ifndef _PYLIST
#define _PYLIST

#include<iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include "Container.h"

using LL = long long int;

class Pylist {
    std::vector<std::shared_ptr<Box>> data;

    // isolates foremost argument and adds it, then recurses
    template<typename T, typename...ARGS>
    void recursiveAdd(T iso, ARGS...pac) {
        append(iso);
        recursiveAdd(pac...);
    }
    // base case for above method - hits when no arguments left
    void recursiveAdd() {}
    // prints contents of pylist - to help the ostream operator
    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < data.size(); i++) {
            data[i]->print();
            if (i < data.size() - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
public:
    // kind of an initializer list constructor - uses variadic templates (variable number of arbitary type arguments)
    template<typename...ARGS>
    Pylist(ARGS...args) { recursiveAdd(args...); }
    // appends value to end of pylist
    template <typename T>
    void append(const T& val) {
        std::shared_ptr<Box> ptr = std::make_shared<Boxed<T>>(val);
        data.push_back(ptr);
    }
    // extends pylist by appending all elements of another given pylist
    void extend(const Pylist& other) {
        std::size_t lim = data.size();
        std::size_t otherLim = other.data.size();
        data.resize(lim + otherLim);
        for (std::size_t i = 0; i < otherLim; i++) {
            data[lim + i] = other.data[i];
        }
    }
    // inserts given value at given index
    template <typename T>
    void insert(LL i, const T& val) {
        if (i > data.size() - 1) throw std::invalid_argument("index does not exist");
        if (i < 0) i = i % data.size();
        auto ptr = std::make_shared<Boxed<T>>(val);
        data.insert(data.begin() + i, ptr);
    }
    // sets the given value at given index - replaces
    template <typename T>
    void setitem(std::size_t i, const T& val) {
        if (i > data.size() - 1) throw std::invalid_argument("index does not exit");
        if (i < 0) i = i % data.size();
        data[i] = std::make_shared<Boxed<T>>(val);
    }
    // removes last value or value at given index
    std::shared_ptr<Box> pop(LL i = -1) {
        if (i > (LL)data.size() - 1) throw std::invalid_argument("index does not exist");
        if (i < 0) i = i % data.size();
        data.erase(data.begin() + i);
        if (data.size() == 0) return nullptr;
        if (i < data.size()) return data[i];
        else return data[data.size() - 1];
    }
    // removes given value from pylist
    template <typename T>
    void remove(const T& val) {
        int idx = index(val);
        pop(idx);
    }
    
    // returns count of occurances of value within pylist
    template <typename T>
    int count(const T& val) const {
        int count = 0;
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i]->type() != typeid(val)) continue;
            std::shared_ptr<Boxed<T>> ptr = std::dynamic_pointer_cast<Boxed<T>>(data[i]);
            if (ptr->getVal() == val) count++;
        }
        return count;
    }
    // returns size/length of pylist
    std::size_t len() const { return data.size(); }
    // returns index of given value if found within pylist
    template <typename T>
    int index(const T& val) const {
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i]->type() != typeid(val)) continue;
            std::shared_ptr<Boxed<T>> ptr = std::dynamic_pointer_cast<Boxed<T>>(data[i]);
            if (ptr->getVal() == val) return i;
        }
        throw std::invalid_argument("not found");
    }
    // returns if pylist contains given value
    template <typename T>
    bool contains(const T& val) const {
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i]->type() != typeid(val)) continue;
            std::shared_ptr<Boxed<T>> ptr = std::dynamic_pointer_cast<Boxed<T>>(data[i]);
            if (ptr->getVal() == val) return 1;
        }
        return 0;
    }
    
    // reverses the order of elements within pylist
    void reverse() { std::reverse(data.begin(), data.end()); }
    // sorts pylist in ascending order unless given reverse
    void sort(bool reverse = false) {
        auto comparator = [](const std::shared_ptr<Box>& a, const std::shared_ptr<Box>& b) -> bool {
            return a->less(*b);
        };

        if (reverse) {
            std::sort(data.begin(), data.end(),
                [&comparator](const auto& a, const auto& b) {
                    return comparator(b, a);
                });
        }
        else std::sort(data.begin(), data.end(), comparator);
    }
    // wipes the pylist clear
    void clear() { data.clear(); }
    // returns a copy of this pylist
    Pylist copy() const {
        Pylist n;
        n.data.resize(data.size());
        for (std::size_t i = 0; i < data.size(); i++) {
            n.data[i] = data[i];
        }
        return n;
    }
    // returns a pylist as a slice of this pylist defined by given start/end values
    Pylist slice(LL start, LL end) const {
        LL _size = data.size() - 1, _diff = 0;
        Pylist n;

        if (start > _size || end > _size) throw std::invalid_argument("index does not exist");
        if (start < 0) start = (start % data.size());
        if (end < 0) end = (end % data.size());

        _diff = end - start;
        if (_diff <= 0) return n;
        n.data.resize(_diff);

        for (LL i = 0; i < _diff; i++) {
            n.data[i] = data[start + i];
        }
        return n;
    }
    
    // returns the union of this pylist with the given pylist
    Pylist operator+(const Pylist& other) const {
        Pylist c = copy();
        c.extend(other);
        return c;
    }
    // returns if this pylist is smaller than the given one
    bool operator<(const Pylist& other) const{
        if (data.size() < other.data.size()) return 1;
        return 0;
    }
    // returns if this pylist is larger than the given one
    bool operator>(const Pylist& other) const {
        if (data.size() > other.data.size()) return 1;
        return 0;
    }
    // returns if this pylist equal to the given one (in size and elements)
    bool operator==(const Pylist& other) const {
        if (data.size() != other.data.size()) return 0;
        for (std::size_t i = 0; i < data.size(); i++) {
            if (data[i] != other.data[i]) return 0;
        }
        return 1;
    }
    // returns if this pylist not equal to the given one (in size and elements)
    bool operator!=(const Pylist& other) const{ return !(*this == other); }
    // getter - returns the pointer at given index
    std::shared_ptr<Box> operator[](size_t i) const {
        if (i > data.size() - 1) throw std::invalid_argument("index does not exit");
        if (i < 0) i = i % data.size();
        return data[i];
    }

    // returns iterator to starting position of pylist
    auto begin() { return data.begin(); }
    // returns iterator to just beyond the last position of pylist
    auto end() { return data.end(); }
    // returns iterator to last position of pylist
    auto rbegin() { return data.rbegin(); }
    // returns iterator to just beyond the starting position of pylist
    auto rend() { return data.rend(); }
    
    // ostream operator - to print pylist easily
    friend std::ostream& operator<<(std::ostream& os, const Pylist& p) {
        p.print();
        return os;
    }
};

#endif

#ifndef _CONTAINER
#define _CONTAINER

#include <typeinfo>


// abstract class
class Box {
public:
    // virtual destructor
    virtual ~Box() = default;
    // must have methods for child classes
    virtual void print() const = 0;
    virtual const std::type_info& type() const = 0;
    virtual bool less(const Box& other) const = 0;
};

template <typename T>
class Boxed : public Box {
    // to prevent static arrays
    static_assert(!std::is_array<T>::value, "Static arrays are not supported");

    T value;

public:
    // constructor
    Boxed(const T& v) : value(v) {}
    // prints the value held inside Boxed
    void print() const override { std::cout << value; }
    // returns id for the type of value held within Boxed
    const std::type_info& type() const override { return typeid(value); }
    // compares if given Boxed object holds lesser type than this one  
    bool less(const Box& other) const override {
        if (type().name() > other.type().name()) return 1;
        if (type().name() == other.type().name()) {
            auto obj = dynamic_cast<const Boxed<T>*>(&other);
            if (value < obj->getVal()) return 1;
        }
        return 0;
    }
    // rerturns value within Boxed - read only
    T getVal() const { return value; }
};


#endif

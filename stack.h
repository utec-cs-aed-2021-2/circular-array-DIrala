#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
public:
    void push(T data){this->push_back(data); }
    T pop(){return this->pop_back();}
};
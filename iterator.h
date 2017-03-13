#ifndef ITERATOR_H
#define ITERATOR_H
#include"cap.h"

//!
//! \brief The Iterator class iterators for
//!
template < typename T >
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Iterator(T* ptr) :
        ptr_(ptr)
    {}

    Iterator& operator ++()
    {
        ++ptr_;
        return *this;
    }

    T& operator *()
    {
        return *ptr_;
    }

    bool operator !=(const Iterator& rhs) const
    {
        return ptr_ != rhs.ptr_;
    }
private:
    T* ptr_;
};

#endif // ITERATOR_H

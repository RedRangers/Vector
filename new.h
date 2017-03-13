#ifndef NEW_H
#define NEW_H

#include"cap.h"

void* operator new( size_t size, size_t n, int init )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    void* p = malloc( size*n );
    memset( p, init, size*n );

    std::cout << "adress: " << p << std::endl;

    return p;
}


#endif // NEW_H

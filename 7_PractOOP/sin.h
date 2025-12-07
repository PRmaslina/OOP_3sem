#ifndef SIN_H
#define SIN_H

#include "function.h"
#include "array.h"

template<typename T>
class Sin : public Function<T>
{
public:
    Sin(int accuracy) : Function<T>(Array<double>({0,1,0,-1}), accuracy){
    }
};

#endif // SIN_H

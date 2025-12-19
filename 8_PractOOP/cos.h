#ifndef COS_H
#define COS_H

#include "function.h"
#include "array.h"

template <typename T>
class Cos : public Function<T>
{
public:
    Cos(int accuracy) : Function<T>(Array<double>({1,0,-1,0}), accuracy){
    }
};

#endif // COS_H

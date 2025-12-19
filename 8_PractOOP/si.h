#ifndef SI_H
#define SI_H

#include "function.h"
#include "array.h"

template<typename T>
class Si : public Function<T>
{
public:
    Si(int accuracy) : Function<T>(Array<double>({0,1,0,-1}), accuracy){
    }

    T solve(T x) {
        if(x == 0)
            return 1;
        return Polynom<T>::solve(x)/x;
    }

};


#endif // SI_H

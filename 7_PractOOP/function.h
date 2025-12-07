#ifndef FUNCTION_H
#define FUNCTION_H

#include "polynom.h"
#include "array.h"
#include <QString>

template<typename T>
class Function : public Polynom<T>
{

public:
    double factorial(double x){
        double a = 1;
        for(double i = 2; i <= x; i++){
            a*=i;
        }
        return a;
    }
    Array<T> makloren(Array<double>& zeroValues, int accuracy){
        Array<T> coeffs(accuracy);
        double g;
        double a;
        double b;
        double c;
        for(int i = 0; i < accuracy; i++){
            a = zeroValues.get(i%zeroValues.getSize());
            b = factorial(i);
            c = a/b;
            g = zeroValues.get(i%zeroValues.getSize())/factorial(i);
            coeffs.put(i,zeroValues.get(i%zeroValues.getSize())/factorial(i));
        }
        return coeffs;
    }
    Function(Array<double> zeroValues, int accuracy) : Polynom<T>(makloren(zeroValues, accuracy))
    {}
};

#endif // FUNCTION_H

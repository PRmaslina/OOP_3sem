#ifndef POLYNOM_H
#define POLYNOM_H

#include "number.h"
#include "array.h"
#include <QString>

class Polynom
{
    int degree;
    Array coeffs;
    Array roots;
    void calcCoeffs(number, Array);
    int printType;
public:
    Polynom();
    Polynom(number, Array);

    number getCoeff(int);
    number getRoot(int);
    number solve(number);
    int getDegree();
    void setPrintType(int);
    int getPrintType();
    friend QString outputString(Polynom);
    friend void inputString(QString,QString, Polynom*);
};

#endif

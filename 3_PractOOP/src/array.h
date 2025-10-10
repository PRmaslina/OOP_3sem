#ifndef ARRAY_H
#define ARRAY_H

#include "number.h"

class Array
{
    int size;
    number* arr;
    
public:
    Array();
    Array(int newSize, number* newArr);
    ~Array();
    
    int getSize();
    void changeSize(int newSize);
    void cinNumber(int place);
    void coutNumber(int place);
    number calcAverage();
    number calcStandardDeviation();
    void sort(bool Direction = true);

    number get(int);
    void put(int, number);
    void append(number);
    int find(number);
};

#endif

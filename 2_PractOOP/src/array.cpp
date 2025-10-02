#include <iostream>
#include <ncurses.h>
#include <cmath>
#include "array.h"

Array::Array() {
    size = 0;
    arr = nullptr;
}

Array::Array(int newSize, number* newArr) {
    size = newSize;
    arr = new number[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = newArr[i];
    }
}

Array::~Array() {
    delete[] arr;
}

int Array::getSize(){
    return size;
}

void Array::changeSize(int newSize){
    number* newArr = new number[newSize];
    for(int i = 0; i < (newSize > size ? size : newSize) ; i++){
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}

void Array::cinNumber(int place){
    scanw("%lf", &arr[place]);
}

void Array::coutNumber(int place){
    printw("%lf", arr[place]);
}

number Array::calcAverage(){
    number avr = 0;
    for(int i = 0; i < size; ++i){
        avr = avr + arr[i];
    }
    avr = avr / size;
    return avr;
}

number Array::calcStandardDeviation() {
    number StandardDeviation = 0;
    if (size == 0) 
        return StandardDeviation;
    
    number average = calcAverage();
    number sumSquaredDifferences = 0;
    
    for (int i = 0; i < size; i++) {
        number difference = arr[i] - average;
        sumSquaredDifferences += difference * difference;
    }
    
    StandardDeviation = sumSquaredDifferences / size;
    return sqrt(StandardDeviation);
}

void Array::sort(bool Direction) {
    for (int start = 1; start < size; ++start) {
        int stepCount = 0;
        while (start - stepCount > 0 && (Direction == (arr[start - stepCount] < arr[start - 1 - stepCount]))) {
            std::swap(arr[start - stepCount], arr[start - 1 - stepCount]);
            ++stepCount;
        }
    }
}

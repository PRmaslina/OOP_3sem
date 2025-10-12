#include <iostream>
#include <ncurses.h>
#include <cmath>
#include "array.h"

Array::Array() {
    size = 0;
    arr = nullptr;
}

Array::Array(int newSize) {
    size = newSize;
    arr = new number[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = 0;
    }
}

Array::Array(int newSize, number* newArr) {
    size = newSize;
    arr = new number[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = newArr[i];
    }
}


Array::Array(const Array& other) {
    size = other.size;
    arr = new number[size];
    for(int i = 0; i < size; i++){
        arr[i] = other.arr[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] arr;        
        size = other.size;
        arr = new number[size];
        for(int i = 0; i < size; i++){
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

Array::~Array() {
    delete[] arr;
    arr = nullptr;
}

int Array::getSize(){
    return size;
}

void Array::changeSize(int newSize){
    number* newArr = new number[newSize];
    int copySize = (newSize > size ? size : newSize);
    
    for(int i = 0; i < copySize; i++){
        newArr[i] = arr[i];
    }
    // Инициализируем новые элементы нулями
    for(int i = copySize; i < newSize; i++){
        newArr[i] = 0;
    }
    
    delete[] arr;
    arr = newArr;
    size = newSize;
}

void Array::append(number a) {
    int newSize = size + 1;
    changeSize(newSize);
    put(newSize - 1, a);
}


number Array::get(int i) {
    return arr[i];
}

void Array::put(int i, number a) {
    arr[i] = a;
}

int Array::find(number a) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == a) return i;
    }
    return -1;
}
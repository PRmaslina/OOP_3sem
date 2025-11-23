#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array
{
    int size;
    T* arr;

public:
    Array();
    Array(int newSize);
    Array(int newSize, T* newArr);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    int getSize();
    void changeSize(int newSize);
    T get(int);
    void put(int, T);
    void append(T);
    int find(T);
};

// Реализация шаблона в заголовочном файле
template<typename T>
Array<T>::Array() {
    size = 0;
    arr = nullptr;
}

template<typename T>
Array<T>::Array(int newSize) {
    size = newSize;
    arr = new T[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = T(0);
    }
}

template<typename T>
Array<T>::Array(int newSize, T* newArr) {
    size = newSize;
    arr = new T[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = newArr[i];
    }
}

template<typename T>
Array<T>::Array(const Array& other) {
    size = other.size;
    arr = new T[size];
    for(int i = 0; i < size; i++){
        arr[i] = other.arr[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] arr;
        size = other.size;
        arr = new T[size];
        for(int i = 0; i < size; i++){
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template<typename T>
Array<T>::~Array() {
    delete[] arr;
    arr = nullptr;
}

template<typename T>
int Array<T>::getSize(){
    return size;
}

template<typename T>
void Array<T>::changeSize(int newSize){
    T* newArr = new T[newSize];
    int copySize = (newSize > size ? size : newSize);

    for(int i = 0; i < copySize; i++){
        newArr[i] = arr[i];
    }
    for(int i = copySize; i < newSize; i++){
        newArr[i] = T(0);
    }

    delete[] arr;
    arr = newArr;
    size = newSize;
}

template<typename T>
void Array<T>::append(T a) {
    int newSize = size + 1;
    changeSize(newSize);
    put(newSize - 1, a);
}

template<typename T>
T Array<T>::get(int i) {
    return arr[i];
}

template<typename T>
void Array<T>::put(int i, T a) {
    arr[i] = a;
}

template<typename T>
int Array<T>::find(T a) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == a) return i;
    }
    return -1;
}

#endif

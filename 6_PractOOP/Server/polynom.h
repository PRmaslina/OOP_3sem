#ifndef POLYNOM_H
#define POLYNOM_H

#include "array.h"
#include <QString>

template<typename T>
class Polynom
{
    int degree;
    Array<T> coeffs;
    Array<T> roots;
    void calcCoeffs(T, Array<T>);
    int printType;
public:
    Polynom();
    Polynom(T, Array<T>);

    T getCoeff(int);
    T getRoot(int);
    T solve(T);
    int getDegree();
    void setPrintType(int);
    int getPrintType();
};

template<typename T>
QString outputString(Polynom<T> p);

template<typename T>
void inputString(QString, QString, Polynom<T>* p);

// Реализация шаблона Polynom
template<typename T>
Polynom<T>::Polynom() {
    coeffs = Array<T>(1);
    roots = Array<T>(1);
    degree = 0;
    printType = 1;
}

template<typename T>
Polynom<T>::Polynom(T a, Array<T> _roots) {
    roots = _roots;
    degree = roots.getSize();
    coeffs = Array<T>(degree + 1);
    calcCoeffs(a, roots);
    printType = 1;
}

template<typename T>
void Polynom<T>::calcCoeffs(T a, Array<T> _roots) {
    int n = _roots.getSize();
    degree = n;

    Array<T> coeffsTemp(n + 1);
    for (int i = 0; i <= n; i++) coeffsTemp.put(i, T(0));

    coeffsTemp.put(n, a);

    for (int k = 0; k < n; k++) {
        T root = _roots.get(k);

        for (int i = n - k; i <= n; i++) {
            T prevCoeff = (i > 0 ? coeffsTemp.get(i - 1) : T(0));
            T newCoeff = prevCoeff - coeffsTemp.get(i) * root;
            coeffsTemp.put(i - 1, newCoeff);
        }
    }

    coeffs.changeSize(n + 1);
    for (int i = 0; i <= n; i++) {
        coeffs.put(i, coeffsTemp.get(i));
    }
}

template<typename T>
T Polynom<T>::getCoeff(int n) {
    return coeffs.get(n);
}

template<typename T>
T Polynom<T>::getRoot(int n) {
    return roots.get(n);
}

template<typename T>
T Polynom<T>::solve(T x) {
    T solution = coeffs.get(degree);
    for (int i = 0; i < degree; i++) {
        solution = solution * (x - roots.get(i));
    }
    return solution;
}

template<typename T>
int Polynom<T>::getDegree() {
    return degree;
}

template<typename T>
void Polynom<T>::setPrintType(int type) {
    if (type == 1 || type == 2) {
        printType = type;
    }
}

template<typename T>
int Polynom<T>::getPrintType() {
    return printType;
}

#endif

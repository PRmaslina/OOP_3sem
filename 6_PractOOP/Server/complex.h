#ifndef COMPLEX_H
#define COMPLEX_H

#include <QString>

class TComplex
{
    double real;
    double imag;

public:
    // Конструкторы
    TComplex();
    TComplex(double);
    TComplex(double,double);
    // получение значений
    double getReal() const;  // Добавить const
    double getImag() const;  // Добавить const
    // постановка значений
    void putReal(double);
    void putImag(double);
    // операторы сравнения
    bool operator >(const TComplex&) const;
    bool operator <(const TComplex&) const;
    // операторы +- * / для TComplex
    TComplex operator +(const TComplex&) const;
    TComplex operator -(const TComplex&) const;
    TComplex operator *(const TComplex&) const;
    TComplex operator /(const TComplex&) const;
    // операторы +- * / для TComplex и double
    TComplex operator +(const double&) const;
    TComplex operator -(const double&) const;
    TComplex operator *(const double&) const;
    TComplex operator /(const double&) const;
    // операторы присваивания TComplex и TComplex
    TComplex& operator +=(const TComplex&);
    TComplex& operator -=(const TComplex&);
    TComplex& operator *=(const TComplex&);
    TComplex& operator /=(const TComplex&);
    // операторы присваивания TComplex и double
    TComplex& operator +=(const double&);
    TComplex& operator -=(const double&);
    TComplex& operator *=(const double&);
    TComplex& operator /=(const double&);
    TComplex& operator = (const double&);
    bool operator ==(const TComplex&);
    friend TComplex sqrt(TComplex T);

    TComplex getConj();
};

QString complexOut(TComplex &);
TComplex toComplex(QString);

#endif

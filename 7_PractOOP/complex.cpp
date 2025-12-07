#include "complex.h"
#include <QString>
#include <cmath>

// конструкторы

TComplex::TComplex(){
    real = 0;
    imag = 0;
}

TComplex::TComplex(double r){
    real = r;
    imag = 0;
}

TComplex::TComplex(double r, double i){
    real = r;
    imag = i;
}

// получение значений

double TComplex::getReal() const {
    return real;
}

double TComplex::getImag() const {
    return imag;
}

// постановка значений

void TComplex::putReal(double r){
    real = r;
}

void TComplex::putImag(double i){
    imag = i;
}

// операторы сравнения

bool TComplex::operator >(const TComplex &T) const {
    return (real*real + imag*imag) > (T.real*T.real + T.imag*T.imag);
}

bool TComplex::operator <(const TComplex &T) const {
    return (real*real + imag*imag) < (T.real*T.real + T.imag*T.imag);
}

// операторы + - * / для TComplex

TComplex TComplex::operator +(const TComplex&T) const {
    return TComplex(real + T.real, imag + T.imag);
}

TComplex TComplex::operator -(const TComplex&T) const {
    return TComplex(real - T.real, imag - T.imag);
}

TComplex TComplex::operator *(const TComplex&T) const {
    return TComplex(real * T.real - imag * T.imag, real * T.imag + imag * T.real);
}

TComplex TComplex::operator /(const TComplex&T) const {
    double den = T.real*T.real + T.imag*T.imag;
    return TComplex((real * T.real + imag * T.imag)/den,
                    (imag * T.real - real * T.imag)/den);
}

// операторы + - * / для TComplex и double

TComplex TComplex::operator +(const double&D) const {
    return TComplex(real + D, imag);
}

TComplex TComplex::operator -(const double&D) const {
    return TComplex(real - D, imag);
}

TComplex TComplex::operator *(const double&D) const {
    return TComplex(real * D, imag * D);
}

TComplex TComplex::operator /(const double&D) const {
    return TComplex(real / D, imag / D);
}

// операторы присваивания TComplex и TComplex

TComplex& TComplex::operator +=(const TComplex&T){
    real += T.real;
    imag += T.imag;
    return *this;
}

TComplex& TComplex::operator -=(const TComplex&T){
    real -= T.real;
    imag -= T.imag;
    return *this;
}

TComplex& TComplex::operator *=(const TComplex&T){
    double oldReal = real;
    real = real * T.real - imag * T.imag;
    imag = oldReal * T.imag + imag * T.real;
    return *this;
}

TComplex& TComplex::operator /=(const TComplex&T){
    double oldReal = real;
    double oldImag = imag;
    double den = T.real * T.real + T.imag * T.imag;
    real = (oldReal * T.real + oldImag * T.imag) / den;
    imag = (oldImag * T.real - oldReal * T.imag) / den;

    return *this;
}

// операторы присваивания TComplex и double

TComplex& TComplex::operator +=(const double&D){
    real += D;
    return *this;
}

TComplex& TComplex::operator -=(const double&D){
    real -= D;
    return *this;
}

TComplex& TComplex::operator *=(const double&D){
    real *= D;
    imag *= D;
    return *this;
}

TComplex& TComplex::operator /=(const double&D){
    real /= D;
    imag /= D;
    return *this;
}

TComplex& TComplex::operator =(const double&D){
    real = D;
    imag = 0;
    return *this;
}

bool TComplex::operator==(const TComplex& T) {
    return real == T.getReal() && imag == T.getImag();
}

//Корень

TComplex sqrt(TComplex T) {
    double rValue = std::sqrt(T.getReal() * T.getReal() + T.getImag() * T.getImag());
    double theta = std::atan2(T.getImag(), T.getReal()) / 2.0;
    return TComplex(rValue * std::cos(theta), rValue * std::sin(theta));
}

// ввод-вывод

TComplex toComplex(QString text) {
    TComplex T;
    QString number = "";
    text+= " ";
    text.replace("-i", "-1i").replace("+i", "+1i");
    for(int i = 0; i < text.length()-1; i++){
        if(text[i] == '-'){
            number+=text[i];
        }else if ((text[i].isDigit() || text[i]=='.') && !(text[i+1].isDigit() || text[i+1]=='.')){
            number+=text[i];
            if(!(text[i+1] == 'i')){
                T.putReal(number.toDouble());
            }else{
                T.putImag(number.toDouble());
                break;
            }
            number = "";
        }else if ((text[i].isDigit() || text[i]=='.')){
            number+=text[i];
        }
    }
    return T;
}


QString complexOut(TComplex T) {
    double real = T.getReal();
    double imag = T.getImag();
    QString out = "";
    const double EPS = 1e-9;
    if (std::fabs(real) < EPS && std::fabs(imag) < EPS) {
        out+="0";
    }
    else if (std::fabs(imag) < EPS) {
        out+= QString::number(real);
    }
    else if (std::fabs(real) < EPS) {
        out+=QString::number(imag) + "i";
    }
    else {
        if (imag > 0){
            out+=QString::number(real) + "+" + QString::number(imag) + "i";
        } else {
            out+= QString::number(real) + QString::number(imag) + "i";
        }
    }
    return out;
}


TComplex TComplex::getConj() {
    return TComplex(real, -imag);
}

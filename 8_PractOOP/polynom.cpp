#include "polynom.h"
#include "complex.h"
#include <QString>
#include <QStringList>
#include <cmath>
#include <QDebug>

// Специализированные функции вывода для разных типов
template<>
QString outputString(Polynom<double> p) {
    double coeff;
    QString out = "";
    switch (p.getPrintType()) {
    case 1: {
        int n = p.getDegree();
        double coeff = p.getCoeff(n);
        out += QString::number(coeff);
        out += "*x^" + QString::number(n);

        for (int i = n - 1; i >= 0; i--) {
            coeff = p.getCoeff(i);
            if (coeff == 0.0) continue;

            out += " + ";
            out += QString::number(coeff);

            if (i > 0)
                out+="*x";
            if (i > 1)
                out+="^" + QString::number(i);
        }
        break;
    }
    case 2: {
        double a = p.getCoeff(p.getDegree());
        out += QString::number(a);

        for (int i = 0; i < p.getDegree(); i++) {
            double root = p.getRoot(i);
            out +=" * (x - " + QString::number(root) + ")";
        }
        break;
    }
    }
    return out;
}

template<>
QString outputString(Polynom<TComplex> p) {
    TComplex coeff;
    QString out = "";
    switch (p.getPrintType()) {
    case 1: {
        int n = p.getDegree();
        TComplex coeff = p.getCoeff(n);
        out += complexOut(coeff);
        out += "*x^" + QString::number(n);

        for (int i = n - 1; i >= 0; i--) {
            coeff = p.getCoeff(i);
            if (coeff == TComplex(0.0)) continue;

            out += " + (";
            out += complexOut(coeff);
            out +=")";

            if (i > 0)
                out+="*x";
            if (i > 1)
                out+="^" + QString::number(i);
        }
        break;
    }
    case 2: {
        TComplex a = p.getCoeff(p.getDegree());
        out += complexOut(a);

        for (int i = 0; i < p.getDegree(); i++) {
            TComplex root = p.getRoot(i);
            out +=" * (x - (";
            out += complexOut(root);
            out +="))";
        }
        break;
    }
    }
    return out;
}

// Специализированные функции ввода
template<>
void inputString(QString aText, QString text, Polynom<double>* p) {
    Array<double> roots;
    double a = aText.toDouble();
    QStringList list = text.split(" ");
    int n = list[0].toInt();
    list.removeAt(0);
    double root;
    for (int i = 0; i < n; i++) {
        root = list[i].toDouble();
        roots.append(root);
    }

    *p = Polynom<double>(a, roots);
}

template<>
void inputString(QString aText, QString text, Polynom<TComplex>* p) {
    Array<TComplex> roots;
    TComplex a = toComplex(aText);
    QStringList list = text.split(" ");
    int n = list[0].toInt();
    list.removeAt(0);
    TComplex root;
    for (int i = 0; i < n; i++) {
        root = toComplex(list[i]);
        roots.append(root);
    }

    *p = Polynom<TComplex>(a, roots);
}

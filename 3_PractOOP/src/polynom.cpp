#include <ncurses.h>
#include "polynom.h"
#include <iostream>
#include <string>
#include <cmath>

Polynom::Polynom() {
    coeffs = Array(1);
    roots = Array(1);
    degree = 0;
    printType = 1;
}

Polynom::Polynom(number a, Array _roots) {
    roots = _roots;
    degree = roots.getSize();
    coeffs = Array(degree + 1);
    calcCoeffs(a, roots);
    printType = 1;
}

void Polynom::calcCoeffs(number a, Array _roots) {
    int n = _roots.getSize();
    degree = n;

    Array coeffsTemp(n + 1);
    for (int i = 0; i <= n; i++) coeffsTemp.put(i, 0.0);

    coeffsTemp.put(n, a);

    for (int k = 0; k < n; k++) {
        number root = _roots.get(k);

        for (int i = n - k; i <= n; i++) {
            number prevCoeff = (i > 0 ? coeffsTemp.get(i - 1) : 0.0);
            number newCoeff = prevCoeff - coeffsTemp.get(i) * root;
            coeffsTemp.put(i - 1, newCoeff);
        }
    }

    coeffs.changeSize(n + 1);
    for (int i = 0; i <= n; i++) {
        coeffs.put(i, coeffsTemp.get(i));
    }
}

number Polynom::getCoeff(int n) {
    return coeffs.get(n);
}

number Polynom::getRoot(int n) {
	return roots.get(n);
}

number Polynom::solve(number x) {
    number solution = coeffs.get(degree);
    for (int i = 0; i < degree; i++) {
        solution *= x - roots.get(i);
    }
    return solution;
}


int Polynom::getDegree() {
    return degree;
}

void Polynom::setPrintType(int type) {
    if (type == 1 || type == 2) {
        printType = type;
    }
}

int Polynom::getPrintType() {
    return printType;
}

void printw(const char* _, Polynom p) {
	number coeff;
    switch (p.getPrintType()) {
    case 1: {
		int n = p.getDegree();
		number coeff = p.getCoeff(n);
		printw("", coeff);
		printw("*x^%d", n);

		for (int i = n - 1; i >= 0; i--) {
			coeff = p.getCoeff(i);
			if (coeff == 0.0) continue;

			printw(" + (");
			printw("", coeff);
			printw(")");

			if (i > 0)
				printw("*x");
			if (i > 1)
				printw("^%d", i);
    	}
    }
        break;
    case 2: {
        
        number a = p.getCoeff(p.getDegree());
        printw("", a);
        
        for (int i = 0; i < p.getDegree(); i++) {
            number root = p.getRoot(i);
            printw(" * (x - ("); printw("", root); printw("))");
        }
        break;
    }
    }
}

void scanw(const char* _, Polynom* p) {
    number a;
    Array roots;
    int n;
    
    scanw("%lf", &a);     
    scanw("%d", &n);
    
    for (int i = 0; i < n; i++) {
        number root;
        scanw("", &root);
        roots.append(root);
    }
    
    *p = Polynom(a, roots);
}
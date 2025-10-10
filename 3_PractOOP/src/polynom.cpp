#include <ncurses.h>
#include "polynom.h"
#include <iostream>
#include <string>
#include <cmath>

Polynom::Polynom() {
	coeffs = Array();
	coeffs.append(0);
	roots = Array();
	roots.append(0);
	degree = 0;
}

Polynom::Polynom(number a, Array _roots) {
	coeffs = Array();
	roots = Array();
	for (int i = 0; i < _roots.getSize(); i++) {
		roots.append(_roots.get(i));
	}
	for (int i = 0; i < _roots.getSize(); i++) {
		number elem = _roots.get(i);
		if (roots.find(elem.getConj()) < 0) roots.append(elem.getConj());
	}
	coeffs.changeSize(roots.getSize());
	calcCoeffs(a, roots);
	degree = roots.getSize();
}

number Polynom::getCoeff(int n) {
	return coeffs.get(n);
}

number Polynom::getRoot(int n) {
	return roots.get(n);
}

number Polynom::solve(number x) {
	number solution = coeffs.get(degree);
	for (int i = 0; i < degree; i++) solution *= x - roots.get(i);
	return solution;	
}

void Polynom::calcCoeffs(number a, Array _roots) {
	for (int i = 0; i < pow(2, _roots.getSize()); i++) {
		int n = i, k = 0;
		number temp = a;
		for (int j = 0; j < _roots.getSize(); j++) {
			temp = (n % 2) ? _roots.get(j) : 1;
			k += n % 2;
		       	n /= 2;
	       	}
		coeffs.put(k, temp);
	}	
}

void printw(char* _, Polynom p) {
	switch (p.getPrintType()) {
	case 1: {
		for (int i = p.getDegree(); i > 0; i--) {
			printw("("); printw("", p.getCoeff(i)); (i > 1) ? printw(")*x^%d+", i) : printw(")*x+");
		}
		printw("("); printw("", p.getCoeff(0)); printw(")");
		break; }
	case 2: {
		printw("("); printw("", p.getCoeff(p.getDegree())); printw(")");
		for (int i = 0; i < p.getDegree(); i++) {
			printw("(x - ("); printw("", p.getRoot(i)); printw("))");
		}
		break; }
	}
	}

void scanw(char* _, Polynom* p) {
	number a;
	Array roots;
	int n;
	printw("Great coefficient: "); scanw("", &a);
	scanw("Number of roots: %d", &n);
	for (int i = 0; i < n; i++) {
		number root;
		scanw("", &root);
		roots.append(root);
	}
	*p = Polynom(a, roots);
}

int Polynom::getDegree() {
       	return degree;
}

void Polynom::setPrintType(int type) {
	switch(type) {
	case 1:
		printType = 1; break;
	case 2:
		printType = 2; break;
	default: 
		break;
	}	
}

int Polynom::getPrintType() {
	return printType;
}

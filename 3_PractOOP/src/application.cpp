#include <iostream>
#include <string>
#include <ncurses.h>
#include "array.h"
#include "application.h"

ConsoleApp::ConsoleApp() {
    startY = 1;
    countRows = 4;
    menu = new std::string[countRows];
    menu[0] = "Задать полином";
    menu[1] = "Вывести полином";
    menu[2] = "Вычислить значение в точке х";
    menu[3] = "Выйти из приложения";
}

ConsoleApp::~ConsoleApp() {
    delete[] menu;
}

void ConsoleApp::startApp(Polynom& p){
    int end = 1;
    while (end != -1){
        end = choiseMenu(p);
    };
}

int ConsoleApp::choiseMenu(Polynom& p) {
    setlocale(LC_CTYPE, "");
    initscr();
    int size, index;
    int choise = 0;
    int press = 0;
    int x = 0, y = startY;
    if (has_colors() == FALSE){
        endwin();
        printf("Your terminal does not support color\n");
        return -1;
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    refresh();
    move(y, x);
    keypad(stdscr, TRUE);
    while(choise != 6){
    clear();
    y = startY;
    for (int i = 0; i < countRows; ++i, ++y) {
        move(y, x);
        printw("%s",menu[i].c_str());
    }
    y = startY;
    attron(COLOR_PAIR(1));
    move(y, x);
    choise = 0;
    printw("> %s",menu[choise].c_str()); refresh();
    attron(COLOR_PAIR(2));
    press = 0;
    do{
        press = getch();
        switch (press) {
        case KEY_UP:
            move(y, x);
            printw("%s     ",menu[choise].c_str());
            refresh();
            if (choise == 0) {
                choise = countRows - 1;
                y = startY + countRows - 1;
            }
            else {
                choise--;
                y--;
            }
            move(y, x);
            attron(COLOR_PAIR(1));
            printw("> %s",menu[choise].c_str()); refresh();
            attron(COLOR_PAIR(2));
            break;
        case KEY_DOWN:
            move(y, x);
            printw("%s     ",menu[choise].c_str()); refresh();
            if (choise == countRows - 1) {
                choise = 0;
                y = startY;
            }
            else {
                choise++;
                y++;
            }
            move(y, x);
            attron(COLOR_PAIR(1));
            printw("> %s",menu[choise].c_str());
            refresh();
            attron(COLOR_PAIR(2));
            break;
        }
    } while (press != '\n');
    clear();
    
    attron(COLOR_PAIR(2));
    refresh();
    switch (choise)
    {
    case 0: {
       	scanw("", &p); 
        printw("\nНажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        
        break; }
    case 1: {
	int t = 1;
	scanw("Выберите форму вывода [1/2]: %d", &t);
	p.setPrintType(t);
	printw("", p);
        printw("\nНажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        break; }
    case 2: {
	number x;
	printw("Введите значение x: "); refresh(); scanw("", &x);
	printw("p(x) = "); printw("", p.solve(x));
        printw("\nНажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        
        break; }
    }
    }
    endwin();
    return -1;
}

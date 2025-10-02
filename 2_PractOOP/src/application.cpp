#include <iostream>
#include <string>
#include <ncurses.h>
#include "array.h"
#include "application.h"

ConsoleApp::ConsoleApp() {
    startY = 1;
    countRows = 7;
    menu = new std::string[countRows];
    menu[0] = "Задать массив";
    menu[1] = "Рассчитать среднее и СКО элементов массива";
    menu[2] = "Отсортировать массив";
    menu[3] = "Изменить размерность массива";
    menu[4] = "Изменить значение элемента массива";
    menu[5] = "Ввод в консоль элементов текущего объекта массива";
    menu[6] = "Выйти из приложения";
}

ConsoleApp::~ConsoleApp() {
    delete[] menu;
}

void ConsoleApp::startApp(Array& arr){
    int end = 1;
    while (end != -1){
        end = choiseMenu(arr);
    };
}

int ConsoleApp::choiseMenu(Array& arr) {
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
        printw("Введите размер массива\n"); refresh();
        scanw("%d",&size);
        arr.changeSize(size);
        printw("Введите значения массива\n"); refresh();
        for(int i = 0; i < size; ++i){
            printw("Элемент %d: ",i); refresh();
            arr.cinNumber(i);
        }
        printw("Нажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        
        break; }
    case 1: {
	printw("Среднее: "); printw("%lf", arr.calcAverage()); printw("\n");
        printw("СКО: "); printw("%lf", arr.calcStandardDeviation()); printw("\n");
        printw("Нажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        break; }
    case 2: {
	printw("Отсортировать массив в порядке возростания? (Отказ для убывания) (Y/n): "); refresh();
	char cdir = 'Y';
	scanw("%c", &cdir);
	bool dir = !(cdir == 'N');
        arr.sort(dir);
        printw("Отсортированный массив:\n");
        for(int i = 0; i < arr.getSize(); ++i){
            arr.coutNumber(i);
            printw(" ");
        }
        
        printw("\nНажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        
        break; }
    case 3: {
        printw("Введите новый размер массива\n");
        scanw("%d",&size);
        arr.changeSize(size);
	printw("Новый массив: ");
	for (int i = 0; i < size; i++) {
	    arr.coutNumber(i); printw(" ");	
	}
	printw("\n");
        printw("Нажмите любую клавишу для продолжения...");
        refresh();
        getch();
        
        break; }
    case 4: {
        printw("Введите номер элемента для изменения (0-%d): ",arr.getSize()-1); 
        refresh();
        scanw("%d",&index);
        
        if (index >= 0 && index < arr.getSize()) {
            printw("Текущее значение: "); refresh();
            arr.coutNumber(index);
            printw("\nВведите новое значение: "); refresh();
            arr.cinNumber(index);
            printw("Элемент изменен.\n"); refresh();
        } else {
            printw("Неверный индекс!\n"); refresh();
        }
        
        printw("Нажмите любую клавишу для продолжения..."); refresh();
        getch();
        
        break; }
    case 5: {
        printw("Введите номер элемента (0-%d):",arr.getSize()-1); refresh();
        scanw("%d",&index);
        
        if (index >= 0 && index < arr.getSize()) {
            printw("Элемент %d: ",index);
            arr.coutNumber(index);
            printw("\n");
        } else {
            printw("Неверный индекс!\n");
        }
        
        printw("Нажмите любую клавишу для продолжения..."); 
        refresh();
        getch();
        
        break; }
    }
    }
    endwin();
    return -1;
}

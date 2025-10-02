#include <string>
#include "array.h"
#include <ncurses.h>

class ConsoleApp
{
    int countRows;
    int startY;
    std::string* menu;

public:
    ConsoleApp();
    ~ConsoleApp();
    void startApp(Array& arr);
    int choiseMenu(Array& arr);
};

#include <string>
#include "array.h"
#include "polynom.h"
#include <ncurses.h>

class ConsoleApp
{
    int countRows;
    int startY;
    std::string* menu;

public:
    ConsoleApp();
    ~ConsoleApp();
    void startApp(Polynom&);
    int choiseMenu(Polynom&);
};

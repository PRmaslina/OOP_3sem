#include <iostream>
#include "application.h"
#include "array.h"

int main(){
    setlocale(0, "");
    ConsoleApp app;
    Array arr;
    app.startApp(arr);
    return 0;
}
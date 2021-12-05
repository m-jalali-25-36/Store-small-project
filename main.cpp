#include <iostream>
#include <stdlib.h>
#include "class/UnitWorkDb.cpp"
#include "fun/fun.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    UnitWorkDb db(".\\");
    system("cls");
    welcome("Welcome to our store.\n");
    firstPanel(&db);
    return 0;
}

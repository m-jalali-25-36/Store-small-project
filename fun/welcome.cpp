#include <iostream>
#include "../library/delay.cpp"

#pragma once
using namespace std;

void welcome(string message = "Welcome\n")
{
    for (int i = 0; i < message.size(); i++)
    {
        delay(100);
        cout << message[i];
    }
    delay(2000);
}
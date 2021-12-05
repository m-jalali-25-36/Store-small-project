#include <iostream>

using namespace std;

#pragma once

string tolower(string inp)
{
    string result = "";
    for (int i = 0; i < inp.size(); i++)
    {
        if (inp[i] >= 'A' && inp[i] <= 'Z')
            result += inp[i] + 32;
        else
            result += inp[i];
    }

    return result;
}

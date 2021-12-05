#include <iostream>

using namespace std;

#pragma once

string ltrim(string inp)
{
    string result = "";
    bool isFirst = true;
    for (int i = 0; i < inp.size(); i++)
    {
        if (isFirst && inp[i] == ' ')
            continue;
        result += inp[i];
        isFirst = false;
    }
    return result;
}
string rtrim(string inp)
{
    string result = "";
    bool isFirst = true;
    for (int i = inp.size() - 1; i >= 0; i--)
    {
        if (isFirst && inp[i] == ' ')
            continue;
        result = inp[i] + result;
        isFirst = false;
    }
    return result;
}
string trim(string inp)
{
    return ltrim(rtrim(inp));
}

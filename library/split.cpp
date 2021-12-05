#include <iostream>
#include <vector>
#include "trim.cpp"

using namespace std;
#pragma once
vector<string> split(string inp, char spliter)
{
    vector<string> result;
    int lastPos = 0;
    while (lastPos < inp.size())
    {
        size_t findPos = inp.find(spliter, lastPos);
        if (findPos == std::string::npos)
            findPos = inp.size();
        result.push_back(inp.substr(lastPos, findPos - lastPos));
        lastPos = ++findPos;
    }
    return result;
}

vector<string> split(string inp, string spliter)
{
    vector<string> result;
    if (inp == "")
        return result;
    int lastPos = 0;
    while (lastPos < inp.size())
    {
        size_t findPos = inp.find(spliter, lastPos);
        if (findPos == std::string::npos)
            findPos = inp.size();
        result.push_back(trim(inp.substr(lastPos, findPos - lastPos)));
        lastPos = findPos + spliter.size();
    }
    return result;
}

vector<string> split(string inp, char spliter_1, char spliter_2)
{
    vector<string> result;
    int lastPos = 0;
    while (lastPos < inp.size())
    {
        size_t f_1 = inp.find(spliter_1, lastPos);
        size_t f_2 = inp.find(spliter_2, lastPos);
        size_t findPos = f_1 <= f_2 ? f_1 : f_2;
        if (findPos == std::string::npos)
            findPos = inp.size();
        result.push_back(inp.substr(lastPos, findPos - lastPos));
        lastPos = findPos + 1;
    }
    return result;
}

vector<string> split(string inp, char spliter_1, char spliter_2, char spliter_3)
{
    vector<string> result;
    int lastPos = 0;
    while (lastPos < inp.size())
    {
        size_t f_1 = inp.find(spliter_1, lastPos);
        size_t f_2 = inp.find(spliter_2, lastPos);
        size_t f_3 = inp.find(spliter_3, lastPos);
        size_t findPos = f_1 <= f_2 ? f_1 : f_2;
        findPos = f_3 <= findPos ? f_3 : findPos;
        if (findPos == std::string::npos)
            findPos = inp.size();
        result.push_back(inp.substr(lastPos, findPos - lastPos));
        lastPos = findPos + 1;
    }
    return result;
}

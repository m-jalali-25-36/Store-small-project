#include <iostream>

#pragma once
using namespace std;

bool contain(string inp,string key)
{
    return inp.find(key) != std::string::npos;
}
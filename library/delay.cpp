#include <time.h>

#pragma once
void delay(int milli_seconds)
{
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
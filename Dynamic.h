#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <algorithm>

struct Item{
    int weight;
    int profit;
    int id;
    double ratio;

    Item(int w, int p, int i) {
        weight = w;
        profit = p;
        id = i;
        ratio = p / w;
    }
};

#endif

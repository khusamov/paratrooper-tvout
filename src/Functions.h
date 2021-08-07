#pragma once

#include <TVout.h>

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#endif

double mapf(double val, double in_min, double in_max, double out_min, double out_max);
void drawCircle(TVout tv, int x0, int y0, int radius);
bool pointOffScreen(int x, int y);
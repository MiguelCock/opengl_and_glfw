#include <stdbool.h>
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

int ComputeOutCode(double x, double y);
bool CohenSutherlandLineClip(double* x0, double* y0, double* x1, double* y1);
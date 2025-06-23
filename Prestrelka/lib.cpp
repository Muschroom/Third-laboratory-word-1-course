#include <iostream>
#include <cmath>
using namespace std;
const double g = 9.8;
const double PI = 3.14;

extern "C"{

double bin_search(double v, double x0, double x1) {
    double left = 0;
    double right = PI / 2;
    while (right - left > 0.001) {
        double mid = (left + right) / 2;
        double way = (v * v * sin(2 * mid)) / g;
        if (way >= x0 && way <= x1) {
            return mid;
        }
        else if (way < x0) {
            left = mid;
        }
        else {
            right = mid;
        }
    }

    return -1;
}

}

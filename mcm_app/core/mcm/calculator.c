#include "calculator.h"

int mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int calcular_mcm(int a, int b) {
    return (a * b) / mcd(a, b);
}

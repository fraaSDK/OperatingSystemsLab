#include <stdio.h>

static double salva = 0;

double quadrato(double n) {
    salva = n * n;
    return salva;
}

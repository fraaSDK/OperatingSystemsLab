#include <stdio.h>
#include "quadrato.h"
#include "dimezza.h"

static double salva = 0;

int main() {
    salva = quadrato(dimezza(13.17));
    printf("%f\n", salva);
    return 0;
}

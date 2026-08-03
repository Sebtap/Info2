#include <stdlib.h>
#include <stdio.h>
// Este programa imprime el valor de la variable de entorno VERBOSE, si está definida. Si no está definida, imprime un mensaje indicando que no lo está.
int main(int argc, char *argv[]) {

    char *verbose = getenv("VERBOSE");
    if (verbose != NULL) {
        printf("La variable VERBOSE es: %s\n", verbose);
    } else {
        printf("VERBOSE no esta definida.\n");
    }
    return 0;
}

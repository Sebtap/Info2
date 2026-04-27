#include <stdio.h>

/*Realizar un programa que muestre la cantidad de argumentos 
del main que recibe y los enumere.  */

int main(int argc, char *argv[]) {

    printf("Cantidad de argumentos: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Argumento %d: %s\n", i, argv[i]);
    }
    return 0;

}
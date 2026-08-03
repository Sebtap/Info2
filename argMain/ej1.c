#include <stdio.h>

// recibe argumentos en la funcion main desde el sistema operativo, y los imprime en pantalla.
int main(int argc, char *argv[]) { // argc: cantidad de argumentos, argv: arreglo de punteros a char (strings) que contienen los argumentos, recibe la direccion de memoria de cada argumento. argv[0] es el nombre del programa, argv[1] es el primer argumento, argv[2] es el segundo argumento, y asi sucesivamente. argv[argc] es NULL, es decir, el ultimo elemento del arreglo es un puntero nulo.
    printf("Numero de argumentos (argc): %d\n", argc);

    for (int i = 0; i <= argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
#include <stdio.h>

int main() {
    int edad;
    char tipo, c;

    printf("Edad: ");
    scanf("%d", &edad);
    while ((c = getchar () )!='\n');
    printf("Tipo (A/B): ");
    scanf("%c", &tipo);

    printf("Edad ingresada: %d\n", edad);
    printf("Tipo ingresado: %c\n", tipo);

    return 0;
}
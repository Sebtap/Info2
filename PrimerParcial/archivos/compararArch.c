#include <stdio.h>

/*
Hacer un programa que compare dos archivos de texto e indique si tienen o
no igual contenido
*/

int main() {
    FILE *archTexto1 = fopen("archTexto1.txt", "r");
    if (archTexto1 == NULL) {
        fprintf(stderr, "Error al abrir archTexto1.txt\n");
        return 1;
    }
    
    FILE *archTexto2 = fopen("archTexto2.txt", "r");
    if (archTexto2 == NULL) {
        fprintf(stderr, "Error al abrir archTexto2.txt\n");
        fclose(archTexto1); // Liberar el primer recurso si falla el segundo
        return 1;
    }

    int c1, c2;
    int son_iguales = 1;

    // Leemos caracter por caracter en simultaneo de ambos archivos
    do {
        c1 = fgetc(archTexto1);
        c2 = fgetc(archTexto2);

        if (c1 != c2) {
            son_iguales = 0;
            break; // Si hay una diferencia (o uno termina antes), se interrumpe
        }
    } while (c1 != EOF && c2 != EOF);

    if (son_iguales) {
        printf("Tienen igual contenido\n");
    } else {
        printf("Tienen contenido diferente\n");
    }

    fclose(archTexto1);
    fclose(archTexto2);

    return 0;
}
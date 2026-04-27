#include <stdio.h>
/*Hacer un programa que compare dos archivos de texto e 
indique si tienen o no igual contenido.*/

int main() {
    FILE *archivo1, *archivo2;  
    int caracter1, caracter2;
    
    // Abrimos ambos archivos en modo lectura
    archivo1 = fopen("archivo.txt", "r");
    archivo2 = fopen("archivo2.txt", "r");
    if (archivo1 == NULL || archivo2 == NULL) {
        printf("No se pudo abrir uno de los archivos. Asegurate de que 'archivo1.txt' y 'archivo2.txt' existan.\n");
        return 1;
    }
    
    // Leemos los archivos caracter por caracter y los comparamos
    while ((caracter1 = fgetc(archivo1)) != EOF && (caracter2 = fgetc(archivo2)) != EOF) {
        if (caracter1 != caracter2) {
            printf("Los archivos tienen contenido diferente.\n");
            fclose(archivo1);
            fclose(archivo2);
            return 0;
        }
    }

    // Verificamos si ambos archivos llegaron al final al mismo tiempo
    if ((caracter1 == EOF) && (caracter2 == EOF)) {
        printf("Los archivos tienen el mismo contenido.\n");
    } else {
        printf("Los archivos tienen contenido diferente.\n");
    }

    fclose(archivo1);
    fclose(archivo2);
    return 0;
}
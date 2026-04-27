#include <stdio.h>

/*Concatenar dos archivos de texto (poner uno a continuación 
del otro en un mismo archivo).  */

int main() {
    FILE *archivo1, *archivo2, *archivoSalida;  
    int caracter;

    // Abrimos ambos archivos en modo lectura
    archivo1 = fopen("archivo.txt", "r");
    archivo2 = fopen("archivo2.txt", "r");
    if (archivo1 == NULL || archivo2 == NULL) {
        printf("No se pudo abrir uno de los archivos. Asegurate de que 'archivo.txt' y 'archivo2.txt' existan.\n");
        return 1;
    }

    // Abrimos el archivo de salida en modo escritura (creará o sobrescribirá)
    archivoSalida = fopen("archivo_concatenado.txt", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        fclose(archivo1);
        fclose(archivo2);
        return 1;
    }

    // Copiamos el contenido del primer archivo al archivo de salida
    while ((caracter = fgetc(archivo1)) != EOF) {
        fputc(caracter, archivoSalida);
    }

    // Copiamos el contenido del segundo archivo al archivo de salida
    while ((caracter = fgetc(archivo2)) != EOF) {
        fputc(caracter, archivoSalida);
    }

    // Cerramos todos los archivos
    fclose(archivo1);
    fclose(archivo2);
    fclose(archivoSalida);

    printf("Los archivos han sido concatenados en 'archivo_concatenado.txt'.\n");
    
    return 0;
}
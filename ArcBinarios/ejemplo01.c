//Realizar un programa para copiar un archivo de texto en otro.

#include <stdio.h>

int main() {
    FILE *archivoOrigen, *archivoDestino;
    char caracter;

    // Abrimos el archivo de origen en modo lectura
    archivoOrigen = fopen("archivo.txt", "r");
    if (archivoOrigen == NULL) {
        printf("No se pudo abrir el archivo de origen. Asegurate de que 'archivo.txt' exista.\n");
        return 1;
    }

    // Abrimos el archivo de destino en modo escritura
    archivoDestino = fopen("copia.txt", "w");
    if (archivoDestino == NULL) {
        printf("No se pudo abrir el archivo de destino.\n");
        fclose(archivoOrigen); // Cerramos el archivo de origen antes de salir
        return 1;
    }

    // Leemos el archivo de origen caracter por caracter y lo escribimos en el destino
    while ((caracter = fgetc(archivoOrigen)) != EOF) {
        fputc(caracter, archivoDestino);
    }

    // Cerramos ambos archivos
    fclose(archivoOrigen);
    fclose(archivoDestino);

    printf("Archivo copiado exitosamente.\n");
    return 0;
}
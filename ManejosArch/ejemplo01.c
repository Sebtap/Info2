#include <stdio.h> 
//Hacer un programa que cuente la cantidad de bytes 
//que contiene un archivo de texto. 

int main() {
    FILE *archivo;
    long int contadorBytes = 0;
    int caracter; // Cambiado a int para detectar bien el EOF

    // Abrimos en "rb" (read binary) para contar bytes reales
    archivo = fopen("archivo.txt", "rb");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo. Asegurate de que 'archivo.txt' exista.\n");
        return 1;
    }

    /* EXPLICACIÓN DEL BUCLE:
       1. fgetc(archivo): Lee el SIGUIENTE byte (caracter) del archivo.
       2. (caracter = fgetc...): Guarda ese byte en la variable 'caracter'.
       3. != EOF: Compara si lo que leyó es el "Fin de Archivo".
    */
    // Leemos byte por byte hasta el final
    while ((caracter = fgetc(archivo)) != EOF) {
        // Si no es el final, sumamos 1 al contador
        contadorBytes++;
    }

    fclose(archivo);
    printf("El archivo contiene %ld bytes.\n", contadorBytes);

    return 0;
}
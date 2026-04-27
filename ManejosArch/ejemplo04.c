#include <stdio.h>
#include <string.h>

/*Realizar un programa que busque una palabra en un archivo 
de texto y si está varias veces indicar cuántas. La palabra 
se debe ingresar como argumento del main.*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo> <palabra>\n", argv[0]);
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", argv[1]);
        return 1;
    }

    char palabra[100];
    strcpy(palabra, argv[2]);

    int contador = 0;
    char caracter;
    int i = 0;

    while ((caracter = fgetc(archivo)) != EOF) { //fgetc(archivo) lee un caracter del archivo y lo guarda en 'caracter' y eof es el fin del archivo
        if (caracter == palabra[i]) {
            i++;
            if (i == strlen(palabra)) {//strlen(palabra) devuelve la longitud de la palabra
                contador++;
                i = 0;
            }
        } else {
            i = 0;
        }
    }

    printf("La palabra '%s' aparece %d veces en el archivo.\n", palabra, contador);

    fclose(archivo);
    return 0;
}
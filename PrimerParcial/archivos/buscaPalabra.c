/*
Realizar un programa que busque una palabra en un archivo de texto y si esta
varias veces indicar cuantas. La palabra debe ingresar como argumento del main
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 1. Validar que el usuario haya pasado la palabra por argumento
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <palabra_a_buscar>\n", argv[0]);
        return 1;
    }

    // 2. Abrir el archivo en modo lectura
    FILE *archText = fopen("archtext.txt", "r");
    if (archText == NULL) {
        fprintf(stderr, "Error: No se pudo abrir archtext.txt\n");
        return 1;
    }

    char palabra_leida[100];
    int cant_apariciones = 0;

    // 3. Leer palabra por palabra hasta el final del archivo
    // fscanf devuelve 1 cada vez que logra leer una palabra con %s
    while (fscanf(archText, "%99s", palabra_leida) == 1) {
        
        // Comparar la palabra leída con el argumento recibido (argv[1])
        if (strcmp(palabra_leida, argv[1]) == 0) {
            cant_apariciones++;
        }
    }

    fclose(archText);

    // 4. Mostrar el resultado
    printf("La palabra '%s' aparece %d veces en el archivo.\n", argv[1], cant_apariciones);

    return 0;
}
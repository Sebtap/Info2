/*
Realizar un programa que copie un archivo a otros cuyos nombres estaran 
indicados como argumentos del main. Asi: copy_archivo.txt archivo_copia.txt
*/

#include <stdio.h>

int main(int argc, char *argv[]) {

    // 1. Validar que tengamos al menos origen y destino en los argumentos
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo_origen> <archivo_destino>\n", argv[0]);
        return 1;
    }

    // 2. Abrir archivo origen en modo LECTURA ("r")
    FILE *origen = fopen(argv[1], "r");
    if (origen == NULL) {
        fprintf(stderr, "Error al abrir el archivo origen: %s\n", argv[1]);
        return 1;
    }

    // 3. Abrir archivo destino en modo ESCRITURA ("w")
    FILE *destino = fopen(argv[2], "w");
    if (destino == NULL) {
        fprintf(stderr, "Error al crear/abrir el archivo destino: %s\n", argv[2]);
        fclose(origen);
        return 1;
    }

    // 4. Copiar contenido linea por linea
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), origen) != NULL) {
        fputs(buffer, destino); // Copia la linea leida dentro del archivo destino
    }

    // 5. Cerrar recursos
    fclose(origen);
    fclose(destino);

    printf("Copia realizada con exito de '%s' a '%s'\n", argv[1], argv[2]);

    return 0;
}
#include <stdio.h>

int main() {
    FILE *fp = fopen("archivo_grande.bin", "wb");
    if (fp == NULL) return 1;

    // Un mega de ceros (1024 * 1024 bytes)
    char mega[1048576] = {0}; 

    // Escribimos ese mega 100 veces
    for (int i = 0; i < 100; i++) {
        fwrite(mega, 1, 1048576, fp);
    }

    fclose(fp);
    printf("¡Listo! Archivo de 100 MB creado en tu carpeta.\n");
    return 0;
}
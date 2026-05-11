#include <stdio.h>

// Definimos el tamaño del buffer aquí. 
// Para probar diferentes medidas, cambiás este número y re-compilás.
#define TAM_BUFFER 4096 

/*Para 1 B: #define TAM_BUFFER 1

Para 1 KB: #define TAM_BUFFER 1024

Para 4 KB: #define TAM_BUFFER 4096

Para 64 KB: #define TAM_BUFFER 65536

Para 1 MB: #define TAM_BUFFER 1048576*/

int main() {
    FILE *entrada = fopen("archivo_grande.bin", "rb");
    FILE *salida = fopen("copia.bin", "wb");
    
    if (entrada == NULL || salida == NULL) {
        perror("Error al abrir los archivos");
        return 1;
    }

    // Usamos un array común como buffer
    unsigned char buffer[TAM_BUFFER];
    size_t leidos;

    // El bucle sigue mientras fread logre leer algo
    while ((leidos = fread(buffer, 1, TAM_BUFFER, entrada)) > 0) {
        // Escribimos exactamente la cantidad que leímos en este viaje
        fwrite(buffer, 1, leidos, salida);
    }

    fclose(entrada);
    fclose(salida);
    
    printf("Copia finalizada con buffer de %d bytes.\n", TAM_BUFFER);
    return 0;
}
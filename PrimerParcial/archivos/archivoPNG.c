/*
Escribir un programa que abra un archivo PNG en modo binario y muestro 
por pantalla:
A. Si el archivo es realmente un PNG valido (verificando los primeros 8 bytes: 
    89 50 4E 47 0D 0A 1A 0A).
B. El ancho y alto de la imagen en pixeles.
Datos del formato:
-Los primeros 8 bytes son la firma PNG.
-A continuacion viene un chunk llamado IHDR. Su estructura comienza asi:
    -4 bytes: tamaño del chunk(uint32_t,big-endian)--ignorarlo
    -4 bytes: tipo del chunk(los caracteres ASCII "IHDR")--ignorarlos.
    -4 bytes: ancho(uint32_t,big-endian).
    -4 bytes: alto(uint32_t,big-endian).
    -Los uint32_t estan en big-endian(network byte order). Como las PCs son
    little-endian, hay que invertir el orden de los bytes al leer.
Probar el programa con varios PNG de ancho y alto conocido. Verificar el 
resultado abriendo la imagen en cualquier visor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Firma oficial de un archivo PNG (8 bytes)
const uint8_t PNG_SIGNATURE[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

// Convierte un arreglo de 4 bytes en orden Big-Endian a uint32_t (Little-Endian)
uint32_t leer_uint32_be(const uint8_t bytes[4]) {
    return ((uint32_t)bytes[0] << 24) |
           ((uint32_t)bytes[1] << 16) |
           ((uint32_t)bytes[2] << 8)  |
            (uint32_t)bytes[3];
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <ruta_al_archivo.png>\n", argv[0]);
        return 1;
    }

    // 1. Abrir el archivo en modo binario ("rb")
    FILE *archivo = fopen(argv[1], "rb");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // 2. Verificar Firma PNG (Punto A)
    uint8_t firma[8];
    if (fread(firma, 1, 8, archivo) != 8) {
        printf("El archivo es demasiado pequeño para ser un PNG valido.\n");
        fclose(archivo);
        return 1;
    }

    bool es_png = true;
    for (int i = 0; i < 8; i++) {
        if (firma[i] != PNG_SIGNATURE[i]) {
            es_png = false;
            break;
        }
    }

    if (!es_png) {
        printf("A. El archivo NO es un PNG valido (la firma no coincide).\n");
        fclose(archivo);
        return 0;
    }

    printf("A. El archivo es un PNG VALIDO.\n");

    // 3. Ignorar los primeros 8 bytes del Chunk IHDR
    // (4 bytes de tamaño del chunk + 4 bytes del tipo "IHDR")
    if (fseek(archivo, 8, SEEK_CUR) != 0) {
        printf("Error al desplazarse en el archivo.\n");
        fclose(archivo);
        return 1;
    }

    // 4. Leer Ancho y Alto (Punto B)
    uint8_t buf_ancho[4];
    uint8_t buf_alto[4];

    if (fread(buf_ancho, 1, 4, archivo) != 4 || fread(buf_alto, 1, 4, archivo) != 4) {
        printf("Error al leer el ancho/alto en el encabezado IHDR.\n");
        fclose(archivo);
        return 1;
    }

    // Convertir de Big-Endian a la endianness nativa
    uint32_t ancho = leer_uint32_be(buf_ancho);
    uint32_t alto = leer_uint32_be(buf_alto);

    printf("B. Dimensiones de la imagen:\n");
    printf("   - Ancho: %u px\n", ancho);
    printf("   - Alto:  %u px\n", alto);

    fclose(archivo);
    return 0;
}
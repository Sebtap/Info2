/*4. Escribir un programa que abra un archivo PNG en modo 
binario y muestre por pantalla: A. Si el archivo es realmente 
un PNG válido (verificando los primeros 8 bytes: 
89 50 4E 47 0D 0A 1A 0A). B. 2. El ancho y alto de la imagen 
en píxeles. Datos del formato: • Los primeros 8 bytes son la 
firma PNG. • A continuación viene un chunk llamado IHDR. 
Su estructura comienza así: • 4 bytes: tamaño del 
chunk (uint32_t, big-endian) — ignorarlo. 
• 4 bytes: tipo del chunk (los caracteres ASCII "IHDR") 
— ignorarlos. • 4 bytes: ancho (uint32_t, big-endian). 
• 4 bytes: alto (uint32_t, big-endian). 
• Los uint32_t están en big-endian (network byte order). 
Como las PCs son little-endian, hay que invertir el orden de 
los bytes al leer. Probar el programa con varios PNG de ancho y 
alto conocido. Verificar el resultado abriendo la imagen en 
cualquier visor. */

#include <stdio.h>
#include <stdint.h> // Para usar uint32_t (enteros de 4 bytes exactos)

// Función para invertir los bytes de Big-Endian a Little-Endian
uint32_t invertirBytes(uint32_t num) {
    return ((num >> 24) & 0x000000FF) | // Mueve el byte 1 al 4
           ((num >> 8)  & 0x0000FF00) | // Mueve el byte 2 al 3
           ((num << 8)  & 0x00FF0000) | // Mueve el byte 3 al 2
           ((num << 24) & 0xFF000000);   // Mueve el byte 4 al 1
}

int main() {
    FILE *fp = fopen("imagen.png", "rb"); // Modo binario es OBLIGATORIO
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // A. Verificar la firma (8 bytes)
    unsigned char firma[8];
    unsigned char firmaValida[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    
    fread(firma, 1, 8, fp);
    
    for(int i = 0; i < 8; i++) {
        if(firma[i] != firmaValida[i]) {
            printf("Error: No es un archivo PNG valido.\n");
            fclose(fp);
            return 1;
        }
    }
    printf("Archivo PNG verificado correctamente.\n");

    // B. Obtener Ancho y Alto
    // Saltamos 8 bytes (4 del tamaño del chunk + 4 del nombre "IHDR")
    fseek(fp, 8, SEEK_CUR);

    uint32_t ancho, alto;

    // Leemos el ancho (4 bytes)
    fread(&ancho, sizeof(uint32_t), 1, fp);
    // Leemos el alto (4 bytes)
    fread(&alto, sizeof(uint32_t), 1, fp);

    // Invertimos los bytes porque el archivo viene en Big-Endian
    ancho = invertirBytes(ancho);
    alto = invertirBytes(alto);

    printf("--- DATOS DE LA IMAGEN ---\n");
    printf("Ancho: %u pixeles\n", ancho);
    printf("Alto:  %u pixeles\n", alto);

    fclose(fp);
    return 0;
}
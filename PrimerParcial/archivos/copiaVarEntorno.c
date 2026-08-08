/*
Escriba un programa que lea el contenido de la variable de entorno PATH y lo
almacene en un archivo de texto llamado path.txt
1/ Como extra, se pide que el contenido se procese de forma tal que cada ruta
contenida en PATH(separadas por ; en windows o : en linux)quede en una linea
distinta del archivo
*/

#include <stdio.h>
#include <stdlib.h> // Necesaria para getenv()

int main() {

    // 1. Obtener el valor de la variable de entorno PATH
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "No se pudo encontrar la variable de entorno PATH\n");
        return 1;
    }

    // 2. Abrir archivo path.txt en modo escritura ("w")
    FILE *arc = fopen("path.txt", "w");
    if (arc == NULL) {
        fprintf(stderr, "Error al abrir el archivo path.txt\n");
        return 1;
    }

    // 3. Recorrer la cadena y reemplazar los separadores ';' y ':' por '\n'
    int i = 0;
    while (path[i] != '\0') {
        if (path[i] == ';' || path[i] == ':') {
            fputc('\n', arc); // Reemplaza el separador por un salto de linea
        } else {
            fputc(path[i], arc); // Escribe el caracter normal de la ruta
        }
        i++;
    }

    // Agregamos un salto de linea final al archivo
    fputc('\n', arc);

    // 4. Cerrar el recurso
    fclose(arc);

    printf("Variable PATH exportada con exito a 'path.txt'\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Escriba un programa que lea el contenido de la variable de 
entorno PATH y lo almacene en un archivo de texto llamado 
path.txt. 1. Como extra, se pide que el contenido se 
procese de forma tal que cada ruta contenida en PATH 
(separadas por ; en Windows o : en Linux) quede en una 
línea distinta del archivo.*/

int main() {
    // 1. Obtenemos el puntero a la variable PATH
    char *path_original = getenv("PATH");
    
    if (path_original == NULL) {
        fprintf(stderr, "Error: No se pudo obtener la variable PATH.\n");
        return 1;
    }

    // 2. Abrimos el archivo para escribir
    FILE *file = fopen("path.txt", "w");
    if (file == NULL) {
        perror("Error al abrir el archivo"); // perror da un mensaje de error más detallado
        return 1;
    }

    /* DETALLE TÉCNICO: strtok modifica el string. 
       Para evitar problemas, trabajamos sobre una copia.
       Usamos strdup para duplicar el string en memoria dinámica.
    */
    char *path_copy = strdup(path_original);

    /*
       DEFINICIÓN DE SEPARADOR:
       Windows usa ";" y Linux/Unix usa ":". 
       Al poner ";:" strtok buscará cualquiera de los dos.
    */
    char *delimitadores = ";:"; 

    // 3. Procesamos con strtok
    char *token = strtok(path_copy, delimitadores);
    
    while (token != NULL) {
        // Escribimos cada ruta en una línea nueva del archivo
        fprintf(file, "%s\n", token);
        
        // Pedimos el siguiente trozo (token)
        token = strtok(NULL, delimitadores);
    }

    // 4. Limpieza
    fclose(file);
    free(path_copy); // Liberamos la memoria de la copia

    printf("Proceso completado. Revisá el archivo 'path.txt'.\n");

    return 0;
}
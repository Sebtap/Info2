/*
Escribir un programa en C que cree un archivo de texto llamado notas.txt. 
El programa debe pedirle al usuario que ingrese la nota final de un 
alumno (un entero) y escribir ese número dentro del archivo de texto. 
Luego, debe cerrar el archivo correctamente.
*/

#include <stdio.h>

int main() {

    //Creamos un archivo de texto llamado "notas.txt" en modo escritura ("w")
    FILE *archivo = fopen("notas.txt","w"); //modo escritura, si el archivo no existe, se crea; si existe, se sobrescribe
    if(archivo == NULL) {
        fprintf(stderr, "Error al crear el archivo notas.txt\n");
        return 1; // Salimos con error
    }
    int nota;
    //Le pedimos al usuario que ingrese la nota final del alumno
    printf("Ingrese la nota final del alumno (entero): ");
    scanf("%d", &nota);

    //Escribimos la nota en el archivo de texto
    //Para archivos de texto, usamos fprintf en lugar de fwrite
    //recibe como argumentos el puntero al archivo, el formato y la variable a escribir
    fprintf(archivo, "%d\n", nota);


    //Cerramos el archivo correctamente
    fclose(archivo);

    return 0;
}
/*
Enunciado:

Diseñar un programa en C que defina una estructura Alumno con legajo (entero) 
y promedio (float). El programa debe:

Pedirle los datos de 1 alumno al usuario.

Abrir (o crear) un archivo binario llamado alumnos.dat en modo escritura 
binaria ("wb").

Guardar la estructura completa en el disco usando fwrite().

Abrir inmediatamente el archivo en modo lectura binaria ("rb"), leer la 
estructura con fread() y mostrar sus datos por pantalla para verificar 
que se guardó bien.
*/

#include <stdio.h>

typedef struct {
    int legajo;
    float promedio;
} Alumno;

int main() {

    Alumno alumno;

    //Pedimos al usuario que ingrese los datos del alumno
    printf("Ingrese el legajo del alumno (entero): ");
    scanf("%d", &alumno.legajo);
    printf("Ingrese el promedio del alumno (float): ");
    scanf("%f", &alumno.promedio);

    //Abrimos (o creamos) el archivo binario "alumnos.dat" en modo escritura binaria ("wb")
    FILE *archivo = fopen("alumnos.dat", "wb");
    if (archivo == NULL) {
        fprintf(stderr, "Error al crear el archivo alumnos.dat\n");
        return 1; // Salimos con error
    }

    //Guardamos la estructura completa en el disco usando fwrite()
    //fwrite (DIRECCION DE DONDE SALEN LOS DATOS(&), TAMAÑO EN BYTES DE 1 SOLO ELEMENTO, CANTIDAD DE ELEMENTOS, PUNTERO AL ARCHIVO)
    fwrite(&alumno, sizeof(Alumno), 1, archivo);

    //Cerramos el archivo después de escribir
    fclose(archivo);
    printf("Datos del alumno guardados correctamente en alumnos.dat\n");

    //Abrimos inmediatamente el archivo en modo lectura binaria ("rb")
    archivo = fopen("alumnos.dat", "rb");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo alumnos.dat para lectura\n");
        return 1; // Salimos con error
    }

    //Leemos la estructura con fread()
    Alumno alumno_leido; //Variable donde a cargar lo que leamos del disco
    fread(&alumno_leido,sizeof(alumno),1,archivo);

    //Cerramos el archivo de lectura
    fclose(archivo);

    //Mostrar el resultado leido desde el archivo
    printf("\n=== DATOS RECUPERADOS DEL ARCHIVO BINARIO ===\n");
    printf("Legajo: %d\n", alumno_leido.legajo);
    printf("Promedio: %.2f\n", alumno_leido.promedio);





}
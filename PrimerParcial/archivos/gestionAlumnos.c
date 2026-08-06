/*
Enunciado:
Diseñar un programa en C con una estructura Alumno (legajo y promedio) 
que permita:

Cargar múltiples alumnos: Pedir al usuario cuántos alumnos desea ingresar, 
guardarlos en un vector y escribirlos todos de un solo golpe en el archivo 
alumnos.dat en modo "ab".

Listar todo el archivo: Abrir el archivo en modo "rb" y leer registro por 
registro dentro de un ciclo while utilizando el valor de retorno de fread(), 
mostrando cada alumno guardado hasta llegar al final.

*/


#include <stdio.h>

typedef struct {
    int legajo;
    float promedio;
} Alumno;

int main() {
    FILE *archivo;
    int n, i;

    // =========================================================================
    // 1. ESCRITURA: Cargar e ingresar un grupo de alumnos ("ab")
    // =========================================================================
    printf("¿Cuantos alumnos desea ingresar?: ");
    scanf("%d", &n);

    Alumno lista[n]; // Vector para almacenar temporalmente en memoria RAM

    for (i = 0; i < n; i++) {
        printf("\n--- Alumno %d ---\n", i + 1);
        printf("Legajo: ");
        scanf("%d", &lista[i].legajo);
        printf("Promedio: ");
        scanf("%f", &lista[i].promedio);
    }

    // Abrimos en modo "ab" (Append Binary): no borra lo anterior, agrega al final.
    archivo = fopen("alumnos.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return 1;
    }

    // Escribimos los 'n' alumnos juntos
    //lista sin corchete equivale a la direccion de memoira del 1er elemento
    fwrite(lista, sizeof(Alumno), n, archivo);
    fclose(archivo);
    printf("\n[OK] %d alumno(s) guardado(s) correctamente.\n", n);


    // =========================================================================
    // 2. LECTURA: Leer todo el archivo binario desde el principio ("rb")
    // =========================================================================
    archivo = fopen("alumnos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return 1;
    }

    Alumno aux; // Variable aux para ir recibiendo cada registro uno por uno
    int contador = 0;

    printf("\n===========================================\n");
    printf("     LISTADO COMPLETO DE ALUMNOS EN DISCO   \n");
    printf("===========================================\n");

    // El while se ejecuta MIENTRAS fread() lea exitosamente 1 registro
    while (fread(&aux, sizeof(Alumno), 1, archivo) == 1) {
        contador++;
        printf("Alumno #%d -> Legajo: %d | Promedio: %.2f\n", contador, aux.legajo, aux.promedio);
    }

    fclose(archivo);

    if (contador == 0) {
        printf("El archivo está vacío.\n");
    }

    return 0;
}
/*
Ingresar por teclado un entero que reprente la cantidad de elementos que 
debe crearse un vector. Crear el vector en forma dinamica, cargar e imprimir
sus datos. Hacer todo en el main.
*/

#include <stdio.h>
#include <stdlib.h> // Necesaria para malloc() y free()

int main() {
    int n;

    // 1. Pedir el tamaño del vector
    printf("Ingrese la cantidad de elementos: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Debe ingresar un numero entero mayor a 0.\n");
        return 1;
    }

    // 2. Asignacion dinamica de memoria
    int *vec = (int *)malloc(n * sizeof(int));
    
    // Validacion de memoria (Clave de examen)
    if (vec == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria suficiente.\n");
        return 1;
    }

    // 3. Cargar el vector
    printf("\n--- CARGA DE DATOS ---\n");
    for (int i = 0; i < n; i++) {
        printf("Ingrese el elemento [%d]: ", i);
        scanf("%d", &vec[i]); // Tambien podrias usar *(vec + i)
    }

    // 4. Imprimir el vector
    printf("\n--- CONTENIDO DEL VECTOR ---\n");
    for (int i = 0; i < n; i++) {
        printf("vec[%d] = %d\n", i, vec[i]);
    }

    // 5. Liberar la memoria reservada
    free(vec);

    return 0;
}
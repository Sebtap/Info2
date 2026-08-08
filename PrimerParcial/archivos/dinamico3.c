/*
Se tiene la siguiente declaracion de registro:

struct producto{
    int codigo;
    char descripcion[41];
    float precio;
};
Definir un puntero de tipo producto y luego mediante la funcion malloc crear
un registro en la pila dinamica. Cargar el registro, imprimirlo y finalmente
liberar el espacio reservado mediante la funcion free.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct producto {
    int codigo;
    char descripcion[41];
    float precio;
};

int main() {
    // 1. Definir el puntero al tipo de estructura
    struct producto *p;

    // 2. Reservar memoria dinámica para UN registro completo
    p = (struct producto *) malloc(sizeof(struct producto));

    // Validación de asignación de memoria (Clave de examen)
    if (p == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria en el Heap.\n");
        return 1;
    }

    // 3. Cargar el registro (usando el operador flecha '->')
    printf("Ingrese codigo del producto: ");
    scanf("%d", &p->codigo);
    getchar(); // Consumir el '\n' remanente del buffer de lectura

    printf("Ingrese descripcion (max 40 chars): ");
    fgets(p->descripcion, sizeof(p->descripcion), stdin);
    p->descripcion[strcspn(p->descripcion, "\n")] = '\0'; // Eliminar el salto de linea al final

    printf("Ingrese precio: ");
    scanf("%f", &p->precio);

    // 4. Imprimir el registro
    printf("\n--- DATOS DEL PRODUCTO CARGADO ---\n");
    printf("Codigo:      %d\n", p->codigo);
    printf("Descripcion: %s\n", p->descripcion);
    printf("Precio:      $%.2f\n", p->precio);

    // 5. Liberar la memoria reservada
    free(p);

    return 0;
}
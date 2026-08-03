/*
### Ejercicio 4: Punteros a Función y Tablas de Despacho
Diseñar un menú interactivo o procesador de comandos que utilice un arreglo de 
punteros a función:
1. Declarar el tipo de dato puntero a función (`typedef`).
2. Crear un vector/tabla de funciones para cada comando disponible.
3. Invocar dinámicamente la función correspondiente según el comando ingresado 
por el usuario, evitando estructuras extensas de `if-else` o `switch-case`.
*/

#include <stdio.h>

// 1. DECLARACIÓN DEL TIPO DE DATO PUNTERO A FUNCIÓN
typedef void (*AccionFuncion)(float, float);

// Funciones del sistema (todas respetan la firma: void funcion(float, float))
void comando_sumar(float a, float b) {
    printf("\n[EJECUTANDO] Suma: %.2f + %.2f = %.2f\n", a, b, a + b);
}

void comando_restar(float a, float b) {
    printf("\n[EJECUTANDO] Resta: %.2f - %.2f = %.2f\n", a, b, a - b);
}

void comando_multiplicar(float a, float b) {
    printf("\n[EJECUTANDO] Multiplicacion: %.2f * %.2f = %.2f\n", a, b, a * b);
}

void comando_promedio(float a, float b) {
    printf("\n[EJECUTANDO] Promedio: (%.2f + %.2f) / 2 = %.2f\n", a, b, (a + b) / 2.0f);
}

int main() {
    // 2. CREACIÓN DE LA TABLA DE DESPACHO
    // Arreglo que contiene las direcciones de memoria de las funciones
    AccionFuncion tabla_comandos[] = {
        comando_sumar,        // Opción 0
        comando_restar,       // Opción 1
        comando_multiplicar,  // Opción 2
        comando_promedio      // Opción 3
    };

    // Calculamos el número total de comandos cargados
    int total_comandos = sizeof(tabla_comandos) / sizeof(tabla_comandos[0]);

    int opcion;
    float val1 = 15.5f, val2 = 4.5f;

    do {
        printf("\n=== MENÚ INTERACTIVO (TABLA DE DESPACHO) ===\n");
        printf("Valores actualizados de trabajo: a = %.1f, b = %.1f\n", val1, val2);
        printf("0. Sumar\n");
        printf("1. Restar\n");
        printf("2. Multiplicar\n");
        printf("3. Promedio\n");
        printf("4. Salir\n");
        printf("Ingrese comando [0-%d]: ", total_comandos);
        
        if (scanf("%d", &opcion) != 1) {
            break;
        }

        // Salida limpia
        if (opcion == total_comandos) {
            printf("\nSaliendo del programa...\n");
            break;
        }

        // Validación de rango
        if (opcion >= 0 && opcion < total_comandos) {
            
            // 3. INVOCACIÓN DINÁMICA DIRECTA
            // Se ejecuta la función correspondiente al índice sin ningún IF/SWITCH
            tabla_comandos[opcion](val1, val2);

        } else {
            printf("\n[ERROR] Opción invalida. Intente nuevamente.\n");
        }

    } while (1);

    return 0;
}
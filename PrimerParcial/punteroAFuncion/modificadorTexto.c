/*
Enunciado:
Un programa recibe un mensaje fijo en pantalla y le permite al usuario elegir 
cómo quiere mostrarlo.
-Funciones de Estilo (3):
    estiloMayusculas: Imprime "[ESTILO UPPER] MENSAJE EN MAYUSCULAS".
    estiloMinusculas: Imprime "[estilo lower] mensaje en minusculas".
    estiloDecorado: Imprime "*** [ESTILO DECORADO] mensaje ***".
-Puntero a Función: Declarar una variable puntero que pueda apuntar a cualquiera 
de estas 3 funciones.
-Selección: El usuario ingresa una opción (1, 2 o 3). Según la opción elegida, 
asignar la función correspondiente al puntero.
-Ejecución: Invocar la función seleccionada únicamente a través del puntero a 
función.
*/

#include <stdio.h> // Librería estándar de entrada/salida. Mostrar mensajes en pantalla y leer datos desde teclado.

//Funciones independientes
void estiloMayusculas(void) {
    printf("[ESTILO UPPER] MENSAJE EN MAYUSCULAS\n");
}
void estiloMinusculas(void) {
    printf("[estilo lower] mensaje en minusculas\n");
}
void estiloDecorado(void) {
    printf("*** [ESTILO DECORADO] mensaje ***\n");
}

int main() {
    int opcion;

    // Puntero a función que puede apuntar a cualquiera de las 3 funciones de estilo
    void (*estiloSeleccionado)(void) = NULL;

    //Pedimos al usuario que elija un estilo
    printf("=== MODIFICADOR DE ESTILO DE MENSAJE ===\n");
    printf("Elija un estilo para mostrar el mensaje:\n");
    printf("1. Mayusculas\n");
    printf("2. Minusculas\n");
    printf("3. Decorado\n");
    printf("Ingrese su opcion (1, 2 o 3): ");
    scanf("%d", &opcion);

    // Conectamos la decision del usuario con el puntero a función
    switch (opcion) {
        case 1:
            estiloSeleccionado = estiloMayusculas;
            break;
        case 2:
            estiloSeleccionado = estiloMinusculas;
            break;
        case 3:
            estiloSeleccionado = estiloDecorado;
            break;
        default:
            printf("Opcion invalida. Saliendo del programa.\n");
            return 1;
    }

    // Ejecutamos la función seleccionada a través del puntero
    if(estiloSeleccionado != NULL) {
        estiloSeleccionado(); //Se dispara recien aca!
    }

    return 0;
}
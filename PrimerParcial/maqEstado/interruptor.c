/*
 Ejercicio: El Interruptor de Luz
Consigna:
Crear una máquina de estados que simule una bombilla de luz.

La bombilla tiene solo 2 estados: APAGADO y ENCENDIDO.

Comienza en estado APAGADO.

Si el usuario presiona la letra 'p' (pulsar botón), cambia al estado contrario.

Si ingresa cualquier otra letra, el sistema no hace nada.

Si el usuario presiona 's' (salir), el programa termina.
*/

#include <stdio.h>
#include <ctype.h>

/*
 ==============================================================================
 1. DEFINICIÓN DE LOS ESTADOS (enum)
 ==============================================================================
 'enum' (enumeración) es la mejor forma de manejar estados.
 Le asigna internamente un número a cada palabra: APAGADO=0, ENCENDIDO=1.
 Esto hace que el código sea muy legible para los humanos.
*/
typedef enum {
    APAGADO,
    ENCENDIDO
} EstadoBombilla;

/*
 ==============================================================================
 2. LA FUNCIÓN QUE MANEJA LA MÁQUINA DE ESTADO
 ==============================================================================
*/
void maquinaInterruptor() {
    // A. Condición Inicial de la Máquina
    EstadoBombilla estado_actual = APAGADO;
    char entrada;

    printf("--- SIMULADOR DE INTERRUPTOR ---\n");
    printf("- Ingresa 'p' para pulsar el boton.\n");
    printf("- Ingresa 's' para salir.\n");
    printf("El foco esta APAGADO.\n\n");

    // B. Bucle de Recepción de Eventos (Bucle Infinito)
    while (1) {
        printf("Comando: ");
        
        // El espacio antes de %c " %c" evita que capture los saltos de línea al presionar ENTER
        if (scanf(" %c", &entrada) != 1) continue;
        
        entrada = tolower(entrada); // Convertimos todo a minúscula por las dudas

        // Si es 's', rompemos el bucle y salimos
        if (entrada == 's') {
            printf("\nApagando sistema...\n");
            break;
        }

        /* 
         ======================================================================
         3. LA LÓGICA DE TRANSICIONES (El corazón de la máquina)
         ======================================================================
         El 'switch' revisa en qué estado nos encontramos AHORA.
         Dentro de cada 'case', evaluamos qué evento de entrada recibimos
         para decidir a qué estado nos movemos (transición).
        */
        switch (estado_actual) {

            // ¿Qué pasa si estamos en el estado APAGADO?
            case APAGADO:
                if (entrada == 'p') {
                    // Acción al transicionar
                    printf("-> Click! El foco ahora esta ENCENDIDO.\n\n");
                    
                    // Transición de estado
                    estado_actual = ENCENDIDO; 
                } else {
                    printf("  (Tecla ignorada)\n");
                }
                break;

            // ¿Qué pasa si estamos en el estado ENCENDIDO?
            case ENCENDIDO:
                if (entrada == 'p') {
                    // Acción al transicionar
                    printf("-> Click! El foco ahora esta APAGADO.\n\n");
                    
                    // Transición de estado
                    estado_actual = APAGADO; 
                } else {
                    printf("  (Tecla ignorada)\n");
                }
                break;
        }
    }
}

/*
 ==============================================================================
 4. EL MAIN
 ==============================================================================
*/
int main() {
    maquinaInterruptor();
    return 0;
}
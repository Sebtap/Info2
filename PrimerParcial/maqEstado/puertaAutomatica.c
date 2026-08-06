/*
Ejercicio: La Puerta Automática
Consigna: Diseñar un sistema para controlar la puerta de un garaje con un botón.
-Estados posibles (3):
    CERRADA (Estado inicial)
    ABRIENDO (La puerta se está moviendo hacia arriba)
    ABIERTA (La puerta llegó arriba de todo)
-Eventos por teclado:
    Presionar 'b' (Presionar el Botón del control).
    Presionar 'f' (Fin de carrera / El sensor detecta que la puerta llegó arriba).
    Presionar 's' (Salir del programa).
-Reglas de negocio:
    Estando CERRADA, si presionas el botón 'b', la puerta pasa a estado ABRIENDO.
    Estando ABRIENDO, solo responde al sensor 'f' (que avisa que terminó de subir) para pasar a estado ABIERTA. Si tocas cualquier otra tecla mientras sube, la ignora.
    Estando ABIERTA, si vuelves a presionar el botón 'b', la puerta vuelve directamente a estado CERRADA.
*/

#include <stdio.h>
#include <ctype.h>

/*
 ==============================================================================
 1. DEFINICIÓN DE ESTADOS (3 Estados)
 ==============================================================================
*/
typedef enum {
    ESTADO_CERRADA,  // 0: Puerta abajo de todo
    ESTADO_ABRIENDO, // 1: En movimiento hacia arriba
    ESTADO_ABIERTA   // 2: Puerta arriba de todo
} EstadoPuerta;

/*
 ==============================================================================
 2. LÓGICA DE LA MÁQUINA DE ESTADOS
 ==============================================================================
*/
void maquinaPuerta() {
    EstadoPuerta estado_actual = ESTADO_CERRADA;
    char entrada;

    printf("=== CONTROLES DEL GARAJE ===\n");
    printf("Comandos:\n");
    printf("  'b' -> Presionar Boton del control\n");
    printf("  'f' -> Activar Sensor Fin de Carrera (Avance del motor)\n");
    printf("  's' -> Salir\n\n");
    printf("[ESTADO INICIAL] La puerta esta CERRADA.\n\n");

    while (1) {
        printf("Ingresar evento: ");
        if (scanf(" %c", &entrada) != 1) continue;

        entrada = tolower(entrada);

        if (entrada == 's') {
            printf("\nApagando sistema del garaje...\n");
            break; // Salir del bucle y terminar el programa
        }

        /*
         ======================================================================
         3. TRANSICIONES SEGÚN EL ESTADO ACTUAL
         ======================================================================
        */
        switch (estado_actual) {

            // CASO 1: La puerta está totalmente cerrada
            case ESTADO_CERRADA:
                if (entrada == 'b') {
                    printf("-> [ACCION] Motor encendido. La puerta comienza a subir...\n");
                    estado_actual = ESTADO_ABRIENDO; // Pasa a estado de movimiento
                } else {
                    printf("  (Estando CERRADA, el comando '%c' no hace nada)\n", entrada);
                }
                break;

            // CASO 2: La puerta está subiendo (En movimiento)
            case ESTADO_ABRIENDO:
                if (entrada == 'f') {
                    printf("-> [ACCION] Sensor activado! El motor se detiene arriba.\n");
                    estado_actual = ESTADO_ABIERTA; // Llegó arriba
                } else if (entrada == 'b') {
                    printf("  (¡El motor ya esta subiendo! Esperando que toque el sensor 'f')\n");
                } else {
                    printf("  (Comando '%c' ignorado mientras sube)\n", entrada);
                }
                break;

            // CASO 3: La puerta está totalmente abierta
            case ESTADO_ABIERTA:
                if (entrada == 'b') {
                    printf("-> [ACCION] Cerrando puerta instantaneamente...\n");
                    estado_actual = ESTADO_CERRADA; // Vuelve a cerrar
                } else {
                    printf("  (Estando ABIERTA, el comando '%c' no hace nada)\n", entrada);
                }
                break;
        }

        // Mostramos el estado actual tras cada evento para ver el progreso
        printf("   >> ESTADO ACTUAL: ");
        if (estado_actual == ESTADO_CERRADA) printf("CERRADA\n\n");
        if (estado_actual == ESTADO_ABRIENDO) printf("ABRIENDO...\n\n");
        if (estado_actual == ESTADO_ABIERTA) printf("ABIERTA\n\n");
    }
}

int main() {
    maquinaPuerta();
    return 0;
}
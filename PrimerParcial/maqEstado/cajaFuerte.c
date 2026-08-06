/*
Diseñar el sistema de control de una caja fuerte digital que requiere la 
clave fija 123 para abrirse.

Estados (4):

BLOQUEADA (Estado inicial, no tenemos ningún número).

PASO_1 (Ya ingresó el '1').

PASO_2 (Ya ingresó el '1' y luego el '2').

DESBLOQUEADA (Ingresó la secuencia '1', '2', '3').

Entradas: Caracteres numéricos del '0' al '9' (o 's' para salir).

Reglas de seguridad (Validación de fallos):

Si en cualquier momento el usuario presiona el número incorrecto, la máquina 
debe reiniciar el progreso a cero (BLOQUEADA).

Si estando DESBLOQUEADA presiona cualquier tecla, la caja se vuelve a cerrar 
automáticamente (BLOQUEADA).
*/

#include <stdio.h>
#include <ctype.h>

typedef enum {
    ESTADO_BLOQUEADA,  // 0: Estado inicial
    ESTADO_PASO_1,     // 1: Ingresó '1'
    ESTADO_PASO_2,     // 2: Ingresó '1' y luego '2'
    ESTADO_DESBLOQUEADA // 3: Ingresó '1', '2', '3'
} EstadoCaja;

void maquinaCajaFuerte() {


    EstadoCaja estado_actual = ESTADO_BLOQUEADA;
    char entrada;

    printf("=== SIMULADOR DE CAJA FUERTE DIGITAL ===\n");
    printf("Comandos:\n");
    printf("  '0'-'9' -> Ingresar dígito de la clave\n");
    printf("  's' -> Salir del programa\n\n");
    printf("[ESTADO INICIAL] La caja está BLOQUEADA.\n\n");
    
    //Bucle principal de la máquina de estados
    while(1){

        printf("Ingresar digito: ");
        if (scanf(" %c", &entrada) != 1) continue; //Evalua si se ingresó un caracter y si no, vuelve a pedirlo

        entrada = tolower(entrada);

        if (entrada == 's') {
            printf("\nApagando sistema de la caja fuerte...\n");
            break; // Salir del bucle y terminar el programa
        }

        // Lógica de transición de estados
        switch (estado_actual) {
            
            // Esperando el primer dígito correcto '1'
            case ESTADO_BLOQUEADA:
                if (entrada == '1') {
                    estado_actual = ESTADO_PASO_1;
                    printf("[INFO] Ingresó '1'. Progreso: PASO_1.\n");
                } else {
                    printf("[ERROR] Número incorrecto. Reiniciando a BLOQUEADA.\n");
                }
                break;
            
            // Esperando el segundo dígito correcto '2'
            case ESTADO_PASO_1:
                if (entrada == '2') {
                    estado_actual = ESTADO_PASO_2;
                    printf("[INFO] Ingresó '2'. Progreso: PASO_2.\n");
                } else {
                    estado_actual = ESTADO_BLOQUEADA;
                    printf("[ERROR] Número incorrecto. Reiniciando a BLOQUEADA.\n");
                }
                break;
            
            // Esperando el tercer dígito correcto '3'
            case ESTADO_PASO_2:
                if (entrada == '3') {
                    estado_actual = ESTADO_DESBLOQUEADA;
                    printf("[EXITO] Clave correcta. La caja está DESBLOQUEADA.\n");
                } else {
                    estado_actual = ESTADO_BLOQUEADA;
                    printf("[ERROR] Número incorrecto. Reiniciando a BLOQUEADA.\n");
                }
                break;
            
            // Si la caja está desbloqueada, cualquier entrada la bloquea nuevamente
            case ESTADO_DESBLOQUEADA:
                estado_actual = ESTADO_BLOQUEADA;
                printf("[INFO] La caja se ha cerrado automáticamente. Estado: BLOQUEADA.\n");
                break;
        }
        // Mostramos el indicador visual del estado
        printf("   [Estado actual: ");
        switch (estado_actual) {
            case ESTADO_BLOQUEADA:    printf(" BLOQUEADA]\n\n"); break;
            case ESTADO_PASO_1:       printf(" PROGRESO 1/3 (1--)]\n\n"); break;
            case ESTADO_PASO_2:       printf(" PROGRESO 2/3 (12-)]\n\n"); break;
            case ESTADO_DESBLOQUEADA: printf(" ABIERTA]\n\n"); break;
        }
    }

}

int main() {
    maquinaCajaFuerte();
    return 0;
}
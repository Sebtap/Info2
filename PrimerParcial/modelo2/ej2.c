/*
Ejercicio 2 – Máquina de Estado
Realizar un programa que simule un sistema de detección de intrusos en un 
servidor. El sistema debe analizar una secuencia de puertos de red atacados 
(ingresados como caracteres individuales por teclado) para detectar un patrón 
específico de escaneo táctico: la secuencia "p-o-r-t".
*/

#include <stdio.h>
#include <stdlib.h>

// 1. DEFINICIÓN DE LOS ESTADOS DE LA FSM
typedef enum {
    ESTADO_INICIO,  // Estado inicial (esperando 'p')
    ESTADO_P,       // Leída la 'p' (esperando 'o')
    ESTADO_PO,      // Leídas "po" (esperando 'r')
    ESTADO_POR,     // Leídas "por" (esperando 't')
    ESTADO_ALERTA   // Secuencia "port" detectada
} Estado;

int main() {
    Estado estado_actual = ESTADO_INICIO;
    char c;

    printf("=== SISTEMA DE DETECCIÓN DE INTRUSOS EN SERVIDOR ===\n");
    printf("Ingrese secuencia de caracteres/puertos (presione ENTER tras escribir):\n");
    printf("Para finalizar el programa ingrese '*'\n\n");

    // Leemos caracter por caracter
    while ((c = getchar()) != '*') {

        // Ignoramos saltos de línea (\n) para facilitar las pruebas desde la consola
        if (c == '\n') continue;

        switch (estado_actual) {

            case ESTADO_INICIO:
                if (c == 'p' || c == 'P') {
                    estado_actual = ESTADO_P;
                }
                break;

            case ESTADO_P:
                if (c == 'o' || c == 'O') {
                    estado_actual = ESTADO_PO;
                } else if (c == 'p' || c == 'P') {
                    estado_actual = ESTADO_P; // Nos mantenemos si repite 'p'
                } else {
                    estado_actual = ESTADO_INICIO; // Vuelve al inicio si rompe la secuencia
                }
                break;

            case ESTADO_PO:
                if (c == 'r' || c == 'R') {
                    estado_actual = ESTADO_POR;
                } else if (c == 'p' || c == 'P') {
                    estado_actual = ESTADO_P; // Reinicia con la nueva 'p'
                } else {
                    estado_actual = ESTADO_INICIO;
                }
                break;

            case ESTADO_POR:
                if (c == 't' || c == 'T') {
                    estado_actual = ESTADO_ALERTA;
                } else if (c == 'p' || c == 'P') {
                    estado_actual = ESTADO_P; // Reinicia la secuencia
                } else {
                    estado_actual = ESTADO_INICIO;
                }
                break;

            case ESTADO_ALERTA:
                // No debería llegar aquí directamente en el bucle principal
                break;
        }

        // Si se alcanzó el estado de alerta
        if (estado_actual == ESTADO_ALERTA) {
            printf("\n[🚨 ALERTA DE INTRUSO 🚨] Se ha detectado el patrón de escaneo táctico: \"p-o-r-t\"\n");
            
            // Reiniciamos la FSM para seguir escuchando
            estado_actual = ESTADO_INICIO; 
            printf("Sistema restablecido. Escuchando nuevo tráfico...\n");
        }
    }

    printf("\nSistema de detección finalizado correctamente.\n");
    return 0;
}
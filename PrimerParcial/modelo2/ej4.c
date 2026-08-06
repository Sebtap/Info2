/*
Ejercicio 4 – Puntero a función

Un sistema industrial de control de procesos mide constantemente la temperatura
 de un reactor químico. Dependiendo del nivel de la temperatura medida, el 
 sistema debe disparar una acción de alerta diferente de forma dinámica.
Se solicita diseñar un programa en lenguaje C que cumpla con los siguientes 
requerimientos:
1 Funciones de Alerta: Implementar tres funciones independientes que 
representen las acciones a tomar:
• alertaNormal: Imprime "[OK] Temperatura estable. Estado óptimo.".
• alertaAdvertencia: Imprime "[CUIDADO] Temperatura elevada. Monitorear de 
cerca.".
• alertaCritica: Imprime "[PELIGRO] ¡CRÍTICO! Activando sistema de 
enfriamiento de emergencia.".

2 Lógica del Selector (Puntero a Función): En lugar de usar un bloque 
if-else o switch-case gigante dentro de la rutina principal para ejecutar 
las alertas, debes declarar un puntero a función.

3 Evaluación: El programa solicitará al usuario la temperatura actual 
(un número entero).
• Si es menor a 40: se asignará el puntero a la función de alerta normal.
• Si está entre 40 y 79: se asignará a la función de advertencia.
• Si es 80 o más: se asignará a la función crítica.

4 Ejecución: Al final del ciclo, se debe invocar la acción correspondiente 
exclusivamente a través del puntero a función configurado.
*/

#include <stdio.h>

// ------------------------------------------------------------------
// 1. REQUERIMIENTO 1: LAS TRES FUNCIONES DE ALERTA INDEPENDIENTES
// ------------------------------------------------------------------

void alertaNormal(void) {
    printf("[OK] Temperatura estable. Estado optimo.\n");
}

void alertaAdvertencia(void) {
    printf("[CUIDADO] Temperatura elevada. Monitorear de cerca.\n");
}

void alertaCritica(void) {
    printf("[PELIGRO] ¡CRITICO! Activando sistema de enfriamiento de emergencia.\n");
}

int main() {
    int temp;

    // ------------------------------------------------------------------
    // 2. REQUERIMIENTO 2: DECLARACIÓN DEL PUNTERO A FUNCIÓN
    // ------------------------------------------------------------------
    // Puede apuntar a cualquier función que sea void nombre(void)
    void (*accion_alerta)(void) = NULL;

    printf("=== SISTEMA INDUSTRIAL DE CONTROL DE TEMPERATURA ===\n");
    printf("Ingrese la temperatura actual del reactor (°C): ");

    // Validación básica de entrada
    if (scanf("%d", &temp) != 1) {
        printf("[ERROR] Debe ingresar un valor numerico entero valido.\n");
        return 1;
    }

    // ------------------------------------------------------------------
    // 3. REQUERIMIENTO 3: SELECCIÓN DINÁMICA DE LA FUNCIÓN
    // ------------------------------------------------------------------
    // Asignamos la dirección de memoria de la función al puntero
    if (temp < 40) {
        accion_alerta = alertaNormal;
    } 
    else if (temp >= 40 && temp <= 79) {
        accion_alerta = alertaAdvertencia;
    } 
    else { // temp >= 80
        accion_alerta = alertaCritica;
    }

    // ------------------------------------------------------------------
    // 4. REQUERIMIENTO 4: EJECUCIÓN A TRAVÉS DEL PUNTERO
    // ------------------------------------------------------------------
    printf("\nResultado de la evaluacion:\n--> ");

    // Invocación explícita mediante el puntero cargado
    if (accion_alerta != NULL) {
        accion_alerta(); // Se ejecuta la función seleccionada dinámicamente
    }

    return 0;
}
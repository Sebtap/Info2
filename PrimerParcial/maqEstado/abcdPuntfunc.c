#include <stdio.h>
#include <stdbool.h>

// Definición del tipo puntero a función de estado
typedef void (*StateFunc)(char c);

// Declaración previa de las funciones de cada estado
void state_wait_a(char c);
void state_wait_b(char c);
void state_wait_c(char c);
void state_wait_d(char c);

// Puntero global al estado actual
StateFunc currentState = state_wait_a;

// Estado inicial: Esperando la letra 'a'
void state_wait_a(char c) {
    if (c == 'a') {
        currentState = state_wait_b;
    }
}

// Estado: Se recibió 'a', esperando 'b'
void state_wait_b(char c) {
    if (c == 'b') {
        currentState = state_wait_c;
    } else if (c == 'a') {
        currentState = state_wait_b; // Permanece si entra otra 'a' (ej. "aa")
    } else {
        currentState = state_wait_a;
    }
}

// Estado: Se recibió "ab", esperando 'c'
void state_wait_c(char c) {
    if (c == 'c') {
        currentState = state_wait_d;
    } else if (c == 'a') {
        currentState = state_wait_b; // Reinicia desde 'a' (ej. "aba")
    } else {
        currentState = state_wait_a;
    }
}

// Estado: Se recibió "abc", esperando 'd'
void state_wait_d(char c) {
    if (c == 'd') {
        printf("\n[¡ÉXITO!] Secuencia 'abcd' detectada.\n");
        currentState = state_wait_a; // Reiniciar para detectar nuevas secuencias
    } else if (c == 'a') {
        currentState = state_wait_b;
    } else {
        currentState = state_wait_a;
    }
}

int main(void) {
    char input;

    printf("Ingrese texto (Ctrl+C o EOF para salir):\n");

    // Lectura caracter por caracter desde teclado
    while ((input = getchar()) != EOF) {
        // Llamada al estado actual a través del puntero a función
        currentState(input);
    }

    return 0;
}
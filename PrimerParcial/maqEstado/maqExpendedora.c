#include <stdio.h>
#include <ctype.h>

typedef enum {
    SALDO_0,
    SALDO_5,
    SALDO_10,
    SALDO_15,
    SALDO_20
} Estado;

int main() {
    Estado estado = SALDO_0;
    char opcion;

    printf("=== MAQUINA EXPENDEDORA DE GOLOSINAS ===\n");
    printf("Precios: Chicle = $0.15 (15c) | Chocolate = $0.20 (20c)\n");
    printf("Opciones:\n");
    printf("  [5] Ingresar moneda de 5c\n");
    printf("  [1] Ingresar moneda de 10c\n");
    printf("  [C] Seleccionar Chicle ($0.15)\n");
    printf("  [H] Seleccionar Chocolate ($0.20)\n");
    printf("  [D] Devolucion de dinero\n");
    printf("  [Q] Salir\n");
    printf("----------------------------------------\n");

    while (1) {
        // Mostrar saldo actual
        int saldo_actual = 0;
        switch (estado) {
            case SALDO_0:  saldo_actual = 0;  break;
            case SALDO_5:  saldo_actual = 5;  break;
            case SALDO_10: saldo_actual = 10; break;
            case SALDO_15: saldo_actual = 15; break;
            case SALDO_20: saldo_actual = 20; break;
        }

        printf("\n[Saldo actual: $%0.2f (%dc)] -> Ingrese opcion: ", saldo_actual / 100.0, saldo_actual);
        if (scanf(" %c", &opcion) != 1) break;
        opcion = toupper(opcion);

        if (opcion == 'Q') {
            if (saldo_actual > 0) {
                printf("Devolviendo $%0.2f antes de salir...\n", saldo_actual / 100.0);
            }
            printf("Programa finalizado.\n");
            break;
        }

        switch (estado) {

            case SALDO_0:
                if (opcion == '5') {
                    printf(">> [Sonido]: Click\n");
                    estado = SALDO_5;
                } else if (opcion == '1') {
                    printf(">> [Sonido]: Click Click\n");
                    estado = SALDO_10;
                } else if (opcion == 'C' || opcion == 'H') {
                    printf(">> Saldo insuficiente.\n");
                } else if (opcion == 'D') {
                    printf(">> No hay dinero para devolver.\n");
                }
                break;

            case SALDO_5:
                if (opcion == '5') {
                    printf(">> [Sonido]: Click\n");
                    estado = SALDO_10;
                } else if (opcion == '1') {
                    printf(">> [Sonido]: Click Click\n");
                    estado = SALDO_15;
                } else if (opcion == 'C' || opcion == 'H') {
                    printf(">> Saldo insuficiente.\n");
                } else if (opcion == 'D') {
                    printf(">> DEVOLUCION: Se devuelven $0.05 (5c).\n");
                    estado = SALDO_0;
                }
                break;

            case SALDO_10:
                if (opcion == '5') {
                    printf(">> [Sonido]: Click\n");
                    estado = SALDO_15;
                } else if (opcion == '1') {
                    printf(">> [Sonido]: Click Click\n");
                    estado = SALDO_20;
                } else if (opcion == 'C' || opcion == 'H') {
                    printf(">> Saldo insuficiente.\n");
                } else if (opcion == 'D') {
                    printf(">> DEVOLUCION: Se devuelven $0.10 (10c).\n");
                    estado = SALDO_0;
                }
                break;

            case SALDO_15:
                if (opcion == '5') {
                    printf(">> [Sonido]: Click\n");
                    estado = SALDO_20;
                } else if (opcion == '1') {
                    printf(">> [Sonido]: Click Click (Moneda devuelta por exceso de saldo máximo)\n");
                    // Se mantiene en 20c devolviendo los 5c sobrantes de la moneda de 10
                    estado = SALDO_20;
                } else if (opcion == 'C') {
                    printf(">> ¡ENTREGANDO CHICLE! ¡Gracias por su compra!\n");
                    estado = SALDO_0;
                } else if (opcion == 'H') {
                    printf(">> Saldo insuficiente para Chocolate (faltan 5c).\n");
                } else if (opcion == 'D') {
                    printf(">> DEVOLUCION: Se devuelven $0.15 (15c).\n");
                    estado = SALDO_0;
                }
                break;

            case SALDO_20:
                if (opcion == '5' || opcion == '1') {
                    printf(">> Receptáculo lleno / Saldo máximo ($0.20) alcanzado. Moneda devuelta.\n");
                } else if (opcion == 'C') {
                    printf(">> ¡ENTREGANDO CHICLE!\n");
                    printf(">> VUELTO: Se devuelven $0.05 (5c) de cambio.\n");
                    estado = SALDO_0;
                } else if (opcion == 'H') {
                    printf(">> ¡ENTREGANDO CHOCOLATE! ¡Gracias por su compra!\n");
                    estado = SALDO_0;
                } else if (opcion == 'D') {
                    printf(">> DEVOLUCION: Se devuelven $0.20 (20c).\n");
                    estado = SALDO_0;
                }
                break;
        }
    }

    return 0;
}
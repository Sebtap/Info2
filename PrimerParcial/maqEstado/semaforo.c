#include <stdio.h>
#include <unistd.h> // Necesario para la funcion sleep() en Linux/macOS (en Windows usar <windows.h> y Sleep(ms))

typedef enum {
    ESTADO_1, // sem1: Rojo     | sem2: Verde    (30s)
    ESTADO_2, // sem1: Rojo     | sem2: Amarillo (2s)
    ESTADO_3, // sem1: Amarillo | sem2: Rojo     (2s)
    ESTADO_4, // sem1: Verde    | sem2: Rojo     (30s)
    ESTADO_5, // sem1: Amarillo | sem2: Rojo     (2s)
    ESTADO_6  // sem1: Rojo     | sem2: Amarillo (2s)
} EstadoSemaforo;

int main() {
    EstadoSemaforo estado = ESTADO_1;

    printf("=== CONTROLADOR DE SEMAFOROS INTERSECCION ===\n\n");

    while (1) {
        switch (estado) {
            case ESTADO_1:
                printf("[SEM 1: ROJO    ]  [SEM 2: VERDE   ]  | Tiempo: 30s\n");
                sleep(30);
                estado = ESTADO_2;
                break;

            case ESTADO_2:
                printf("[SEM 1: ROJO    ]  [SEM 2: AMARILLO]  | Tiempo: 2s\n");
                sleep(2);
                estado = ESTADO_3;
                break;

            case ESTADO_3:
                printf("[SEM 1: AMARILLO]  [SEM 2: ROJO    ]  | Tiempo: 2s\n");
                sleep(2);
                estado = ESTADO_4;
                break;

            case ESTADO_4:
                printf("[SEM 1: VERDE   ]  [SEM 2: ROJO    ]  | Tiempo: 30s\n");
                sleep(30);
                estado = ESTADO_5;
                break;

            case ESTADO_5:
                printf("[SEM 1: AMARILLO]  [SEM 2: ROJO    ]  | Tiempo: 2s\n");
                sleep(2);
                estado = ESTADO_6;
                break;

            case ESTADO_6:
                printf("[SEM 1: ROJO    ]  [SEM 2: AMARILLO]  | Tiempo: 2s\n");
                sleep(2);
                estado = ESTADO_1; // Vuelve a reiniciar el ciclo de la interseccion
                break;
        }
    }

    return 0;
}
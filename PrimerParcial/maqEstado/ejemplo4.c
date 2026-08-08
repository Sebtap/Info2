#include <stdio.h>
#include <stdint.h>

#define STX 0x02
#define ETX 0x03
#define MAX_BUFFER 256

// Definición de los estados de la FSM
typedef enum {
    ESTADO_WAIT_STX,
    ESTADO_WAIT_CANT,
    ESTADO_WAIT_DATOS,
    ESTADO_WAIT_CHK,
    ESTADO_WAIT_ETX
} EstadoFSM;

// Función receptora byte a byte usando la Máquina de Estados
void procesar_byte(uint8_t byte) {
    static EstadoFSM estado = ESTADO_WAIT_STX;
    static uint8_t cant_datos = 0;
    static uint8_t datos[MAX_BUFFER];
    static uint8_t indice_datos = 0;
    static uint8_t chk_calculado = 0;

    switch (estado) {
        case ESTADO_WAIT_STX:
            if (byte == STX) {
                estado = ESTADO_WAIT_CANT;
            }
            break;

        case ESTADO_WAIT_CANT:
            cant_datos = byte;
            indice_datos = 0;
            chk_calculado = 0; // Reiniciar acumulador XOR para los datos

            if (cant_datos > 0) {
                estado = ESTADO_WAIT_DATOS;
            } else {
                estado = ESTADO_WAIT_CHK; // Si son 0 datos, salta directo a CHK
            }
            break;

        case ESTADO_WAIT_DATOS:
            datos[indice_datos] = byte;
            chk_calculado ^= byte; // XOR de todos los datos recibidos
            indice_datos++;

            if (indice_datos == cant_datos) {
                estado = ESTADO_WAIT_CHK;
            }
            break;

        case ESTADO_WAIT_CHK:
            if (byte == chk_calculado) {
                estado = ESTADO_WAIT_ETX;
            } else {
                printf("\n[ERROR] Checksum incorrecto. Recibido: 0x%02X | Esperado: 0x%02X\n", byte, chk_calculado);
                estado = ESTADO_WAIT_STX; // Reset por trama corrupta
            }
            break;

        case ESTADO_WAIT_ETX:
            if (byte == ETX) {
                // Trama recibida y verificada con éxito
                printf("\n>>> TRAMA RECIBIDA CON EXITO <<<\n");
                printf("Cantidad de bytes: %d\n", cant_datos);
                printf("Contenido: ");
                for (int i = 0; i < cant_datos; i++) {
                    printf("%c", datos[i]);
                }
                printf("\n");
            } else {
                printf("\n[ERROR] Byte de fin ETX (0x03) no encontrado.\n");
            }
            estado = ESTADO_WAIT_STX; // Reinicia para escuchar la siguiente trama
            break;
    }
}

int main() {
    // Ejemplo de prueba: Enviar "HOLA"
    // 'H'=0x48, 'O'=0x4F, 'L'=0x4C, 'A'=0x41
    // Checksum XOR: 0x48 ^ 0x4F ^ 0x4C ^ 0x41 = 0x4A
    uint8_t trama_prueba[] = {
        0x02,                 // STX
        4,                    // CANT_DATOS (4 bytes)
        'H', 'O', 'L', 'A',   // DATOS
        0x4A,                 // CHK (0x48 ^ 0x4F ^ 0x4C ^ 0x41)
        0x03                  // ETX
    };

    printf("Simulando recepcion de trama byte por byte...\n");
    int tam_trama = sizeof(trama_prueba) / sizeof(trama_prueba[0]);

    for (int i = 0; i < tam_trama; i++) {
        procesar_byte(trama_prueba[i]);
    }

    return 0;
}
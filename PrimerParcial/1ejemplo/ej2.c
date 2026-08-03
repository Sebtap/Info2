/* 
### Ejercicio 2: Máquina de Estados Finitos (FSM)
Implementar una máquina de estados para el control de acceso/proceso mediante 
una matriz o tabla de transiciones:
- Definir los estados (`INICIO`, `PROCESANDO`, `ALERTA`, `FIN`) mediante `enum`.
- Definir los eventos mediante `enum`.
- Controlar el flujo de ejecución procesando eventos secuenciales y ejecutando 
    las acciones asociadas a cada transición.
 */

 /*
 Nuestra maquina tendra 4 estados y 4 eventos, que seran los siguientes:
Estados(typedef enum):
- INICIO: La maquina esta encendida pero en reposo, esperando el evento de inicio.
- PROCESANDO : La maquina esta leyendo y procesando datos de temperatura.
- ALERTA : Se detecto una temperatura critica y se activa la alerta.
- FIN : Fin de la lectura o apagado del sistema, se liberan recursos y se cierra el archivo.
Eventos(typedef enum):
- EVENTO_START :El usuario presiona el boton de inicio
- EVENTO_TEMP_NORMAL : La temperatura esta en rango seguro
- EVENTO_TEMP_ALTA : La temperatura supera el umbral critico 75.0°C
- EVENTO_EOF : Se alcanza el fin del archivo de lectura o se pide apagar.
 */
//USO METODO SWITCH-CASE

 #include <stdio.h>
#include <stdlib.h>

typedef enum {
    ESTADO_INICIO,
    ESTADO_PROCESANDO,
    ESTADO_ALERTA,
    ESTADO_FIN
} Estado;

int main() {

    FILE *archivo = fopen("temperaturas.txt", "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        return 1;
    }

    int cantidad = 0; 
    float maximo = -1000.0; 
    float acumulador = 0.0; 
    int cantidad_criticas = 0; 

    Estado estado_actual = ESTADO_INICIO; 
    float temp_aux; 

    printf("Sistema de control de temperatura iniciado.\n");

    while (estado_actual != ESTADO_FIN) {
        switch (estado_actual) {
            
            case ESTADO_INICIO:
                printf("Esperando evento de inicio...\n");
                estado_actual = ESTADO_PROCESANDO;
                break;

            case ESTADO_PROCESANDO:
                if (fscanf(archivo, "%f", &temp_aux) == 1) {
                    
                    // Procesamos la lectura común a TODAS las temperaturas
                    cantidad++;
                    acumulador += temp_aux;
                    if (temp_aux > maximo) {
                        maximo = temp_aux;
                    }

                    // Evaluamos si cambiamos de estado
                    if (temp_aux > 75.0) {
                        cantidad_criticas++; 
                        estado_actual = ESTADO_ALERTA; // Saltamos a ALERTA
                    } else {
                        printf("Lectura normal: %.2f *C\n", temp_aux);
                        estado_actual = ESTADO_PROCESANDO; 
                    }
                } else {
                    estado_actual = ESTADO_FIN; // Fin de archivo (EOF)
                }
                break;

            case ESTADO_ALERTA:
                // Se ejecuta la ACCIÓN del estado alerta para la temperatura leída anteriormente
                printf("¡ALERTA! Temperatura critica detectada: %.2f *C\n", temp_aux);
                
                // Volvemos a procesar para leer el siguiente dato en la próxima vuelta
                estado_actual = ESTADO_PROCESANDO; 
                break;

            case ESTADO_FIN:
                printf("Fin del procesamiento. Cerrando sistema.\n");
                break;
        }
    }

    fclose(archivo);

    // Muestra de informe final
    printf("\n=== Maquina de estados finalizada ===\n");
    printf("Total de temperaturas procesadas: %d\n", cantidad);
    printf("Cantidad de lecturas criticas (>75.0 *C): %d\n", cantidad_criticas);
    if (cantidad > 0) {
        printf("Valor maximo registrado: %.2f *C\n", maximo);
        printf("Promedio general: %.2f *C\n", acumulador / cantidad);
    }

    return 0;
}
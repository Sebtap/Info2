/*### Ejercicio 1: Lectura de Archivo y Procesamiento Dinámico
Dado un archivo de texto (`temperaturas.txt`) que contiene lecturas de temperatura de un sensor (un dato tipo `float` por línea):
1. Abrir el archivo de manera segura verificando punteros nulos (`NULL`).
2. Implementar memoria dinámica (`malloc` y `realloc`) para almacenar las lecturas conforme se leen.
3. Procesar los datos en una sola pasada ("al vuelo") para determinar:
   - Valor máximo registrado .
   - Promedio general de las lecturas.
   - Cantidad de lecturas que superaron la temperatura crítica Tcrit = 75.0°C.
4. Liberar la memoria reservada y cerrar el archivo adecuadamente.

---  */

#include <stdio.h>
#include <stdlib.h>

//Prototipos

int main(){

    //Al trabajar con memoria dinamica, creamos un puntero para almacenar las lecturas
    float *temperaturas = NULL; // Puntero para almacenar las lecturas
    float temp_aux; // Variable auxiliar para recibir cada lectura
    int cantidad = 0; // Contador de la cantidad de lecturas
    float maximo = -1000.0; // Inicializamos el valor máximo a un valor muy bajo
    float acumulador = 0.0; // Acumulador para calcular el promedio
    int cantidad_criticas = 0; // Contador de lecturas críticas

    //Abrimos el archivo de manera segura y verificamos si se abrió correctamente
    FILE *archivo=fopen("temperaturas.txt","r");
    if(archivo == NULL){
        fprintf(stderr,"Error al abrir el archivo\n");
        return 1;
    }

    //Lectura de las temperaturas y procesamiento dinámico
    //Al ser tipo texto plano, podemos leer línea por línea y convertir a float, con la funcion fscanf
    //Los argumentos de fscanf son: el puntero al archivo, el formato de lectura y la dirección de memoria donde se almacenará el valor leído
    while(fscanf(archivo, "%f", &temp_aux) == 1){
        //Reservamos memoria dinámica en el HEAP para almacenar la nueva lectura
        cantidad++; // Incrementamos la cantidad de lecturas
        float *temp_nueva= realloc(temperaturas, cantidad * sizeof(float));
        if(temp_nueva == NULL){
            fprintf(stderr,"Error al asignar memoria\n");
            free(temperaturas); // Liberamos la memoria previamente asignada
            fclose(archivo); // Cerramos el archivo antes de salir
            return 1;
        }
        temperaturas = temp_nueva; // Actualizamos el puntero al nuevo bloque de memoria
        temperaturas[cantidad - 1] =temp_aux; // Almacenamos la nueva lectura en el arreglo dinámico

        // Hacemos los calculos al vuelo: valor máximo, promedio y cantidad de lecturas críticas
        acumulador += temp_aux; // Acumulamos para el promedio
        if(temp_aux > maximo){
            maximo = temp_aux; // Actualizamos el valor máximo
        }

        //Conteo de superacion de umbral critico (>75.0°C)
        if(temp_aux > 75.0){
            cantidad_criticas++;
        }

    }

    //Cerramos el archivo(Ya no necesitamos el puntero al archivo)
    fclose(archivo);

    // Muestra de resultados
    if(cantidad > 0){
        float promedio = acumulador / cantidad;
        printf("Valor maximo registrado: %.2f°C\n", maximo);
        printf("Promedio general de las lecturas: %.2f°C\n", promedio);
        printf("Cantidad de lecturas que superaron la temperatura critica (75.0°C): %d\n", cantidad_criticas);
    } else {
        printf("No se leyeron temperaturas del archivo.\n");
    }
}
/*
Una universidad guarda los datos de sus alumnos en un archivo binario 
alumnos.dat. Cada registro tiene:
Legajo (int)
Nombre (char[50])
Promedio (float)
Se solicita armar un programa que:
Lectura y Estadísticas (fseek / ftell):
Abrir alumnos.dat en modo binario ("rb").
Usar fseek y ftell para calcular la cantidad total de registros grabados 
sin leer el archivo entero con un bucle.
Memoria Dinámica (malloc / realloc):
Reservar memoria dinámica exacta para cargar todos los alumnos a un 
vector en RAM.
Cargar los registros usando fread.
Cálculos e Informes:
Calcular cuál es el promedio máximo de toda la universidad.
Exportación a Texto (fprintf):
Generar un reporte en un archivo de texto reporte_top.txt que guarde 
únicamente a los alumnos con promedio elevado (>=8.0).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int legajo;
    char nombre[50];
    float promedio;
} Alumno;

int main() {
    FILE *f_bin, *f_txt;
    
    // =========================================================================
    // 1. USO DE fseek() Y ftell() PARA CONTAR REGISTROS
    // =========================================================================
    f_bin = fopen("alumnos.dat", "rb");
    if (f_bin == NULL) {
        printf("Error: No se pudo abrir 'alumnos.dat'.\n");
        return 1;
    }

    // Mover el puntero de lectura al FINAL del archivo
    fseek(f_bin, 0, SEEK_END);
    
    // ftell nos dice cuántos BYTES mide el archivo completo
    long tamano_total_bytes = ftell(f_bin);
    
    // Cantidad = Total Bytes / Bytes de 1 Alumno
    int total_alumnos = tamano_total_bytes / sizeof(Alumno);

    printf("El archivo contiene %d alumno(s) grabado(s).\n", total_alumnos);

    if (total_alumnos == 0) {
        fclose(f_bin);
        return 0;
    }

    // Regresamos el puntero al INICIO para poder leerlos
    fseek(f_bin, 0, SEEK_SET);

    // =========================================================================
    // 2. MEMORIA DINÁMICA (malloc)
    // =========================================================================
    // Reservamos en RAM el espacio exacto para el vector de alumnos
    Alumno *vector = (Alumno *) malloc(total_alumnos * sizeof(Alumno));
    if (vector == NULL) {
        printf("Error: Memoria insuficiente.\n");
        fclose(f_bin);
        return 1;
    }

    // Leemos TODOS los alumnos del binario de un solo golpe al vector dinámico
    fread(vector, sizeof(Alumno), total_alumnos, f_bin);
    fclose(f_bin); // Ya tenemos los datos en la RAM, cerramos el binario.

    // =========================================================================
    // 3. CÁLCULO DE MÁXIMO PROMEDIO Y EXPORTACIÓN A TEXTO
    // =========================================================================
    f_txt = fopen("reporte_top.txt", "w"); // "w" para archivo de TEXTO
    if (f_txt == NULL) {
        printf("Error al crear el archivo de texto.\n");
        free(vector);
        return 1;
    }

    float max_promedio = vector[0].promedio;
    int i;

    // Encabezado del archivo de texto
    fprintf(f_txt, "=== ALUMNOS DESTACADOS (PROMEDIO >= 8.0) ===\n\n");

    for (i = 0; i < total_alumnos; i++) {
        // Buscar el máximo
        if (vector[i].promedio > max_promedio) {
            max_promedio = vector[i].promedio;
        }

        // Si cumple la condición, lo escribimos en el archivo de TEXTO
        if (vector[i].promedio >= 8.0) {
            fprintf(f_txt, "Legajo: %d | Nombre: %-20s | Promedio: %.2f\n", 
                    vector[i].legajo, vector[i].nombre, vector[i].promedio);
        }
    }

    printf("\n--> El promedio maximo alcanzado fue: %.2f\n", max_promedio);
    printf("--> Se exporto el informe a 'reporte_top.txt'.\n");

    // =========================================================================
    // 4. LIMPIEZA
    // =========================================================================
    fclose(f_txt);
    free(vector); // ¡SIEMPRE liberar la memoria reservada con malloc!

    return 0;
}


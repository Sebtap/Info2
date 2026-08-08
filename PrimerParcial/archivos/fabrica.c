/*
	Se dispone de un archivo llamado Stock.dat que contiene la información 
    de los 10 productos que vende una fábrica. En el archivo se guarda: 
•	Código de artículo (entero) 
•	Descripción (50 caracteres máximo) 
•	Stock (entero) 
	
Luego se ingresan por teclado las ventas a realizar indicando: 
•	Código de artículo 
•	Cantidad 

Ls carga de las ventas se envían como parámetros en el main() (podrá ser más 
de una a la vez).
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar 
el stock de dicho producto, sino hay stock se debe vender lo que quede 
disponible y grabar un registro en un archivo Faltantes.dat con la cantidad 
que no pudo venderse, dicho registro debe contener: 
•	Código de artículo 
•	Cantidad 
Se genera un registro por cada venta que no pudo concretarse, pudiendo quedar 
en el archivo varios registros faltantes del mismo producto. 
Al finalizar actualizar el archivo Stock.dat con el stock actualizado luego 
de procesar las ventas.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructuras según la consigna
typedef struct {
    int codigo;
    char descripcion[50];
    int stock;
} Producto;

typedef struct {
    int codigo;
    int cantidad;
} Faltante;

int main(int argc, char *argv[]) {
    // 1. Validar que los parametros vengan en pares (Codigo Cantidad)
    // argc debe ser impar: 1 (nombre del programa) + un numero par de argumentos
    if (argc < 3 || (argc - 1) % 2 != 0) {
        printf("Uso correcto: %s <cod1> <cant1> [<cod2> <cant2> ...]\n", argv[0]);
        return 1;
    }

    // 2. Abrir archivo Stock.dat en modo "rb+" (lectura/escritura)
    FILE *f_stock = fopen("Stock.dat", "rb+");
    if (f_stock == NULL) {
        fprintf(stderr, "Error: No se pudo abrir Stock.dat\n");
        return 1;
    }

    // Cargar los 10 productos a memoria (arreglo)
    Producto productos[10];
    size_t leidos = fread(productos, sizeof(Producto), 10, f_stock);

    // 3. Abrir archivo Faltantes.dat en modo "ab" (append binario para agregar registros)
    FILE *f_faltantes = fopen("Faltantes.dat", "ab");
    if (f_faltantes == NULL) {
        fprintf(stderr, "Error: No se pudo abrir Faltantes.dat\n");
        fclose(f_stock);
        return 1;
    }

    // 4. Procesar las ventas pasadas como parametros en el main
    for (int i = 1; i < argc; i += 2) {
        int cod_venta = atoi(argv[i]);
        int cant_venta = atoi(argv[i + 1]);
        int encontrado = 0;

        for (int j = 0; j < leidos; j++) {
            if (productos[j].codigo == cod_venta) {
                encontrado = 1;

                if (productos[j].stock >= cant_venta) {
                    // Hay stock suficiente: se resta directo
                    productos[j].stock -= cant_venta;
                } else {
                    // Stock insuficiente: vender lo que quede y grabar el faltante
                    int no_vendido = cant_venta - productos[j].stock;
                    productos[j].stock = 0; // Se agota el stock disponible

                    // Registrar en Faltantes.dat
                    Faltante reg_faltante;
                    reg_faltante.codigo = cod_venta;
                    reg_faltante.cantidad = no_vendido;

                    fwrite(&reg_faltante, sizeof(Faltante), 1, f_faltantes);
                    printf(" Alerta: Stock insuficiente para codigo %d. Faltante grabado: %d unidades.\n", 
                           cod_venta, no_vendido);
                }
                break;
            }
        }

        if (!encontrado) {
            printf(" Advertencia: El articulo codigo %d no fue encontrado en el stock.\n", cod_venta);
        }
    }

    // Cerrar archivo de faltantes
    fclose(f_faltantes);

    // 5. Reescribir el archivo Stock.dat con el stock actualizado
    fseek(f_stock, 0L, SEEK_SET); // Volver al inicio del archivo
    fwrite(productos, sizeof(Producto), leidos, f_stock);
    fclose(f_stock);

    printf("\nProcesamiento de ventas finalizado con exito.\n");
    return 0;
}
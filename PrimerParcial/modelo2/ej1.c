/*
# Ejercicio 1 - Archivos

Se dispone de un archivo llamado Stock.dat que contiene la información de los 
10 productos que vende una fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)

Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad

Ls carga de las ventas se envían como parámetros en el main() (podrá ser más 
de una a la vez).
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar 
el stock de dicho producto, sino hay stock se debe vender lo que quede 
disponible y grabar un registro en un archivo Faltantes.dat con la cantidad 
que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad  
Se genera un registro por cada venta que no pudo concretarse, pudiendo quedar 
en el archivo varios registros faltantes del mismo producto.
Al finalizar actualizar el archivo Stock.dat con el stock actualizado luego 
de procesar las ventas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANT_PRODUCTOS 10

// 1. DEFINICIÓN DE ESTRUCTURAS DE DATOS

// Estructura para el archivo Stock.dat
typedef struct {
    int codigo;
    char descripcion[50];
    int stock;
} Producto;

// Estructura para el archivo Faltantes.dat
typedef struct {
    int codigo;
    int cantidad_faltante;
} Faltante;

// Función auxiliar para buscar el índice de un producto por su código
int buscar_producto(Producto productos[], int cantidad, int codigo_buscado) {
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].codigo == codigo_buscado) {
            return i; // Retorna la posición del producto en el arreglo
        }
    }
    return -1; // No encontrado
}

int main(int argc, char *argv[]) {

    // ------------------------------------------------------------------
    // PASO 1: VALIDAR PARÁMETROS DE ENTRADA (argc / argv)
    // ------------------------------------------------------------------
    // argv[0] es el nombre del ejecutable.
    // Los argumentos restantes vienen de a pares (codigo, cantidad).
    // Por ende, (argc - 1) debe ser un número PAR y mayor a 0.
    if (argc < 3 || (argc - 1) % 2 != 0) {
        printf("Uso correcto: %s <cod_art1> <cant1> [<cod_art2> <cant2> ...]\n", argv[0]);
        printf("Ejemplo: %s 101 5 102 20\n", argv[0]);
        return 1;
    }

    // ------------------------------------------------------------------
    // PASO 2: CARGAR Stock.dat EN MEMORIA
    // ------------------------------------------------------------------
    FILE *arch_stock = fopen("Stock.dat", "rb");
    if (arch_stock == NULL) {
        fprintf(stderr, "Error: No se pudo abrir el archivo Stock.dat\n");
        return 1;
    }

    Producto productos[CANT_PRODUCTOS];
    size_t leidos = fread(productos, sizeof(Producto), CANT_PRODUCTOS, arch_stock);
    fclose(arch_stock);

    if (leidos < CANT_PRODUCTOS) {
        printf("Advertencia: Se leyeron %zu productos de los %d esperados.\n", leidos, CANT_PRODUCTOS);
    }

    printf("=== PROCESANDO VENTAS DESDE LÍNEA DE COMANDOS ===\n\n");

    // Abrimos el archivo de faltantes en modo "ab" (Append Binary)
    // para ir agregando registros sin borrar los faltantes existentes.
    FILE *arch_faltantes = fopen("Faltantes.dat", "ab");
    if (arch_faltantes == NULL) {
        fprintf(stderr, "Error al abrir o crear Faltantes.dat\n");
        return 1;
    }

    // ------------------------------------------------------------------
    // PASO 3 Y 4: PROCESAR LAS VENTAS Y REGISTRAR FALTANTES
    // ------------------------------------------------------------------
    // Recorremos los argumentos de a 2 en 2
    for (int i = 1; i < argc; i += 2) {
        int cod_venta = atoi(argv[i]);       // Convertimos argumento texto a int
        int cant_venta = atoi(argv[i + 1]);  // Convertimos argumento texto a int

        printf("-> Intento de Venta: Codigo %d | Cantidad Pedida: %d\n", cod_venta, cant_venta);

        int pos = buscar_producto(productos, CANT_PRODUCTOS, cod_venta);

        if (pos == -1) {
            printf("   [ERROR] El codigo de producto %d no existe en el catalogo.\n\n", cod_venta);
            continue;
        }

        Producto *p = &productos[pos]; // Puntero al producto actual para código más limpio

        // CASO A: Stock suficiente
        if (p->stock >= cant_venta) {
            p->stock -= cant_venta;
            printf("   [EXITO] Venta realizada. Nuevo stock de '%s': %d\n\n", p->descripcion, p->stock);
        }
        // CASO B y C: Stock insuficiente o nulo
        else {
            int no_pudo_venderse = cant_venta - p->stock;

            printf("   [FALTANTE] Stock insuficiente (%d disponibles). Se vendieron %d unidades.\n", 
                   p->stock, p->stock);
            printf("   -> Registrando faltante de %d unidades para el articulo %d...\n\n", 
                   no_pudo_venderse, p->codigo);

            // El stock del producto pasa a ser 0
            p->stock = 0;

            // Grabamos el registro del faltante en Faltantes.dat
            Faltante registro_faltante;
            registro_faltante.codigo = cod_venta;
            registro_faltante.cantidad_faltante = no_pudo_venderse;

            fwrite(&registro_faltante, sizeof(Faltante), 1, arch_faltantes);
        }
    }

    // Cerramos el archivo de faltantes
    fclose(arch_faltantes);

    // ------------------------------------------------------------------
    // PASO 5: ACTUALIZAR EL ARCHIVO Stock.dat
    // ------------------------------------------------------------------
    arch_stock = fopen("Stock.dat", "wb"); // "wb" sobrescribe el archivo completo
    if (arch_stock == NULL) {
        fprintf(stderr, "Error al intentar actualizar Stock.dat\n");
        return 1;
    }

    fwrite(productos, sizeof(Producto), CANT_PRODUCTOS, arch_stock);
    fclose(arch_stock);

    printf("=== PROCESO FINALIZADO Y ARCHIVO Stock.dat ACTUALIZADO ===\n");

    return 0;
}
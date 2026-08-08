/*
Se tiene un archivo lista.dat que contiene la Base de Datos de articulus de un
negocio:
- Numero de articulo (int).
- Descripcion (string de 30 caracteres).
- Precio (float).
- Proveedor (string de 30).
- Stock (int).
Actualizar esta Base de Datos aplicando un 20% de aumento a todos los articulos
del proveedor Perez.
Realizar tambien el programa que genere la base de datos y verificar que
funcionan en conjunto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura según la consigna
typedef struct {
    int num_articulo;
    char descripcion[30];
    float precio;
    char proveedor[30];
    int stock;
} Articulo;

// Prototipos de funciones
void generarBaseDeDatos();
void actualizarPreciosPerez();
void mostrarBaseDeDatos();

int main() {
    printf("1. Creando la base de datos inicial con datos de prueba...\n");
    generarBaseDeDatos();
    
    printf("\n--- CONTENIDO ORIGINAL ---\n");
    mostrarBaseDeDatos();

    printf("\n2. Aplicando aumento del 20%% a productos del proveedor 'Perez'...\n");
    actualizarPreciosPerez();

    printf("\n--- CONTENIDO ACTUALIZADO ---\n");
    mostrarBaseDeDatos();

    return 0;
}

// 1. Función que genera el archivo binario lista.dat con datos de prueba
void generarBaseDeDatos() {
    FILE *arch = fopen("lista.dat", "wb"); // "wb" crea o sobrescribe el binario
    if (arch == NULL) {
        fprintf(stderr, "Error al crear lista.dat\n");
        return;
    }

    Articulo listaPrueba[4] = {
        {101, "Martillo", 1000.0f, "Perez", 15},
        {102, "Destornillador", 500.0f, "Gomez", 30},
        {103, "Clavos x100", 200.0f, "Perez", 50},
        {104, "Pintura 1L", 2500.0f, "Lopez", 8}
    };

    fwrite(listaPrueba, sizeof(Articulo), 4, arch);
    fclose(arch);
}

// 2. Función que modifica el archivo binario en el lugar
void actualizarPreciosPerez() {
    // "rb+" permite LEER y ESCRIBIR en el archivo sin borrar su contenido
    FILE *arch = fopen("lista.dat", "rb+");
    if (arch == NULL) {
        fprintf(stderr, "Error al abrir lista.dat para modificar\n");
        return;
    }

    Articulo art;

    // Leemos registro por registro
    while (fread(&art, sizeof(Articulo), 1, arch) == 1) {
        
        // Si el proveedor es "Perez"
        if (strcmp(art.proveedor, "Perez") == 0) {
            art.precio *= 1.20f; // Aumento del 20%

            // CLAVE DE EXAMEN: El fread avanzó el cursor 1 registro hacia adelante.
            // Debemos retroceder 1 registro (SEEK_CUR) para sobrescribir EL MISMO articulo.
            fseek(arch, -((long)sizeof(Articulo)), SEEK_CUR);

            // Sobrescribimos el registro actualizado
            fwrite(&art, sizeof(Articulo), 1, arch);

            // Sincronizamos el flujo para poder continuar leyendo correctamente con fread
            fseek(arch, 0L, SEEK_CUR);
        }
    }

    fclose(arch);
}

// 3. Función auxiliar para leer y mostrar la base de datos completa
void mostrarBaseDeDatos() {
    FILE *arch = fopen("lista.dat", "rb");
    if (arch == NULL) {
        fprintf(stderr, "Error al abrir lista.dat para leer\n");
        return;
    }

    Articulo art;
    while (fread(&art, sizeof(Articulo), 1, arch) == 1) {
        printf("ID: %d | Desc: %-15s | Precio: $%8.2f | Prov: %-8s | Stock: %d\n",
               art.num_articulo, art.descripcion, art.precio, art.proveedor, art.stock);
    }

    fclose(arch);
}
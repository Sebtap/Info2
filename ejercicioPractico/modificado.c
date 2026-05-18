#include <stdio.h>
#include <stdlib.h>

//La estructura va ubicada antes de los prototipos de las funciones para que estas puedan usarla sin problemas. Si la estructura estuviera después de los prototipos, el compilador no sabría qué es "Producto" cuando lo vea en los prototipos y daría un error de compilación.
typedef struct {
    int codigo;
    float precio;
    char descripcion[50];
} Producto;


void agregarProducto(FILE*);

int main(int argc, char *argv[]) {
    // VALIDACIÓN: Si argc es menor a 2, significa que el usuario no pasó el archivo
    if (argc < 2) {
        printf("Error de argumentos.\n");
        printf("Uso correcto: %s <nombre_del_archivo.dat>\n", argv[0]);
        return 1; // Cortamos el programa acá para evitar un Segmentation Fault
    }

    // PUNTOS B y C: Asignamos la dirección de memoria que tiene argv[1]
    // Si en la terminal pones "./programa.exe productos.dat", argv[1] tiene "productos.dat"
    char *archivo_binario = argv[1]; 

    printf("Trabajando con el archivo: %s\n", archivo_binario);

    // ==========================================
    // EJECUCIÓN DEL PUNTO D
    // ==========================================
    // Llamás a tu función pasándole el puntero dinámico que vino por el main
    agregar_producto(archivo_binario);


    // ==========================================
    // EL RESTO DE TUS FUNCIONES (Listar, Aumento, etc.)
    // ==========================================
    // A todas las funciones que ya tenías hechas, ahora en vez de pasarles "productos.dat", 
    // les pasás la variable 'archivo_binario'. Ejemplo:
    //
    // mostrar_productos(archivo_binario);
    // aumento_masivo_teclado(archivo_binario);
    // exportar_a_texto(archivo_binario, "productos.txt");

    return 0;
}

////////////////////////////////////////
void agregarProducto(FILE* fp) {
    Producto p;

    printf("\n--- AGREGAR NUEVO PRODUCTO ---\n");

    // Pedir los datos al usuario
    printf("Ingrese codigo: ");
    scanf("%d", &p.codigo);
    fflush(stdin);

    printf("Ingrese descripcion: ");
    gets(p.descripcion);

    printf("Ingrese precio: ");
    scanf("%f", &p.precio);

    //  Posicionar el puntero al final del archivo
    fseek(fp, 0, SEEK_END);

    // Escribir el registro
    if (fwrite(&p, sizeof(Producto), 1, fp) == 1) {
        printf("\n[SISTEMA] Producto agregado con exito al final del archivo.\n");
    } else {
        printf("\n[ERROR] No se pudo escribir en el archivo.\n");
    }

    // Sincronizamos (buena practica en archivos r+b)
    fseek(fp, 0, SEEK_CUR);
}
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char descripcion[30];
    float precio;
    char proveedor[30];
    int stock;
} t_articulo;

int main() {
    FILE *fp = fopen("lista.dat", "wb");
    if (!fp) return 1;

    t_articulo lista[] = {
        {101, "Tornillos 1/4", 100.0, "Perez", 50},
        {102, "Tuercas", 50.0, "Gomez", 100},
        {103, "Clavos", 80.0, "Perez", 200},
        {104, "Arandelas", 20.0, "Lopez", 300}
    };

    // Escribimos los 4 artículos de un tirón
    fwrite(lista, sizeof(t_articulo), 4, fp);

    fclose(fp);
    printf("Archivo lista.dat generado con exito.\n");
    return 0;
}
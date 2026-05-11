/*Se tiene un archivo lista.dat que contiene la Base de Datos 
de artículos de un negocio: 
• Número de artículo(int), 
• Descripción (string de 30 caracteres), 
• precio (float), • proveedor( string de 30) 
• stock(int). 
Actualizar esta Base de Datos aplicando un 20% de aumento a 
todos los artículos del proveedor Pérez. Realizar también el 
programa que genere la base de datos y verificar que funcionen 
en conjunto. */

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
    FILE *fp = fopen("lista.dat", "rb+"); // rb+ es clave para modificar sin borrar
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    t_articulo art;
    int contador = 0;

    // Leemos registro por registro
    while (fread(&art, sizeof(t_articulo), 1, fp)) {
        
        // Comparamos el proveedor (usamos strcmp de string.h)
        if (strcmp(art.proveedor, "Perez") == 0) {
            
            // Aplicamos el aumento del 20%
            art.precio = art.precio * 1.20; 

            // EXPLICACION DEL MOVIMIENTO:
            // Al leer (fread), el cursor avanza al siguiente registro.
            // Para sobreescribir el que acabamos de leer, retrocedemos uno.
            fseek(fp, -sizeof(t_articulo), SEEK_CUR);
            
            // Grabamos el registro modificado en el mismo lugar
            fwrite(&art, sizeof(t_articulo), 1, fp);
            
            // IMPORTANTE: Después de un fwrite en modo rb+, se recomienda 
            // posicionar el cursor para la siguiente lectura.
            fseek(fp, 0, SEEK_CUR); 

            printf("Articulo %d actualizado. Nuevo precio: %.2f\n", art.id, art.precio);
            contador++;
        }
    }

    fclose(fp);
    printf("Proceso terminado. Se actualizaron %d articulos.\n", contador);
    return 0;
}
#include <stdio.h>
#include <tchar.h> // Para usar _tmain y _TCHAR, que son compatibles con Unicode y ANSI dependiendo de la configuración del proyecto. Esto permite que el programa pueda manejar caracteres especiales y acentos en la consola sin problemas de codificación.
#include <wchar.h> // Para usar funciones de manejo de cadenas anchas (wide characters) como wprintf, wscanf, etc. Esto es útil para trabajar con caracteres Unicode y evitar problemas de codificación en la consola, especialmente en sistemas Windows donde la consola puede no manejar correctamente los caracteres especiales con funciones estándar como printf y scanf.
#include <string.h> // Para usar funciones de manejo de cadenas como strcmp, strcpy, etc

/// DEFINICION DE LA ESTRUCTURA PRODUCTO
// Una estructura es un tipo de dato definido por el usuario que agrupa varias variables bajo un mismo nombre. En este caso, la estructura "Producto" tiene tres campos: "codigo" (un entero), "precio" (un flotante) y "descripcion" (un arreglo de caracteres de tamaño 50). Esta estructura se utiliza para representar la información de un producto en el sistema de gestión de una ferretería.
// Es ubicada en la Ram y cada campo se accede a traves de un punto (.) o una flecha (->) dependiendo si es una variable o un puntero a la estructura.
//cada producto va a ocupar 58 bytes (4+4+50) en el disco y la ram y el archivo se maneja como un conjunto de registros de 58 bytes cada uno.
typedef struct {
    int codigo;
    float precio;
    char descripcion[50];
} Producto;

void mostrarArchivo(FILE *);
void modificarPrecioDeTodo(FILE*,float);
void modificarPrecio(FILE*,char*,float);
void exportarTexto(FILE* );
void mostrarTexto(void );
void ordenarPorPrecio(FILE*);

//los argumnetos y el main se definen asi para que el programa pueda recibir argumentos desde la linea de comandos, lo que permite ejecutar el programa con diferentes opciones sin necesidad de modificar el código fuente. Por ejemplo, se puede ejecutar el programa con un argumento que indique un porcentaje de aumento para aplicar a los precios de los productos al iniciar el programa, lo que hace que sea más flexible y adaptable a diferentes situaciones sin necesidad de recompilar el código cada vez.
int _tmain(int argc, _TCHAR* argv[])
{
    FILE *fp;
    float porc; // Variable para almacenar el porcentaje de aumento
    char nombreBuscado[50]; // Variable para almacenar el nombre del producto a buscar
    float nuevoPrecio; // Variable para almacenar el nuevo precio a asignar
    int opcion = 0; // Variable para almacenar la opción seleccionada por el usuario

    // 1. Apertura del archivo binario
    if ((fp = fopen("C:\\Users\\na_ca\\infoII\\productos.dat", "r+b")) == NULL) {
        printf("\n[ERROR] No se pudo abrir el archivo.\n");
        return 0;
    }

    // Procesamiento por argumento inicial (argv[2])
    if (argc > 2) {
        sscanf(argv[2], "%f", &porc);
        printf("\n[SISTEMA] Argumento detectado. Aplicando aumento inicial del %f%%...\n", porc);
        modificarPrecioDeTodo(fp, porc);
    }

    // 3. MENU PRINCIPAL ACTUALIZADO
    while (opcion != 6) {
        printf("\n--- SISTEMA DE GESTION (Ferreteria) ---");
        printf("\n1. Listar productos (Binario)");
        printf("\n2. Aplicar aumento masivo (Teclado)");
        printf("\n3. Modificar precio por nombre");
        printf("\n4. Exportar a productos.txt (Pipes)");
        printf("\n5. Mostrar archivo productos.txt");
        printf("\n6. Ordenar por precio (Archivo porPrecio.dat)");
        printf("\n7. Salir");   
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarArchivo(fp);
                break;

            case 2:
                printf("\nIngrese el porcentaje de aumento: ");
                scanf("%f", &porc);
                modificarPrecioDeTodo(fp, porc);
                printf("[OK] Precios actualizados.\n");
                break;

            case 3:
                printf("\nIngrese nombre del producto: ");
                fflush(stdin); // Limpiar el buffer de entrada para evitar problemas con gets
                gets(nombreBuscado); // Usamos gets para leer la descripcion con espacios, aunque es inseguro, se recomienda usar fgets en produccion
                printf("Ingrese el nuevo precio: ");
                scanf("%f", &nuevoPrecio);
                modificarPrecio(fp, nombreBuscado, nuevoPrecio);
                break;

            case 4:
                exportarTexto(fp);
                break;

            case 5:
                mostrarTexto();
                break;
            case 6:
                ordenarPorPrecio(fp);
                break;
            case 7:
                printf("\nCerrando archivos y saliendo...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }
    }

    fclose(fp);
    return 0;
}
 ////////////////////////////////////////////////////////////////
// Funcion para mostrar el contenido del archivo binario de productos. Lee cada registro del archivo y lo muestra en un formato tabular con encabezados para facilitar la lectura. Utiliza la función "rewind" para asegurarse de que la lectura comience desde el principio del archivo.
// recibe un file *fp porque necesita acceder al archivo para leer los productos y mostrarlos en pantalla. El puntero "fp" se utiliza para posicionarse al inicio del archivo y luego leer cada registro de producto hasta el final, mostrando su código, precio y descripción de manera formateada. 
void mostrarArchivo(FILE *fp) {

	Producto p; // Variable para almacenar temporalmente cada producto leído del archivo
	// Posicionamos el puntero al inicio del archivo para asegurarnos de leer desde el principio
    rewind(fp);  // es igual a fseek(fp, 0, SEEK_SET);

    printf("\n==========================================================\n");
    printf("%-10s | %-12s | %-30s\n", "CODIGO", "PRECIO", "DESCRIPCION");
    printf("----------------------------------------------------------\n");

    // Leemos cada producto del archivo y lo mostramos en pantalla
    //fread devuelve la cantidad de elementos leidos, en este caso 1 si se leyo un producto correctamente, o 0 si se llego al final del archivo
    // cada argumento de fread es: 1) la direccion donde se va a guardar el producto leido, 2) el tamaño de cada producto, 3) la cantidad de productos a leer (en este caso 1), y 4) el puntero al archivo
    while (fread(&p, sizeof(Producto), 1, fp) == 1) {
        printf("%-10d | $ %-10.2f | %-30s\n",p.codigo,p.precio,p.descripcion);
    }

    printf("==========================================================\n");

}
 /////////////////////////////////////////////////////////

void modificarPrecioDeTodo(FILE* fp,float porc){
    Producto p;

    fseek(fp, 0, SEEK_SET);   //  es lo mismo que rewind(fp)
    // Recorremos el archivo leyendo cada producto
    // fread devuelve la cantidad de elementos leidos, en este caso 1 si se leyo un producto correctamente, o 0 si se llego al final del archivo
    // &p es la direccion donde se va a guardar el producto leido, sizeof(Producto) es el tamaño de cada producto, 1 es la cantidad de productos a leer (en este caso 1), y fp es el puntero al archivo
    //sizeof(Producto) es 58 bytes, entonces cada vez que se lee un producto, el puntero del archivo avanza 58 bytes hacia adelante
    //tercer argumento de fread es la cantidad de productos a leer, en este caso 1, entonces se lee un producto a la vez
    //cuarto argumento es el puntero al archivo, que se va a ir moviendo a medida que se leen los productos
    while (fread(&p, sizeof(Producto), 1, fp) == 1) {
        p.precio += (p.precio * (porc / 100));

        // Retrocedemos para pisar el registro
        //fseeek se utiliza para mover el puntero del archivo a una posición específica. En este caso, se mueve hacia atrás el tamaño de un producto para volver a la posición del registro que se acaba de leer, de modo que al escribir el producto modificado, se sobrescriba el mismo registro en lugar de agregar uno nuevo al final del archivo.
        // El primer argumento es el puntero al archivo, el segundo argumento es el número de bytes a mover (en este caso, el tamaño de un producto), y el tercer argumento indica que se debe mover hacia atrás desde la posición actual del puntero (SEEK_CUR).
        // Se hace porque fread avanzó automáticamente al siguiente registro después de leer.
        fseek(fp, -sizeof(Producto), SEEK_CUR);
        // Escribimos el producto modificado en la misma posición del archivo para actualizarlo
        // 3. Aplastamos el registro viejo con el nuevo precio ya modificado
        fwrite(&p, sizeof(Producto), 1, fp);

        // Sincronizamos el flujo
        // 4. Sincronizamos el buffer del stream para que la próxima lectura sea limpia
        // fseek con SEEK_CUR y un desplazamiento de 0 se utiliza para sincronizar el flujo del archivo después de una operación de escritura. Esto asegura que cualquier cambio realizado en el archivo se refleje correctamente en el sistema de archivos y que el puntero del archivo esté en la posición correcta para la próxima operación de lectura o escritura.
        fseek(fp, 0, SEEK_CUR);
    }
}
 /////////////////////////////////////////////////////////
void modificarPrecio(FILE* fp, char* nombreBuscado, float nuevoPrecio) {

    Producto p;
    int encontrado = 0;

    fseek(fp, 0, SEEK_SET); // Posicionamos el puntero al inicio del archivo para comenzar a buscar desde el principio

    // Recorremos el archivo buscando la coincidencia
    // fread devuelve la cantidad de elementos leidos, en este caso 1 si se leyo un producto correctamente, o 0 si se llego al final del archivo
    while (fread(&p, sizeof(Producto), 1, fp) == 1 && encontrado==0) {

        if (strcmp(p.descripcion, nombreBuscado) == 0 ) {
            p.precio = nuevoPrecio;
            // Volvemos atras un registro para sobreescribir
            fseek(fp, -sizeof(Producto), SEEK_CUR);
            fwrite(&p, sizeof(Producto), 1, fp);
            printf("\n[OK] Producto '%s' actualizado con exito.\n", nombreBuscado);
            fseek(fp, 0, SEEK_SET);
            encontrado = 1;
        }
    }
    // !encontrado es lo mismo que encontrado == 0, es decir, si no se encontro el producto buscado en el archivo, se muestra un mensaje de error indicando que no se pudo encontrar el producto con el nombre especificado.
    if (!encontrado) {
        printf("\n[ERROR] No se encontro el producto: %s\n", nombreBuscado);
    }
}
////////////////////////////////////////////////////////////////////
// Función para exportar el contenido del archivo binario a un archivo de texto con formato delimitado por pipes. Lee cada producto del archivo binario y lo escribe en el archivo de texto en un formato específico (codigo|precio|descripcion). Al finalizar, cierra el archivo de texto y muestra un mensaje de confirmación.
//pipes es un formato de texto donde cada campo de un registro está separado por un carácter específico, en este caso el pipe (|). Esto facilita la lectura y procesamiento del archivo de texto, ya que se puede dividir cada línea en campos utilizando el pipe como delimitador.
void exportarTexto(FILE* fp) {
    FILE* txt  ;
    Producto p;
    if ((txt=fopen("productos.txt", "wt")) == NULL ) {
        printf("Error al abrir archivos productos.txt.\n");
        return;
    }

    rewind(fp); // Empezamos desde el inicio del binario

    while (fread(&p, sizeof(Producto), 1, fp) == 1) {
        fprintf(txt, "%d|%.2f|%s\n", p.codigo, p.precio, p.descripcion);
    }

    fclose(txt);
    printf("\n Datos exportados a productos.txt correctamente.\n");
}

void mostrarTexto() {
    FILE* txt ;
    if ((txt=fopen("productos.txt", "rt")) == NULL) {
        printf("Error: No existe el archivo de texto.\n");
        return;
    }

    char linea[150];
    printf("\n--- CONTENIDO DEL ARCHIVO TXT (Con Pipes) ---\n");

    // Leemos linea por linea hasta el final
    //fgets lee una línea completa del archivo, incluyendo el salto de línea, y la almacena en el arreglo "linea". El segundo argumento especifica el tamaño máximo a leer para evitar desbordamientos. El tercer argumento es el puntero al archivo desde el cual se va a leer. El bucle continúa hasta que fgets devuelve NULL, lo que indica que se ha llegado al final del archivo o que ocurrió un error durante la lectura.
    //fgets devuelve un puntero a la cadena leida si se leyo correctamente, o NULL si se llego al final del archivo o hubo un error
    while (fgets(linea, sizeof(linea), txt) != NULL) {
        printf("%s", linea);
    }

    fclose(txt);
}










//////////////////////////////////
void ordenarPorPrecio(FILE* fp) {
    Producto p1, p2;
    int tam;


    FILE* fpCopia;

    if ((fpCopia= fopen("porPrecio.dat", "w+b")) == NULL) {
        printf("Error al crear el archivo porPrecio.dat\n");
        return;
    }

    rewind(fp);
    //////////////////copiando
    while (fread(&p1, sizeof(Producto), 1, fp) == 1) {
        fwrite(&p1, sizeof(Producto), 1, fpCopia);
    }

    // veo el tamaño del archivo

    fseek(fp, 0, SEEK_END); // Posicionamos el puntero al final del archivo para obtener su tamaño total en bytes
    tam = ftell(fp) / sizeof(Producto); // ftell devuelve la posicion actual del puntero del archivo en bytes, entonces al dividirlo por el tamaño de un producto (58 bytes) obtenemos la cantidad total de productos en el archivo, es decir, el número de registros que contiene el archivo binario. Esto es necesario para saber cuántos productos hay que ordenar en el algoritmo de burbujeo.

    // Algoritmo de Burbujeo directamente sobre el archivo porPrecio.dat
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            fseek(fpCopia, j * sizeof(Producto), SEEK_SET); // Posicionamos el puntero al inicio del registro J
            fread(&p1, sizeof(Producto), 1, fpCopia);
            fread(&p2, sizeof(Producto), 1, fpCopia);
            if (p1.precio > p2.precio) {
                // Si el primero es mayor, intercambiamos en el disco
                // Volvemos a la posicion del registro J
                fseek(fpCopia, j * sizeof(Producto), SEEK_SET); // Posicionamos el puntero al inicio del registro J para escribir los productos en el orden correcto después de compararlos. Esto es necesario porque después de leer los dos productos (p1 y p2), el puntero del archivo se ha movido hacia adelante, por lo que necesitamos volver a la posición del registro J para escribir los productos en el orden correcto (p2 primero y luego p1) si se determina que p1 es mayor que p2.
                // Escribimos p2 donde estaba p1 y p1 donde estaba p2
                fwrite(&p2, sizeof(Producto), 1, fpCopia);
                fwrite(&p1, sizeof(Producto), 1, fpCopia);
            }
        }
    }

    //Mostrar el archivo ya ordenado
    printf("\n--- ARCHIVO 'porPrecio.dat' ORDENADO EN DISCO ---\n");
    mostrarArchivo(fpCopia); // Reutilizamos la funcion de mostrar

    fclose(fpCopia);
}





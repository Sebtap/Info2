#include <stdio.h> 
#include <errno.h> //errno.h es una biblioteca de C que define macros para reportar errores. Proporciona una variable global llamada 'errno' que se establece con un código de error específico cuando ocurre un error en una función de la biblioteca estándar. También incluye funciones como perror() para imprimir mensajes de error basados en el valor de 'errno'.

//Hacer un programa que cuente la cantidad de bytes 
//que contiene un archivo de texto. 

/*Un stream (flujo) tuberia de datos que conecta tu programa con el mundo externo. Es una abstracción que representa una secuencia de datos que se pueden leer o escribir. En C, los streams se manejan a través de la biblioteca estándar de entrada/salida (stdio.h) y se representan mediante la estructura FILE.
Las estandar son stdin, stdout y stderr que representan respectivamente la entrada estándar, la salida estándar y la salida de error.
Son macros que representan flujos de datos predefinidos en FILE*, que es una estructura que contiene información sobre el flujo, como su estado, posición actual, etc.
Que ese FILE? Es la interfaz que permite redireccinar flujos de datos. Es un struct que representa flujo de datos, trabajos a partir de funciones como fgetc,fgets, fprintf,fread,etc. para acceder a los datos. */

/*Para vaciar el flujo stdin el buffer de salida, se usa fflush(stdin) 
No util en linux, GCC o compiladores estandar
Otro metodo es usar fgets() o while((variable=getchar())!='\n')*/

int main() {
    /*Definimos un puntero que apunta a una estructura FILE
    FILE es el nombre de la estructura definida en stdio.h 
    *fp Es un puntero que apunta a una direccion de memoria RAM que ha sido organizada para alojar los datos del archivo con molde de la estructura FILE*/
    FILE *fp;
    long int contadorBytes = 0;
    int caracter; // Cambiado a int para detectar bien el EOF

    // Abrimos en "rb" (read binary) para contar bytes reales
    fp = fopen("archivo.txt", "rb");
    //fopen es una función que se utiliza para abrir un archivo en C. Toma dos argumentos: el nombre del archivo y el modo de apertura (en este caso, "rb" para lectura en modo binario). Devuelve un puntero a FILE que se utiliza para manejar el archivo. Si no se puede abrir el archivo, devuelve NULL.
    //A fp se le asigna la dirección de memoria del archivo abierto, apunta a una estructura objeto FILE creado del archivo, y se puede usar para realizar operaciones de lectura o escritura en ese archivo. Es importante cerrar el archivo con fclose(fp) después de terminar de usarlo para liberar los recursos asociados.
    /*Algunas operaciones son write 'w', read 'r' , read binary 'rb' , 
    append 'a' , read/update 'r+', write/update 'w+', append/update 'a+'*/
    
    // Verificamos si el archivo se abrió correctamente
    if (fp == NULL) {
        perror("No se pudo abrir el archivo. Asegurate de que 'archivo.txt' exista.\n");
        // Muestra un mensaje de error más detallado que printf, basado en el valor actual de errno, que se establece automáticamente cuando fopen falla. Esto proporciona información específica sobre por qué no se pudo abrir el archivo (por ejemplo, si el archivo no existe, si hay un problema de permisos, etc.).
        return 1;
    }

    /* EXPLICACIÓN DEL BUCLE:
       1. fgetc(fp): Lee el SIGUIENTE byte (caracter) del archivo.
       2. (caracter = fgetc...): Guarda ese byte en la variable 'caracter'.
       3. != EOF: Compara si lo que leyó es el "Fin de Archivo".
    */
    // Leemos con fgetc(lee un unico caracter) byte por byte hasta el final
    // EOF (End Of File) es una constante que indica el final de un archivo. Cuando fgetc() alcanza el final del archivo, devuelve EOF, que generalmente tiene un valor de -1. Por eso es importante que 'caracter' sea de tipo int, para poder almacenar ese valor especial.
    //Si el caracter leido no es EOF, se suma 1 al contador de bytes. El bucle continúa hasta que se alcance el final del archivo, momento en el cual fgetc() devolverá EOF y el bucle terminará. 
    //Lo q devuelve el caracter es el valor ASCII del caracter leido, por eso se puede comparar con EOF, que es un valor especial que indica el fin del archivo.
    while ((caracter = fgetc(fp)) != EOF) {
        // Si no es el final, sumamos 1 al contador
        contadorBytes++;
    }

    fclose(fp); // Cierra el archivo para liberar recursos
    printf("El archivo contiene %ld bytes.\n", contadorBytes);


    /*FILE *fp=fopen("archivo.txt", "w")
        if(fp==NULL){
            printf("No se pudo abrir el archivo. Asegurate de que 'archivo.txt' exista.\n");
            return 1;
        }

        //Escribir en el archivo
        char nombre[3];
        int edad[3];
        for(int i=0; i<3; i++){
            printf("Ingrese un nombre: ");
            scanf("%s", nombre);
            printf("Ingrese la edad: ");
            scanf("%d", &edad[i]);
            //fprintf es igual a printf pero en lugar de imprimir en la consola, escribe en un archivo. El primer argumento es el puntero al archivo (fp), el segundo es el formato de la cadena (similar a printf), y los siguientes son las variables que se van a escribir en el archivo según el formato especificado.
            fprintf(fp, "Nombre: %s, Edad: %d\n", nombre, edad[i]); // Escribe el nombre y la edad en el archivo seguido de un salto de línea. fp al inicio pq es el puntero al archivo, "%s\n" es el formato para escribir una cadena seguida de un salto de línea, y nombre es la variable que contiene el nombre ingresado por el usuario.
        }
    */

    return 0;
}
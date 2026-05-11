#include <stdio.h>

/*Realizar un programa que muestre la cantidad de argumentos 
del main que recibe y los enumere.  */

/*argc es el número de argumentos que se pasan al programa, 
incluyendo el nombre del programa en sí.
argv es un array de cadenas de caracteres (strings) que contiene 
los argumentos pasados al programa y cada elemento es un string
es decir, una secuencia de caracteres terminada en '0'*/

/*Lo que se estudia aca es el paso de argumentos a la funcion main traves del so,
a traves de variables de entorno definidas del sistema operativo,
datos de red,Datos de archivos, etc.
 */

int main(int argc, char *argv[]) {

    
    printf("Cantidad de argumentos: %d\n",argc);

    for(int i=0;i<argc;i++){
        printf("Argumento %d: %s\n",i,argv[i]);
    }

    return 0; //Indica que el programa terminó correctamente
}

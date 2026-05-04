#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Realizar un programa que reciba un único argumento desde 
la línea de comandos. Si el argumento es un número entero 
válido y positivo, imprimirlo por stdout. Si el argumento 
no es válido o es negativo, imprimir un mensaje de error 
por stderr. Redirigir el resultado a desde el Shell a un 
archivo “resultado.txt” */

int main(int argc, char *argv[]) {

    //Convencion --help o -h para mostrar ayuda
    
    if(argc ==2 && ((strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h")==0))){
        fprintf(stdout, "Uso: %s <numero_positivo>\n", argv[0]);
        fprintf(stdout, "Ejemplo: %s 42\n", argv[0]);
        return 0;
    }

    //Validacion de cantidad argumentos: argc debe ser 2 (el nombre del programa + el argumento)
    if (argc != 2) {
        //stderr es el flujo de error estándar, se utiliza para imprimir mensajes de error
        fprintf(stderr, "Error: Se requiere un unico argumento.\n");
        return 1; //Indica que el programa terminó con un error
    }

    char *endptr; // Puntero que apunta a una direccion desconocida, se usará para validar la conversión de string a número
    /* argv[1] es el texto que quieres convertir a número.
    &endptr Le estamos dando la direccion de la variable para que almacene el valor donde terminó la conversión, si *endptr es '\0' no se trabo, caso contrario, se trabo en algun caracter no numérico.
    10 es la base (decimal)*/
    long num = strtol(argv[1], &endptr, 10); //En long num queda guardado el numero convertido
    /* strtol y strfol nos permiten convertir strings a números con validación de errores */
    

    // 3. Validación robusta:
    // - endptr == argv[1]: Significa que no leyó ni un solo número (ej: "abc")
    // - *endptr != '\0': Significa que leyó números pero terminó en letras (ej: "123a")
    // - num <= 0: Lo que pide la consigna (positivo)
    if (*endptr != '\0' || num <= 0) {
        fprintf(stderr, "Error: El argumento debe ser un numero entero valido y positivo.\n");
        return 1;
    }
    //stdout es el flujo de salida estándar, se utiliza para imprimir resultados normales
    fprintf(stdout, "Numero ingresado: %ld\n", num);
    return 0; //Indica que el programa terminó correctamente
}
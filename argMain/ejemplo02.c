#include <stdio.h>
#include <stdlib.h>

/*Realizar un programa que reciba un único argumento desde 
la línea de comandos. Si el argumento es un número entero 
válido y positivo, imprimirlo por stdout. Si el argumento 
no es válido o es negativo, imprimir un mensaje de error 
por stderr. Redirigir el resultado a desde el Shell a un 
archivo “resultado.txt” */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        //stderr es el flujo de error estándar, se utiliza para imprimir mensajes de error
        fprintf(stderr, "Error: Se requiere un unico argumento.\n");
        return 1;
    }

    char *endptr;
    long num = strtol(argv[1], &endptr, 10);
    
    // 3. Validación robusta:
    // - endptr == argv[1]: Significa que no leyó ni un solo número (ej: "abc")
    // - *endptr != '\0': Significa que leyó números pero terminó en letras (ej: "123a")
    // - num <= 0: Lo que pide la consigna (positivo)
    if (*endptr != '\0' || num <= 0) {
        fprintf(stderr, "Error: El argumento debe ser un numero entero válido y positivo.\n");
        return 1;
    }
    //stdout es el flujo de salida estándar, se utiliza para imprimir resultados normales
    fprintf(stdout, "Numero ingresado: %ld\n", num);
    return 0;
}
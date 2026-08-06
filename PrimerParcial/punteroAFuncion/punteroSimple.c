/*
Enunciado:
Imagina que quieres crear un programa que pueda realizar dos operaciones 
matemáticas simples con dos números: Sumar o Restar.
En lugar de llamar a la función sumar() o restar() directamente por su nombre, 
vamos a crear una variable tipo "puntero a función" llamada operacion y le 
asignaremos la función que queremos ejecutar según lo que elija el usuario.
*/

#include <stdio.h>

// 1. DEFINICIÓN DE LAS FUNCIONES INDIVIDUALES
// OJO: Ambas funciones tienen la misma "firma": reciben 2 int y devuelven 1 int.
int sumar(int a, int b) {
    return a + b;
}

int restar(int a, int b) {
    return a - b;
}

int main() {
    int n1 = 10, n2 = 4;
    int opcion;

    /*
     ======================================================================
     2. DECLARACIÓN DEL PUNTERO A FUNCIÓN
     ======================================================================
     Sintaxis: tipo_retorno (*nombre_puntero)(tipos_de_parametros);
     
     Aquí creamos una variable llamada 'operacion' capaz de guardar
     la dirección de cualquier función que devuelva un 'int' y reciba dos 'int'.
    */
    int (*operacion)(int, int) = NULL;

    printf("Numeros: %d y %d\n", n1, n2);
    printf("Elije una opcion (1: Sumar, 2: Restar): ");
    scanf("%d", &opcion);

    /*
     ======================================================================
     3. ASIGNACIÓN DINÁMICA
     ======================================================================
     Guardamos en el puntero la función seleccionada.
     Fíjate que se pone el NOMBRE de la función sin paréntesis ni parámetros.
    */
    if (opcion == 1) {
        operacion = sumar;  // 'operacion' ahora apunta a la función sumar()
    } else if (opcion == 2) {
        operacion = restar; // 'operacion' ahora apunta a la función restar()
    } else {
        printf("Opcion invalida.\n");
        return 1;
    }

    /*
     ======================================================================
     4. EJECUCIÓN O INVOCACIÓN
     ======================================================================
     Llamamos a la función usando la variable 'operacion' como si fuera
     una función normal.
    */
    int resultado = operacion(n1, n2);

    printf("El resultado de la operacion elegida es: %d\n", resultado);

    return 0;
}
/*
Funcion recursiva que va incrementando el valor de i hasta llegar a 6
*/

#include <stdio.h>

// Prototipo de la función recursiva
int fr(int);

int main(void)
{
    int i;

    // Llamamos a la función comenzando con i = 3
    i = fr(3);

    // Mostramos el valor que finalmente devolvió la función
    printf("\ni=%d\n", i);

    return 0;
}


// Función recursiva
int fr(int i)
{
    // Mientras i sea distinto de 6,
    // seguimos haciendo llamadas recursivas
    if (i != 6)
    {
        // Mostramos el valor actual antes
        // de hacer la siguiente llamada
        printf("\ni=%d", i);

        // La función se vuelve a llamar a sí misma
        // incrementando i en 1
        i = fr(i + 1);
    }

    // Cuando i llega a 6, ya no entra al if.
    // Devuelve 6.
    return i;
}
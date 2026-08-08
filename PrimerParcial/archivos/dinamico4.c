/*
Pedir ingresar por teclado cuantas letras tiene una palabra. Seguidamente crear
un vector en forma dinamica que reserve el espacio minimo para ingresar dicha 
palabra.
Cargar por teclado la palabra, mostrarla y finalmente liberar el espacio requerido.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int cantLetras;

    // 1. Pedir la cantidad de letras
    printf("Ingrese cuantas letras tiene la palabra: ");
    if (scanf("%d", &cantLetras) != 1 || cantLetras <= 0) {
        fprintf(stderr, "Error: Ingrese un numero valido mayor a 0.\n");
        return 1;
    }

    // 2. Reserva minima: cantLetras + 1 (EL +1 ES CLAVE PARA EL '\0' DE FIN DE CADENA)
    char *palabra = (char *) malloc((cantLetras + 1) * sizeof(char));

    // Validacion de memoria
    if (palabra == NULL) {
        fprintf(stderr, "Error al reservar memoria dinamica.\n");
        return 1;
    }

    // 3. Cargar la palabra por teclado
    printf("Ingrese la palabra: ");
    scanf("%s", palabra);

    // 4. Mostrar la palabra
    printf("\nPalabra ingresada: %s\n", palabra);

    // 5. Liberar el espacio reservado
    free(palabra);

    return 0;
}
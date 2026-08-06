/*
Enunciado:
Escribe una función recursiva llamada sumarVector(int vec[], int tam) 
que reciba un arreglo de números enteros y su tamaño tam, y devuelva 
la suma de todos sus elementos.
*/

/*
Caso base y caso recursivo:
- Caso base: Si tam es igual a 0, la suma es 0.
- Caso recursivo: Para cualquier tam > 0, la suma es el último elemento 
  del vector más la suma de los elementos anteriores.
*/

#include <stdio.h>

// Función recursiva para sumar los elementos de un vector
int sumarVector(int vec[], int tam) {
    // Caso base: Si tam es 0, la suma es 0
    if (tam == 0) {
        return 0;
    }

    // Caso recursivo: La suma es el último elemento más la suma de los elementos anteriores
    return vec[tam - 1] + sumarVector(vec, tam - 1);
}

int main(){
    int vec[5] = {1, 2, 3, 4, 5};
    int tam = sizeof(vec) / sizeof(vec[0]);

    // Llamada a la función recursiva
    int resultado = sumarVector(vec, tam);

    printf("La suma de los elementos del vector es: %d\n", resultado);

    return 0;

}
/*
### Ejercicio 3: Algoritmos Recursivos y Análisis de Complejidad
Dada una estructura de datos lineal (arreglo):
1. Implementar un algoritmo de ordenamiento recursivo (**QuickSort**).
2. Implementar una función recursiva para la búsqueda de un elemento (**Búsqueda Binaria**).
3. Analizar la complejidad temporal en el peor y mejor caso ($O(n \log n)$, $O(n^2)$, etc.).
*/

/*
Una funcion es recursiva si se llama a si misma, ya sea de manera directa o indirecta.
En este ejercicio, implementaremos dos algoritmos recursivos: QuickSort y Búsqueda
La idea es achicar el tamaño del problema en cada llamada recursiva, hasta llegar a un caso base que sea trivial de resolver.
*/

#include <stdio.h>



//Usamos quicksort
int main(){

    float temperaturas[] = {23.0, 80.0, 12.0, 45.0, 30.0};
    int cantidad = 5;

    // Le pasamos: el vector, la primera posición (0) y la última (cantidad - 1)
    quickSort(temperaturas, 0, cantidad - 1);

    // ¡Listo! El vector 'temperaturas' ahora está completamente ordenado.
    return 0;

}

// Esta función acomoda los números y nos devuelve la posición final del pivote
//Recibe como argumentos: el arreglo, el índice más bajo y el índice más alto del sub-arreglo que queremos ordenar
int particion(float temperaturas[], int bajo, int alto) {
    float pivote = temperaturas[alto]; // 1. Tomamos el último número como pivote
    int i = bajo - 1;                  // Marca el límite de los números menores

    // Recorremos el sub-arreglo comparando cada número contra el pivote
    for (int j = bajo; j < alto; j++) {
        if (temperaturas[j] <= pivote) {
            i++;
            // Intercambiamos de lugar para mandar el número menor a la izquierda
            float aux = temperaturas[i];
            temperaturas[i] = temperaturas[j];
            temperaturas[j] = aux;
        }
    }

    // Colocamos el pivote en el centro (entre los menores y los mayores)
    float aux = temperaturas[i + 1];
    temperaturas[i + 1] = temperaturas[alto];
    temperaturas[alto] = aux;

    return (i + 1); // Devolvemos el índice donde quedó ubicado el pivote
}

void quickSort(float temperaturas[], int bajo, int alto) {
    // CASO BASE: Si el sub-arreglo tiene 1 o 0 elementos (bajo >= alto), no hace nada.
    if (bajo < alto) {
        
        // 1. Acomodamos el pivote y guardamos su posición final
        int pos_pivote = particion(temperaturas, bajo, alto);

        // 2. CASO RECURSIVO: Acomodamos la mitad izquierda y la mitad derecha
        quickSort(temperaturas, bajo, pos_pivote - 1); // Lado izquierdo (menores)
        quickSort(temperaturas, pos_pivote + 1, alto); // Lado derecho (mayores)
    }
}
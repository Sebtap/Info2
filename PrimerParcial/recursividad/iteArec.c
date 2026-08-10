#include <stdio.h>

/* ====================================================
 * CÓDIGO ITERATIVO ORIGINAL (COMENTADO)
 * ====================================================
double loge() {
    double enl, delta, fact;
    int n;
    enl = fact = delta = 1.0;
    n = 1;
    do {
        enl += delta;
        n++;
        fact *= n;
        delta = 1.0 / fact;
    } while (enl != enl + delta);
    return enl;
}
*/

// ====================================================
// CÓDIGO RECURSIVO CAMBIADO Y CON COMENTARIOS
// ====================================================

// Función auxiliar recursiva: pasa las variables de estado en cada llamada reemplazando el bucle
double loge_recursivo_aux(int n, double fact, double delta, double enl) {
    // 1. Acumulación: suma el término actual (delta) al total de 'e' (enl)
    enl += delta;

    // 2. Actualización de variables para el siguiente término (n!)
    n++;
    fact *= n;          // Calcula el nuevo factorial (n!)
    delta = 1.0 / fact; // Calcula el siguiente término (1 / n!)

    // 3. Caso base: se detiene cuando 'delta' es tan pequeño que ya no altera la precisión de 'enl'
    if (enl == enl + delta) {
        return enl;
    }

    // 4. Paso recursivo: llamada recursiva enviando el nuevo estado de las variables
    return loge_recursivo_aux(n, fact, delta, enl);
}

// Función principal que invoca la recursión con los valores iniciales
double loge() {
    // Inicialización idéntica al código original (n=1, fact=1.0, delta=1.0, enl=1.0)
    return loge_recursivo_aux(1, 1.0, 1.0, 1.0);
}

int main() {
    // Imprime la aproximación del número e calculada recursivamente
    printf("Aproximacion del numero e (recursivo): %.15f\n", loge());
    return 0;
}
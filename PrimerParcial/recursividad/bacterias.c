/*
Un grupo de biólogos está investigando una especie de bacteria que se duplica 
a un ritmo constante. El comportamiento de la población sigue una regla 
matemática estricta:
•	Minuto 0: Hay exactamente 1 bacteria en el laboratorio.
•	Minuto \(N\): La cantidad de bacterias es exactamente el doble de la 
cantidad que había en el minuto anterior (\(N-1\)).
Realizar un programa en lenguaje C que contenga una función recursiva 
para calcular cuántas bacterias habrá en el laboratorio al cabo de un
 minuto \(N\) ingresado por el usuario.
Casos Base y Recursivo (Mapeo mental):
•	Caso Base: Si el minuto es 0, la población es 1.
•	Caso Recursivo: Para cualquier minuto \(N > 0\), la población 
es \(2 \times \text{población}(N-1)\).

*/

/*
caso base y caso recursivo:
- Caso base: Si el minuto es 0, la población es 1.
- Caso recursivo: Para cualquier minuto N > 0, la población es 2 * población(N-1).
*/

#include <stdio.h>

// Función recursiva para calcular la cantidad de bacterias al cabo de N minutos
long long calcular_bacterias(int n) {
    // Caso base: Minuto 0 -> Hay 1 bacteria
    if (n == 0) {
        return 1;
    }
    
    // Caso recursivo: 2 * bacterias del minuto anterior (N - 1)
    return 2 * calcular_bacterias(n - 1);
}

int main() {
    int minuto;

    printf("=== SIMULADOR DE CRECIMIENTO BACTERIANO ===\n");
    printf("Ingrese el minuto N a consultar: ");

    // Validación de entrada de datos
    if (scanf("%d", &minuto) != 1 || minuto < 0) {
        printf("[ERROR] Debe ingresar un numero entero mayor o igual a 0.\n");
        return 1;
    }

    // Invocación a la función recursiva
    // Usamos 'long long' porque el crecimiento exponencial hace crecer rápido el número
    long long total_bacterias = calcular_bacterias(minuto);

    printf("\nAl cabo del minuto %d habrá exactamente %lld bacterias en el laboratorio.\n", 
           minuto, total_bacterias);

    return 0;
}
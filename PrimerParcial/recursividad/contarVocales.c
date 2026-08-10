#include <stdio.h>
#include <ctype.h>

int vocales(char *cd) {
    // Caso base: al alcanzar el caracter nulo '\0', termina la cadena
    if (*cd == '\0') {
        return 0;
    }

    // Convertimos el caracter actual a minúscula para simplificar la validación
    char c = tolower(*cd);

    // Evaluamos si el caracter actual es una vocal (1) o no (0)
    int es_vocal = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? 1 : 0;

    // Paso recursivo: sumamos la evaluación actual con el conteo del resto de la cadena (cd + 1)
    return es_vocal + vocales(cd + 1);
}

int main() {
    char texto[] = "Estructura de Datos";

    printf("Texto: \"%s\"\n", texto);
    printf("Cantidad de vocales: %d\n", vocales(texto));

    return 0;
}
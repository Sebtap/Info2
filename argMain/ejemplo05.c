#include <stdio.h>
#include <stdlib.h> // Necesaria para getenv
//Ejercicio 5: Variable de entorno MIVAR

int main() {
    // Buscamos en el sistema el valor asociado a la clave "MIVAR"
    char *valor = getenv("MIVAR");

    // getenv devuelve NULL si la variable no existe en el entorno actual
    if (valor == NULL) {
        fprintf(stderr, "La variable MIVAR no esta definida en el sistema.\n");
        fprintf(stderr,"Tip: Usa 'export MIVAR=algo' en Bash o 'set MIVAR=algo' en CMD.\n");
    } else {
        // Si existe, mostramos su contenido como string
        fprintf(stdout, "El contenido de MIVAR es: %s\n", valor);
    }

    return 0;
}
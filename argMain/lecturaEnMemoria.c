#include <stdio.h>
#include <string.h>

// int argc: número de argumentos (incluyendo el nombre del programa)
// char *argv[]: arreglo de punteros a cadenas de caracteres (argumentos)
int main(int argc, char *argv[]) {

    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printf("Uso: %s <text 1> <text 2> ... <text n>\n", argv[0]);
        return 0;
    }
    if (argc < 3) {
        printf("Error: se esperan minimo 2 argumentos.\n");
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        
        // 1. Buscamos la dirección del argumento i (Viaje 1)
        char *dir_del_string = *(argv + i); // Esto es equivalente a char *dir_del_string = argv[i];
        
        // 2. Leemos la primera letra en esa dirección (Viaje 2, posición base)
        char primer_letra = *dir_del_string; // Esto es equivalente a char primer_letra = argv[i][0];
        
        // 3. Leemos el segundo carácter (Viaje 2, pero sumándole 1 byte a la dirección)
        char segundo_caracter = *(dir_del_string + 1); // Esto es equivalente a char segundo_caracter = argv[i][1];
        //*(dir_del_string + 1): La CPU usa su circuito sumador (ALU) adentro del procesador y calcula: 0x7FFF0050 + 1 byte = 0x7FFF0051. Pone ese nuevo número en el bus de direcciones. La RAM busca en el casillero de al lado y le devuelve el '0'.
        
        printf("Arg %d -> Letra 1: %c, Letra 2: %c\n", i, primer_letra, segundo_caracter);
    }
    return 0;
}
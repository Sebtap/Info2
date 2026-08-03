#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: falta un número.\n");
        return 1;
    }

    char *fin;
    float valor = strtof(argv[1], &fin); //recibe la dirección del string que queremos convertir (argv[1]), la dirección del freno (fin) y la base decimal (10). strtof convierte el string a un float y guarda el resultado en valor. Si el string no es un número válido, fin apuntará al primer carácter no numérico.

    if (*fin != '\0') {
        printf("Error: '%s' no es un numero valido.\n", argv[1]);
        return 1;
    }else {
        printf("Valor convertido: %.2f\n", valor);
        return 0;
    }

    
    
}
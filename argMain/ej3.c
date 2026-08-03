#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <numero1> <numero2>\n", argv[0]);
        return 1;
    }

    int valor[argc - 1];// arreglo de enteros para guardar los valores convertidos de los argumentos
    //convierto los argumentos a enteros y los guardo en un arreglo de enteros
    for(int i =0 ; i < argc; i++){
        valor[i] = atoi(argv[i]);
        printf("Valor %d: %d\n", i, valor[i]);
    }
    
    

    printf("[atoi] Valor convertido: %d\n", valor[0] + valor[1]);
    return 0;
}
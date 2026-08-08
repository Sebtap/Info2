#include <stdio.h>

//ESTRUCTURA IMAGINARIA PARA BINARIO
typedef struct{
    int id;
    char nombre[50];
}USUARIO;


int main(){
    //Contar bytes de un archivo de texto, y cantidad de filas

    FILE *archText=fopen("archtext.txt","r");
    if(archText==NULL){
        fprintf(stderr,"No se pudo abrir el archtext.txt");
        return 1;
    }

    int c;
    int ultimo_c = 0;
    long cant_bytes = 0;
    int cant_filas = 0;

    while ((c = fgetc(archText)) != EOF) {
        cant_bytes++;
    
        if (c == '\n') {
            cant_filas++;
        }
    
        ultimo_c = c; // Guardamos el carácter actual
    }

    // VALIDACIÓN DEL CASO BORDES:
    // Si el archivo tenía contenido Y el último carácter no fue '\n', 
    // significa que la última línea no se contó dentro del while.
    if (cant_bytes > 0 && ultimo_c != '\n') {
        cant_filas++;
    }
    fclose(archText);

    printf("Resultados de archtext.txt:\n");
    printf("- Total de bytes: %ld\n",cant_bytes);
    printf("- Total de filas: %d\n",cant_filas);


    //Contar bytes de un archivo binario y cantidad de filas
    USUARIO usuario;

    FILE *archBinario=fopen("archBinario.dat","rb");
    if(archBinario==NULL){
        fprintf(stderr,"No se pudo abrir el archBinario.dat");
        return 1;
    }

    fseek(archBinario,0,SEEK_END);
    long tamanio_bytes=ftell(archBinario);
    int filas=tamanio_bytes/sizeof(usuario);
    rewind(archBinario);

    fclose(archBinario);

    printf("Resultados de archBinario.dat:\n");
    printf("- Total de bytes: %ld\n",tamanio_bytes);
    printf("- Total de filas: %d\n",filas);

}
/*
Se recolectaron datos de usuarios de una plataforma de streaming y se almacenaron en dos archivos:
usuarios.dat:
typedef struct {
    char nombre[30];
    int edad;
    char pais[20];
} Usuario;


actividades.dat:
typedef struct {
    char nombre[30];  // mismo nombre que en usuarios.dat
    int horas_vistas;
    int cantidad_dispositivos;
} Actividad;

Se pide:
	Leer ambos archivos y cargar la información en estructuras utilizando memoria dinámica. Validar que cada actividad tenga un usuario correspondiente.
	Filtrar usuarios destacados, es decir, los que cumplan TODAS estas condiciones:
	Edad mayor a 18 años.
	Más de 50 horas vistas.
	Uso de más de 2 dispositivos.
	Calcular un índice de participación con la siguiente fórmula:
indice de participación=(horas vistas x cantidad de dispositivos)/(edad del usuario)
	Ordenar a los usuarios destacados en forma decreciente según el índice de participación.
	Guardar los datos ordenados en un nuevo archivo binario llamado destacados.dat.
	Mostrar por pantalla los primeros 5 usuarios destacados (nombre, país, índice).

Requisitos:
	Usar malloc para crear estructuras dinámicamente.
	Separar el código en funciones:
	leerUsuarios()
	leerActividades()
	filtrarDestacados()
	ordenarDestacados()
	guardarArchivoDestacados()
	mostrarTop5()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[30];
    int edad;
    char pais[20];
} Usuario;

typedef struct {
    char nombre[30];  // mismo nombre que en usuarios.dat
    int horas_vistas;
    int cantidad_dispositivos;
} Actividad;


typedef struct {
    char nombre[30];
    char pais[20];
    float indice;
} Destacado;





// Prototipo: la funcion devuelve un puntero a Usuario (Usuario*)
Usuario* leerUsuario(int *cantU);
Actividad* leerActividades(int *cantA);
Destacado* filtrarDestacados(Usuario *usuarios,Actividad *actividades,int cantU,int cantA,int *cantD);
void ordenarDestacados(Destacado *destacados, int cantD);
void guardarArchivoDestacados(Destacado *destacados, int cantD);
void mostrarTop5(Destacado *destacados, int cantD);

int main(){
    int cantU=0;
    int cantA=0;
    int cantD=0;
    //Recibimos el puntero al inicio de la memoria reservada
    Usuario *usuarios=leerUsuario(&cantU);
    if(usuarios!=NULL){
        printf("Usuarios cargados correctamente en memoria.\n");
        free(usuarios);
    }

    Actividad *actividades=leerActividades(&cantA);
    if(actividades!=NULL){
        printf("Usuarios cargados correctamente en memoria.\n");
        free(actividades);
    }

    printf("Usuarios y actividades cargados correctamente\n");

    Destacado *destacados=filtrarDestacados(usuarios,actividades,cantU,cantA,&cantD);
    
    if(destacados!=NULL){
        printf("Usuarios cargados correctamente en memoria.\n");
        ordenarDestacados(destacados,cantD);
        guardarArchivoDestacados(destacados,cantD);
        mostrarTop5(destacados,cantD);
        free(destacados);
    }

    return 0;
}

Usuario* leerUsuario(int *cantU){   //Recibe la direccion de cantU
    FILE *archivo=fopen("usuarios.dat","rb");
    if(archivo==NULL){
        fprintf(stderr,"Error al abrir archivo");
        return NULL; 
    }
    //Calcular la cantidad de registros en el archivo
    fseek(archivo,0,SEEK_END);
    long bytes=ftell(archivo);
    int cantRegistro=bytes/sizeof(Usuario);
    rewind(archivo); //Vuelve al inicio del archivo

    //Escribimos en la memoria del main
    *cantU=cantRegistro;

    //Reserva de memoria
    Usuario *usuario=(Usuario*)malloc(cantRegistro*sizeof(Usuario));

    //Cargar cada registro dentro del bloque de memoria reservado
    for(int i=0;i<cantRegistro;i++){
        fread(&usuario[i],sizeof(Usuario),1,archivo);
    }
    fclose(archivo);
    //Retorno el puntero a la primera posicion del bloque
    return usuario;
}

Actividad* leerActividades(int *cantA) {
    FILE *archivo = fopen("actividades.dat", "rb");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir archivo\n");
        return NULL; 
    }

    // Calcular la cantidad de registros en el archivo
    fseek(archivo, 0, SEEK_END);
    long bytes = ftell(archivo);
    int cantRegistro = bytes / sizeof(Actividad);
    rewind(archivo); 

    //Escribimos en la memoria del main
    *cantA=cantRegistro;

    // Reserva de memoria
    Actividad *actividades = (Actividad*) malloc(cantRegistro * sizeof(Actividad));

    // Validacion de seguridad para malloc
    if (actividades == NULL) {
        fclose(archivo);
        return NULL;
    }

    // Cargar cada registro dentro del bloque de memoria reservado
    for (int i = 0; i < cantRegistro; i++) {
        fread(&actividades[i], sizeof(Actividad), 1, archivo); 
    }

    fclose(archivo);

    // Retorno el puntero a la primera posicion del bloque
    return actividades;
}

Destacado* filtrarDestacados(Usuario *usuarios,Actividad *actividades,int cantU,int cantA,int *cantD){

    int contador=0;
    // 1. Reservar memoria máxima posible (en el peor caso, todos son destacados)
    Destacado *destacados = (Destacado*) malloc(cantU * sizeof(Destacado));
    if (destacados == NULL) return NULL;

    // 2. Cruzar datos de ambos bloques de memoria
    for (int i = 0; i < cantA; i++) {
        for (int j = 0; j < cantU; j++) {

            // Validacion 1: Mismo usuario (coincidencia de nombre)
            if (strcmp(actividades[i].nombre, usuarios[j].nombre) == 0) {

                // Validacion 2: Edad > 18, Horas > 50, Dispositivos > 2
                if (usuarios[j].edad > 18 && 
                    actividades[i].horas_vistas > 50 && 
                    actividades[i].cantidad_dispositivos > 2) {

                    // Copiar datos
                    strcpy(destacados[contador].nombre, usuarios[j].nombre);
                    strcpy(destacados[contador].pais, usuarios[j].pais);

                    // Calcular formula del indice
                    destacados[contador].indice = (float)(actividades[i].horas_vistas * actividades[i].cantidad_dispositivos) / usuarios[j].edad;

                    contador++; // Guardamos uno mas
                }
            }
        }
    }
    *cantD=contador;
    return destacados;

}

void ordenarDestacados(Destacado *destacados, int cantD) {
    for (int i = 0; i < cantD - 1; i++) {
        for (int j = 0; j < cantD - i - 1; j++) {
            // Si el actual es menor que el siguiente, los intercambiamos (orden decreciente)
            if (destacados[j].indice < destacados[j + 1].indice) {
                Destacado aux = destacados[j];
                destacados[j] = destacados[j + 1];
                destacados[j + 1] = aux;
            }
        }
    }
}

void guardarArchivoDestacados(Destacado *destacados, int cantD) {
    FILE *archivo = fopen("destacados.dat", "wb");
    if (archivo == NULL) {
        fprintf(stderr, "Error al crear el archivo destacados.dat\n");
        return;
    }

    // Escribe todos los destacados de un solo golpe usando el puntero
    fwrite(destacados, sizeof(Destacado), cantD, archivo);

    fclose(archivo);
}

void mostrarTop5(Destacado *destacados, int cantD) {
    // Si hay menos de 5, el limite sera cantD
    int limite = (cantD < 5) ? cantD : 5;

    printf("\n=== TOP %d USUARIOS DESTACADOS ===\n", limite);
    for (int i = 0; i < limite; i++) {
        printf("%d) Nombre: %-15s | Pais: %-10s | Indice: %.2f\n", 
               i + 1, destacados[i].nombre, destacados[i].pais, destacados[i].indice);
    }
}
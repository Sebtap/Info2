/*
Realizar un programa que maneje un archivo de longitud desconocida, donde 
cada registro contiene el nombre de un alumno y cuatro notas. Hacerlo con un
menu que permita crear el archivo, calcular el promedio, mostrarlo, buscar un
registro determinado, modificar una nota, agregar registros y ordenar 
alfabeticamente. Realizar tambien el programa que genere el archivo y 
verificar que funcionen en conjunto
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char nombre[50];
    int nota1;
    int nota2;
    int nota3;
    int nota4;
    float promedio;
}ALUMNO;

void crearArchivo();
void agregarRegistros();
void buscarRegistro();
void modificarNota();
void ordenarAlfabeticamente();
void mostrarPromedios();

int main(){


    char opcion;
    //Creo el menu

    do{
        printf("=========MENU========\n");
        printf(".a Crear el archivo\n");
        printf(".b Calcular promedio\n");
        printf(".c Mostrar promedios\n");
        printf(".d Buscar un registro determinado\n");
        printf(".e Modificar una nota\n");
        printf(".f Agregar registros\n");
        printf(".g Ordenar alfabeticamente\n");
        printf(".z Salir del programa\n");
        printf("Ingrese la opcion: ");
        scanf("%c",&opcion);
        opcion=tolower(opcion);
        switch(opcion){
            case 'a':crearArchivo();
                break;
            case 'b':calcularPromedio();
                break;
            case 'c':mostrarPromedios();
                break;
            case 'd':buscarRegistro();
                break;
            case 'e':modificarNota();
                break;
            case 'f':agregarRegistros();
                break;
            case 'g':ordenarAlfabeticamente();
                break;
            case 'z': printf("\nSaliendo del programa..\n");
                break;
            default:
                printf("\nIngrese una opcion que no existe, intente nuevamente..\n");
                break;
        }
        getchar(); //Pulsar un enter para continuar
    }while(opcion!='z');

}

void crearArchivo(){

    //Creamos el archivo
    FILE *archivo=fopen("alumnos.dat","wb");

    if(archivo == NULL){
        fprintf(stderr,"Error al crear el archivo.\n");
        return;
    }
    fclose(archivo);
    printf("Archivo creado correctamente.\n");
}

void agregarRegistros()
{
    ALUMNO alumno;
    char continuar;

    // Abrimos en modo ab para Agregar datos al final.
    FILE *archivo = fopen("alumnos.dat", "ab");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    do {
        printf("\nIngrese nombre: ");
        scanf(" %s", alumno.nombre);

        printf("Ingrese nota 1: ");
        scanf("%d", &alumno.nota1);

        printf("Ingrese nota 2: ");
        scanf("%d", &alumno.nota2);

        printf("Ingrese nota 3: ");
        scanf("%d", &alumno.nota3);

        printf("Ingrese nota 4: ");
        scanf("%d", &alumno.nota4);

        fwrite(&alumno, sizeof(ALUMNO), 1, archivo);

        printf("\n¿Desea agregar otro alumno? (s/n): ");
        scanf(" %c", &continuar);
        continuar=tolower(continuar);
    } while (continuar == 's');

    fclose(archivo);
}

void buscarRegistro()
{
    char continuar;
    char alumnoBuscado[50];
    ALUMNO alumno;
    FILE *archivo = fopen("alumnos.dat", "rb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    do {
        int encontrado = 0;

        printf("Ingrese nombre del alumno a buscar: ");
        scanf(" %s", alumnoBuscado);

        rewind(archivo);

        while (fread(&alumno, sizeof(ALUMNO), 1, archivo) == 1) {

            if (strcmp(alumno.nombre, alumnoBuscado) == 0) {

                printf("El alumno fue encontrado.\n");
                printf("El alumno %s tiene notas: %d, %d, %d, %d\n",
                       alumno.nombre,
                       alumno.nota1,
                       alumno.nota2,
                       alumno.nota3,
                       alumno.nota4);

                encontrado = 1;
            }
        }

        if (!encontrado) {
            printf("El alumno no fue encontrado.\n");
        }

        printf("\n¿Desea buscar otro alumno? (s/n): ");
        scanf(" %c", &continuar);
        continuar = tolower(continuar);

    } while (continuar == 's');

    fclose(archivo);
}

void modificarNota()
{
    FILE *archivo;
    ALUMNO alumno;
    char nombreBuscado[50];
    int opcion;
    int nuevaNota;
    int encontrado = 0;

    archivo = fopen("alumnos.dat", "rb+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Ingrese el nombre del alumno: ");
    scanf(" %s", nombreBuscado);

    while (fread(&alumno, sizeof(ALUMNO), 1, archivo) == 1) {

        if (strcmp(alumno.nombre, nombreBuscado) == 0) {

            encontrado = 1;

            printf("\nAlumno encontrado: %s\n", alumno.nombre);
            printf("1. Nota 1: %d\n", alumno.nota1);
            printf("2. Nota 2: %d\n", alumno.nota2);
            printf("3. Nota 3: %d\n", alumno.nota3);
            printf("4. Nota 4: %d\n", alumno.nota4);

            printf("\n¿Qué nota desea modificar? ");
            scanf("%d", &opcion);

            printf("Ingrese la nueva nota: ");
            scanf("%d", &nuevaNota);

            switch (opcion) {
                case 1:
                    alumno.nota1 = nuevaNota;
                    break;

                case 2:
                    alumno.nota2 = nuevaNota;
                    break;

                case 3:
                    alumno.nota3 = nuevaNota;
                    break;

                case 4:
                    alumno.nota4 = nuevaNota;
                    break;

                default:
                    printf("Opción inválida.\n");
                    fclose(archivo);
                    return;
            }

            //Tenemos que volver el cursor hacia atrás para colocarnos donde estaba Pedro.
            fseek(archivo, -sizeof(ALUMNO), SEEK_CUR);

            fwrite(&alumno, sizeof(ALUMNO), 1, archivo);

            printf("Nota modificada correctamente.\n");

            break;
        }
    }

    if (!encontrado) {
        printf("El alumno no fue encontrado.\n");
    }

    fclose(archivo);
}

void ordenarAlfabeticamente()
{
    FILE *archivo;
    ALUMNO *alumnos;
    ALUMNO aux;
    int i, j;
    int cantidad;

    archivo = fopen("alumnos.dat", "rb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Obtener cantidad de registros del archivo
    fseek(archivo, 0, SEEK_END);

    long cantBytes = ftell(archivo);

    cantidad = cantBytes / sizeof(ALUMNO);

    rewind(archivo);


    // Reservar memoria para todos los alumnos
    alumnos = malloc(cantidad * sizeof(ALUMNO));

    if (alumnos == NULL) {
        printf("Error al reservar memoria.\n");
        fclose(archivo);
        return;
    }


    // Cargar registros del archivo a memoria
    for (i = 0; i < cantidad; i++) {
        fread(&alumnos[i], sizeof(ALUMNO), 1, archivo);
    }


    fclose(archivo);


    // Ordenamiento burbuja por nombre
    for (i = 0; i < cantidad - 1; i++) {

        for (j = 0; j < cantidad - i - 1; j++) {

            if (strcmp(alumnos[j].nombre, alumnos[j + 1].nombre) > 0) {

                aux = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = aux;
            }
        }
    }


    // Abrir nuevamente para sobrescribir con el orden nuevo
    archivo = fopen("alumnos.dat", "wb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        free(alumnos);
        return;
    }


    // Guardar los registros ordenados
    for (i = 0; i < cantidad; i++) {
        fwrite(&alumnos[i], sizeof(ALUMNO), 1, archivo);
    }


    fclose(archivo);

    free(alumnos);

    printf("Archivo ordenado correctamente.\n");
}

void calcularPromedio()
{
    FILE *archivo;
    ALUMNO alumno;

    archivo = fopen("alumnos.dat", "rb+");

    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }


    while(fread(&alumno, sizeof(ALUMNO), 1, archivo) == 1)
    {
        // Calculo el promedio
        alumno.promedio = (alumno.nota1 +
                           alumno.nota2 +
                           alumno.nota3 +
                           alumno.nota4) / 4.0;


        // Vuelvo al inicio del registro leído
        fseek(archivo, -sizeof(ALUMNO), SEEK_CUR);


        // Sobrescribo el registro con el promedio actualizado
        fwrite(&alumno, sizeof(ALUMNO), 1, archivo);
    }


    fclose(archivo);

    printf("Promedios calculados correctamente.\n");
}

void mostrarPromedios()
{
    FILE *archivo;
    ALUMNO alumno;

    archivo = fopen("alumnos.dat", "rb");

    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }


    while(fread(&alumno,sizeof(ALUMNO),1,archivo)==1)
    {
        printf("Alumno: %s\n", alumno.nombre);
        printf("Promedio: %.2f\n\n", alumno.promedio);
    }


    fclose(archivo);
}
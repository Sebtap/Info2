/*Realizar un programa que maneje un archivo de longitud 
desconocida, donde cada registro contiene el nombre de un 
alumno y cuatro notas. Hacerlo con un menú que permita crear 
el archivo, calcular el promedio, mostrarlo, buscar un registro
determinado, modificar una nota, agregar registros y ordenar 
el archivo alfabéticamente. Realizar también el programa que 
genere el archivo y verificar que funcionen en conjunto. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos la estructura con tamaños fijos para que sea un archivo de registros constantes
typedef struct { //typedef para definir un nuevo tipo de dato llamado t_alumno
    char nombre[50];
    float notas[4];
    float promedio;
    int activo; // 1 para activo, 0 para borrado lógico (opcional pero profesional)
} t_alumno;

// Prototipos de funciones
void crearArchivo();
void agregarAlumno();
void mostrarAlumnos();
void buscarAlumno();
void modificarNota();
void ordenarAlfabeticamente();
float calcularPromedio(float notas[]);

int main() {
    int opcion;

    do {
        printf("\n--- MENU DE GESTION DE ALUMNOS ---\n");
        printf("1. Crear/Resetear archivo\n");
        printf("2. Agregar alumno\n");
        printf("3. Mostrar todos los alumnos\n");
        printf("4. Buscar alumno por nombre\n");
        printf("5. Modificar nota de un alumno\n");
        printf("6. Ordenar alfabeticamente\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer del teclado

        switch(opcion) {
            case 1: crearArchivo(); break;
            case 2: agregarAlumno(); break;
            case 3: mostrarAlumnos(); break;
            case 4: buscarAlumno(); break;
            case 5: modificarNota(); break;
            case 6: ordenarAlfabeticamente(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while(opcion != 0);

    return 0;
}

// 1. Crear el archivo (o borrar el anterior)
void crearArchivo() {
    FILE *fp = fopen("alumnos.dat", "wb"); // "wb" trunca el archivo a cero
    if (fp == NULL) {
        perror("Error al crear archivo");
        return;
    }
    printf("Archivo 'alumnos.dat' creado exitosamente.\n");
    fclose(fp);
}

// 2. Agregar registros al final
void agregarAlumno() {
    FILE *fp = fopen("alumnos.dat", "ab"); // "ab" para agregar al final
    if (fp == NULL) {
        perror("Error al abrir archivo");
        return;
    }

    t_alumno alu;
    printf("Nombre del alumno: ");
    fgets(alu.nombre, 50, stdin);
    alu.nombre[strcspn(alu.nombre, "\n")] = 0; // Quitar el salto de linea

    for(int i = 0; i < 4; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &alu.notas[i]);
    }
    alu.promedio = calcularPromedio(alu.notas);
    alu.activo = 1;

    fwrite(&alu, sizeof(t_alumno), 1, fp); // Escritura binaria directa
    printf("Alumno guardado.\n");
    fclose(fp);
}

// 3. Mostrar el listado completo (Lectura secuencial)
void mostrarAlumnos() {
    FILE *fp = fopen("alumnos.dat", "rb");
    if (fp == NULL) return;

    t_alumno alu;
    printf("\n%-20s | %-5s | %-5s | %-5s | %-5s | %-7s\n", "Nombre", "N1", "N2", "N3", "N4", "PROM");
    printf("----------------------------------------------------------------------\n");

    while(fread(&alu, sizeof(t_alumno), 1, fp)) {
        printf("%-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-7.2f\n", 
               alu.nombre, alu.notas[0], alu.notas[1], alu.notas[2], alu.notas[3], alu.promedio);
    }
    fclose(fp);
}

// 4. Buscar un registro (Comparacion de strings)
void buscarAlumno() {
    FILE *fp = fopen("alumnos.dat", "rb");
    char buscado[50];
    t_alumno alu;
    int encontrado = 0;

    printf("Ingrese el nombre a buscar: ");
    fgets(buscado, 50, stdin);
    buscado[strcspn(buscado, "\n")] = 0;

    while(fread(&alu, sizeof(t_alumno), 1, fp)) {
        if(strcasecmp(alu.nombre, buscado) == 0) {
            printf("Encontrado: %s - Promedio: %.2f\n", alu.nombre, alu.promedio);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) printf("Alumno no encontrado.\n");
    fclose(fp);
}

// 5. Modificar nota (Uso de fseek para posicionamiento)
void modificarNota() {
    FILE *fp = fopen("alumnos.dat", "rb+"); // Lectura/Escritura sin borrar
    if (fp == NULL) return;

    char nombre[50];
    t_alumno alu;
    int encontrado = 0;

    printf("Nombre del alumno a modificar: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    while(fread(&alu, sizeof(t_alumno), 1, fp)) {
        if(strcasecmp(alu.nombre, nombre) == 0) {
            printf("Modificando notas de %s...\n", alu.nombre);
            for(int i = 0; i < 4; i++) {
                printf("Nueva Nota %d: ", i + 1);
                scanf("%f", &alu.notas[i]);
            }
            alu.promedio = calcularPromedio(alu.notas);

            // Retrocedemos el cursor un registro para pisar el anterior
            fseek(fp, -sizeof(t_alumno), SEEK_CUR);
            fwrite(&alu, sizeof(t_alumno), 1, fp); // Sobreescritura
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) printf("No se encontro el alumno.\n");
    fclose(fp);
}

// 6. Ordenar alfabeticamente (Carga en RAM, ordena y guarda)
void ordenarAlfabeticamente() {
    FILE *fp = fopen("alumnos.dat", "rb");
    if (fp == NULL) return;

    // Calcular cantidad de registros usando ftell
    fseek(fp, 0, SEEK_END);
    long tam = ftell(fp);
    int cant = tam / sizeof(t_alumno);
    rewind(fp);

    // Buffer dinámico en RAM para ordenar
    t_alumno *vAlu = (t_alumno*) malloc(cant * sizeof(t_alumno));
    fread(vAlu, sizeof(t_alumno), cant, fp);
    fclose(fp);

    // Metodo Burbujeo simple
    t_alumno aux;
    for(int i = 0; i < cant - 1; i++) {
        for(int j = i + 1; j < cant; j++) {
            if(strcmp(vAlu[i].nombre, vAlu[j].nombre) > 0) {
                aux = vAlu[i];
                vAlu[i] = vAlu[j];
                vAlu[j] = aux;
            }
        }
    }

    // Guardar todo de nuevo (pisando el anterior)
    fp = fopen("alumnos.dat", "wb");
    fwrite(vAlu, sizeof(t_alumno), cant, fp);
    fclose(fp);
    free(vAlu);
    printf("Archivo ordenado correctamente.\n");
}

float calcularPromedio(float notas[]) {
    float suma = 0;
    for(int i = 0; i < 4; i++) suma += notas[i];
    return suma / 4;
}
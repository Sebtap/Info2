/*
Se recolectaron datos de usuarios de una plataforma de streaming y se 
almacenaron en dos archivos:
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
	Leer ambos archivos y cargar la información en estructuras utilizando 
    memoria dinámica//Es decir un vector dinamico de estructuras. Validar que cada actividad tenga un usuario correspondiente.
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


//El nombre relaciona ambos archivos, por lo que se puede usar como clave para relacionarlos
typedef struct {
    char nombre[30];
    int edad;
    char pais[20];
} Usuario;

typedef struct {
    char nombre[30];
    int horas_vistas;
    int cantidad_dispositivos;
} Actividad;

//Estructura para almacenar los usuarios destacados con su índice de participación
typedef struct {
    char nombre[30];
    char pais[20];
    float indice_participacion;
} UsuarioDestacado;

// Declaración de prototipos de funciones
int leerUsuarios(const char *nombre_archivo, Usuario **usuarios);
int leerActividades(const char *nombre_archivo, Actividad **actividades);
int filtrarDestacados(Usuario *usuarios, int cant_usuarios, Actividad *actividades, int cant_actividades, UsuarioDestacado **destacados);
void ordenarDestacados(UsuarioDestacado *destacados, int cant_destacados);
int guardarArchivoDestacados(const char *nombre_archivo, UsuarioDestacado *destacados, int cant_destacados);
void mostrarTop5(UsuarioDestacado *destacados, int cant_destacados);

int main() {
    Usuario *usuarios = NULL;
    Actividad *actividades = NULL;
    UsuarioDestacado *destacados = NULL;

    // 1. Cargar usuarios desde archivo binario
    int cant_usuarios = leerUsuarios("usuarios.dat", &usuarios);
    if (cant_usuarios <= 0) {
        fprintf(stderr, "Error o archivo vacio al leer usuarios.dat\n");
        return 1;
    }

    // 2. Cargar actividades desde archivo binario
    int cant_actividades = leerActividades("actividades.dat", &actividades);
    if (cant_actividades <= 0) {
        fprintf(stderr, "Error o archivo vacio al leer actividades.dat\n");
        free(usuarios);
        return 1;
    }

    // 3. Filtrar usuarios destacados y calcular el índice de participación
    int cant_destacados = filtrarDestacados(usuarios, cant_usuarios, actividades, cant_actividades, &destacados);

    // 4. Ordenar en forma decreciente por índice de participación
    if (cant_destacados > 0) {
        ordenarDestacados(destacados, cant_destacados);

        // 5. Guardar el resultado ordenado en un nuevo archivo binario
        if (!guardarArchivoDestacados("destacados.dat", destacados, cant_destacados)) {
            fprintf(stderr, "Error al guardar destacados.dat\n");
        }

        // 6. Mostrar el Top 5 en consola
        mostrarTop5(destacados, cant_destacados);
    } else {
        printf("No se encontraron usuarios que cumplan con las condiciones de destacados.\n");
    }

    // 7. Liberar toda la memoria dinámica reservada
    free(usuarios);
    free(actividades);
    free(destacados);

    return 0;
}

/**
 * Lee el archivo de usuarios y asigna memoria dinámica para el vector de estructuras.
 * Retorna la cantidad de usuarios leídos o -1 en caso de error.
 */
int leerUsuarios(const char *nombre_archivo, Usuario **usuarios) {
    FILE *arch = fopen(nombre_archivo, "rb");
    if (arch == NULL) return -1;

    // Calcular la cantidad de registros en el archivo
    fseek(arch, 0, SEEK_END);
    long tam = ftell(arch);
    int cant = tam / sizeof(Usuario);
    rewind(arch);

    if (cant <= 0) {
        fclose(arch);
        return 0;
    }

    // Reservar memoria dinámicamente usando el puntero doble
    *usuarios = (Usuario *)malloc(cant * sizeof(Usuario));
    if (*usuarios == NULL) {
        fclose(arch);
        return -1;
    }

    fread(*usuarios, sizeof(Usuario), cant, arch);
    fclose(arch);
    return cant;
}

/**
 * Lee el archivo de actividades y asigna memoria dinámica para el vector de estructuras.
 * Retorna la cantidad de actividades leídas o -1 en caso de error.
 */
int leerActividades(const char *nombre_archivo, Actividad **actividades) {
    FILE *arch = fopen(nombre_archivo, "rb");
    if (arch == NULL) return -1;

    fseek(arch, 0, SEEK_END);
    long tam = ftell(arch);
    int cant = tam / sizeof(Actividad);
    rewind(arch);

    if (cant <= 0) {
        fclose(arch);
        return 0;
    }

    *actividades = (Actividad *)malloc(cant * sizeof(Actividad));
    if (*actividades == NULL) {
        fclose(arch);
        return -1;
    }

    fread(*actividades, sizeof(Actividad), cant, arch);
    fclose(arch);
    return cant;
}

/**
 * Valida la existencia del usuario, aplica las condiciones de filtrado,
 * calcula el índice de participación y llena el vector de destacados.
 */
int filtrarDestacados(Usuario *usuarios, int cant_usuarios, Actividad *actividades, int cant_actividades, UsuarioDestacado **destacados) {
    int cant_destacados = 0;
    *destacados = NULL;

    for (int i = 0; i < cant_actividades; i++) {
        int encontrado = 0;

        // Validar que cada actividad tenga un usuario correspondiente
        for (int j = 0; j < cant_usuarios; j++) {
            if (strcmp(actividades[i].nombre, usuarios[j].nombre) == 0) {
                encontrado = 1; // Usuario correspondiente validado

                // Verificar condiciones para ser destacado
                if (usuarios[j].edad > 18 && 
                    actividades[i].horas_vistas > 50 && 
                    actividades[i].cantidad_dispositivos > 2) {

                    // Redimensionar el vector de destacados dinámicamente
                    UsuarioDestacado *temp = (UsuarioDestacado *)realloc(*destacados, (cant_destacados + 1) * sizeof(UsuarioDestacado));
                    if (temp == NULL) {
                        fprintf(stderr, "Error de memoria al redimensionar destacados.\n");
                        return cant_destacados;
                    }
                    *destacados = temp;

                    // Calcular índice de participación
                    float indice = (float)(actividades[i].horas_vistas * actividades[i].cantidad_dispositivos) / usuarios[j].edad;

                    // Asignar datos a la nueva estructura
                    strcpy((*destacados)[cant_destacados].nombre, usuarios[j].nombre);
                    strcpy((*destacados)[cant_destacados].pais, usuarios[j].pais);
                    (*destacados)[cant_destacados].indice_participacion = indice;

                    cant_destacados++;
                }
                break; // Detener búsqueda tras encontrar el usuario
            }
        }

        if (!encontrado) {
            printf("Advertencia: La actividad del usuario '%s' no tiene un usuario registrado.\n", actividades[i].nombre);
        }
    }

    return cant_destacados;
}

/**
 * Ordena el vector de usuarios destacados en forma decreciente mediante ordenamiento Burbuja.
 */
void ordenarDestacados(UsuarioDestacado *destacados, int cant_destacados) {
    for (int i = 0; i < cant_destacados - 1; i++) {
        for (int j = 0; j < cant_destacados - i - 1; j++) {
            if (destacados[j].indice_participacion < destacados[j + 1].indice_participacion) {
                UsuarioDestacado temp = destacados[j];
                destacados[j] = destacados[j + 1];
                destacados[j + 1] = temp;
            }
        }
    }
}

/**
 * Guarda los usuarios destacados ordenados en un archivo binario.
 * Retorna 1 si fue exitoso, 0 si ocurrió un error.
 */
int guardarArchivoDestacados(const char *nombre_archivo, UsuarioDestacado *destacados, int cant_destacados) {
    FILE *arch = fopen(nombre_archivo, "wb");
    if (arch == NULL) return 0;

    size_t escritos = fwrite(destacados, sizeof(UsuarioDestacado), cant_destacados, arch);
    fclose(arch);

    return escritos == (size_t)cant_destacados;
}

/**
 * Muestra en pantalla los datos de los primeros 5 usuarios destacados.
 */
void mostrarTop5(UsuarioDestacado *destacados, int cant_destacados) {
    printf("\n================ TOP 5 USUARIOS DESTACADOS ================\n");
    int limite = (cant_destacados < 5) ? cant_destacados : 5;

    for (int i = 0; i < limite; i++) {
        printf("%d. %-20s | Pais: %-12s | Indice: %.2f\n", 
               i + 1, 
               destacados[i].nombre, 
               destacados[i].pais, 
               destacados[i].indice_participacion);
    }
    printf("===========================================================\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructuras exactas del enunciado
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

int main() {
    // 1. Datos de prueba para usuarios.dat
    Usuario usuarios[10] = {
        {"Carlos Gomez", 25, "Argentina"},   // DESTACADO (Horas: 80, Disp: 3)
        {"Ana Lopez", 17, "Chile"},         // No (Menor de edad)
        {"Marcos Perez", 30, "Uruguay"},     // DESTACADO (Horas: 120, Disp: 4)
        {"Sofia Rodriguez", 40, "Argentina"},// No (Pocas horas: 30)
        {"Lucas Martinez", 22, "Colombia"},  // DESTACADO (Horas: 90, Disp: 3)
        {"Elena Gomez", 19, "Mexico"},       // No (Pocos dispositivos: 2)
        {"Diego Fernandez", 35, "Peru"},     // DESTACADO (Horas: 150, Disp: 5)
        {"Lucia Torres", 28, "Argentina"},   // DESTACADO (Horas: 60, Disp: 3)
        {"Mateo Silva", 16, "Brasil"},       // No (Menor de edad)
        {"Valeria Rios", 45, "Chile"}        // No (Pocas horas: 40)
    };

    // 2. Datos de prueba para actividades.dat (en correspondencia 1 a 1 por nombre)
    Actividad actividades[10] = {
        {"Carlos Gomez", 80, 3},     // Indice: (80*3)/25 = 9.60 -> DESTACADO
        {"Ana Lopez", 100, 4},       // Edad 17
        {"Marcos Perez", 120, 4},    // Indice: (120*4)/30 = 16.00 -> DESTACADO
        {"Sofia Rodriguez", 30, 4},  // Horas 30
        {"Lucas Martinez", 90, 3},   // Indice: (90*3)/22 = 12.27 -> DESTACADO
        {"Elena Gomez", 70, 2},      // Dispositivos 2
        {"Diego Fernandez", 150, 5}, // Indice: (150*5)/35 = 21.42 -> DESTACADO
        {"Lucia Torres", 60, 3},     // Indice: (60*3)/28 = 6.42 -> DESTACADO
        {"Mateo Silva", 95, 3},      // Edad 16
        {"Valeria Rios", 40, 3}      // Horas 40
    };

    // Creación de usuarios.dat
    FILE *f_usr = fopen("usuarios.dat", "wb");
    if (f_usr == NULL) {
        perror("Error al crear usuarios.dat");
        return 1;
    }
    fwrite(usuarios, sizeof(Usuario), 10, f_usr);
    fclose(f_usr);
    printf("[OK] Archivo 'usuarios.dat' generado con 10 registros.\n");

    // Creación de actividades.dat
    FILE *f_act = fopen("actividades.dat", "wb");
    if (f_act == NULL) {
        perror("Error al crear actividades.dat");
        return 1;
    }
    fwrite(actividades, sizeof(Actividad), 10, f_act);
    fclose(f_act);
    printf("[OK] Archivo 'actividades.dat' generado con 10 registros.\n");

    return 0;
}
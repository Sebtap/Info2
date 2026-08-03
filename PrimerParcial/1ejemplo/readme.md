# Repaso para el Primer Parcial - Informática II

Este repositorio contiene la resolución práctica de los 4 temas integradores para el primer parcial de la materia.

---

## 📋 Enunciados

### Ejercicio 1: Lectura de Archivo y Procesamiento Dinámico

Dado un archivo de texto (`temperaturas.txt`) que contiene lecturas de temperatura de un sensor (un dato tipo `float` por línea):

1. Abrir el archivo de manera segura verificando punteros nulos (`NULL`).
2. Implementar memoria dinámica (`malloc` y `realloc`) para almacenar las lecturas conforme se leen.
3. Procesar los datos en una sola pasada ("al vuelo") para determinar:
   - Valor máximo registrado .
   - Promedio general de las lecturas.
   - Cantidad de lecturas que superaron la temperatura crítica Tcrit = 75.0°C.
4. Liberar la memoria reservada y cerrar el archivo adecuadamente.

---

### Ejercicio 2: Máquina de Estados Finitos (FSM)

Implementar una máquina de estados para el control de acceso/proceso mediante una matriz o tabla de transiciones:

- Definir los estados (`INICIO`, `PROCESANDO`, `ALERTA`, `FIN`) mediante `enum`.
- Definir los eventos mediante `enum`.
- Controlar el flujo de ejecución procesando eventos secuenciales y ejecutando las acciones asociadas a cada transición.

---

### Ejercicio 3: Algoritmos Recursivos y Análisis de Complejidad

Dada una estructura de datos lineal (arreglo):

1. Implementar un algoritmo de ordenamiento recursivo (**QuickSort**).
2. Implementar una función recursiva para la búsqueda de un elemento (**Búsqueda Binaria**).
3. Analizar la complejidad temporal en el peor y mejor caso (O(n \log n), O(n^2), etc.).

---

### Ejercicio 4: Punteros a Función y Tablas de Despacho

Diseñar un menú interactivo o procesador de comandos que utilice un arreglo de punteros a función:

1. Declarar el tipo de dato puntero a función (`typedef`).
2. Crear un vector/tabla de funciones para cada comando disponible.
3. Invocar dinámicamente la función correspondiente según el comando ingresado por el usuario, evitando estructuras extensas de `if-else` o `switch-case`.

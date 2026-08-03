//3. Analizar la complejidad temporal en el peor y 
//mejor caso (O(n \log n)$, O(n^2), etc.).

/*
ANALISIS DE COMPLEJIDAD TEMPORAL (BIG-O)

1.QuickSort es un algoritmo de ordenamiento recursivo que utiliza la técnica de divide y vencerás.
    Mejor Caso; Complejidad O(n \log n)
Ocurre cuando el pivote siempre divide el vector en dos partes exactamente 
iguales (o muy similares). El árbol de llamadas se divide a la mitad en cada 
nivel (log n niveles) y en cada nivel se procesan n elementos.
    Caso promedio; Complejidad O(n \log n)
Ocurre en la inmensa mayoría de los casos con datos aleatorios o desordenados.
    Peor caso; Complejidad O(n^2)
Ocurre cuando el vector ya está completamente ordenado (o invertido) y elegimos 
siempre el último (o el primero) como pivote. El pivote divide el vector en un 
grupo de n-1 elementos y otro de 0, haciendo n divisiones.

2.Busqueda Binaria es un algoritmo de búsqueda recursivo que requiere que el arreglo esté ordenado.
    Mejor Caso; Complejidad O(1)
Ocurre cuando tienes mucha suerte y el elemento que estás buscando está justo 
en el medio en la primerísima comparación. Lleva tiempo constante.
    Peor Caso; Complejidad O(log n)
Ocurre cuando el elemento está en uno de los extremos del vector o directamente 
no existe en el arreglo. Tienes que dividir el arreglo a la mitad sucesivamente 
hasta que la sub-lista queda de tamaño 1.
*/



# Ejercicio 1 - Archivos

Se dispone de un archivo llamado Stock.dat que contiene la información de los 10 productos que vende una fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)

Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad

Ls carga de las ventas se envían como parámetros en el main() (podrá ser más de una a la vez).
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad  
Se genera un registro por cada venta que no pudo concretarse, pudiendo quedar en el archivo varios registros faltantes del mismo producto.
Al finalizar actualizar el archivo Stock.dat con el stock actualizado luego de procesar las ventas.

Ejercicio 2 – Máquina de Estado
Realizar un programa que simule un sistema de detección de intrusos en un servidor. El sistema debe analizar una secuencia de puertos de red atacados (ingresados como caracteres individuales por teclado) para detectar un patrón específico de escaneo táctico: la secuencia "p-o-r-t".

Ejercicio 3 – Recursividad

Un grupo de biólogos está investigando una especie de bacteria que se duplica a un ritmo constante. El comportamiento de la población sigue una regla matemática estricta:
• Minuto 0: Hay exactamente 1 bacteria en el laboratorio.
• Minuto \(N\): La cantidad de bacterias es exactamente el doble de la cantidad que había en el minuto anterior (\(N-1\)).
Realizar un programa en lenguaje C que contenga una función recursiva para calcular cuántas bacterias habrá en el laboratorio al cabo de un minuto \(N\) ingresado por el usuario.
Casos Base y Recursivo (Mapeo mental):
• Caso Base: Si el minuto es 0, la población es 1.
• Caso Recursivo: Para cualquier minuto \(N > 0\), la población es \(2 \times \text{población}(N-1)\).

Ejercicio 4 – Puntero a función

Un sistema industrial de control de procesos mide constantemente la temperatura de un reactor químico. Dependiendo del nivel de la temperatura medida, el sistema debe disparar una acción de alerta diferente de forma dinámica.
Se solicita diseñar un programa en lenguaje C que cumpla con los siguientes requerimientos:
1 Funciones de Alerta: Implementar tres funciones independientes que representen las acciones a tomar:
• alertaNormal: Imprime "[OK] Temperatura estable. Estado óptimo.".
• alertaAdvertencia: Imprime "[CUIDADO] Temperatura elevada. Monitorear de cerca.".
• alertaCritica: Imprime "[PELIGRO] ¡CRÍTICO! Activando sistema de enfriamiento de emergencia.".

2 Lógica del Selector (Puntero a Función): En lugar de usar un bloque if-else o switch-case gigante dentro de la rutina principal para ejecutar las alertas, debes declarar un puntero a función.

3 Evaluación: El programa solicitará al usuario la temperatura actual (un número entero).
• Si es menor a 40: se asignará el puntero a la función de alerta normal.
• Si está entre 40 y 79: se asignará a la función de advertencia.
• Si es 80 o más: se asignará a la función crítica.

4 Ejecución: Al final del ciclo, se debe invocar la acción correspondiente exclusivamente a través del puntero a función configurado.

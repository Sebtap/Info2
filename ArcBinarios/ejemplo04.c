/*4. Escribir un programa que abra un archivo PNG en modo 
binario y muestre por pantalla: A. Si el archivo es realmente 
un PNG válido (verificando los primeros 8 bytes: 
89 50 4E 47 0D 0A 1A 0A). B. 2. El ancho y alto de la imagen 
en píxeles. Datos del formato: • Los primeros 8 bytes son la 
firma PNG. • A continuación viene un chunk llamado IHDR. 
Su estructura comienza así: • 4 bytes: tamaño del 
chunk (uint32_t, big-endian) — ignorarlo. 
• 4 bytes: tipo del chunk (los caracteres ASCII "IHDR") 
— ignorarlos. • 4 bytes: ancho (uint32_t, big-endian). 
• 4 bytes: alto (uint32_t, big-endian). 
• Los uint32_t están en big-endian (network byte order). 
Como las PCs son little-endian, hay que invertir el orden de 
los bytes al leer. Probar el programa con varios PNG de ancho y 
alto conocido. Verificar el resultado abriendo la imagen en 
cualquier visor. */
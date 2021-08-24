# Modulo Kernel

Este modulo kernel solo funciona para la version de ubuntu 18.04

## Ejecutar Modulo kernel

1. instalar todas las librerias que vamos a utilizar con el comando = sudo apt-get install linux-headers-$(uname -r)
2. instalar build-essential = sudo apt-get install build-essential = es el compilador de c y c++
3. Entrar en consola a la carpeta donde se encuentra el modulo kernel y el makefile 
4. ejecutar el comando = make 
5. Se deben generar el modulo kernel, el archivo más importante es timestamps.ko que es el modulo kernel
6. Para instalar el modulo kernel creado debemos ejecutar el comando = sudo insmod timestamps.ko
7. Para ejecutar el kernel debemos estar en la carpeta proc y ejecutar el comando = cat timestamps 
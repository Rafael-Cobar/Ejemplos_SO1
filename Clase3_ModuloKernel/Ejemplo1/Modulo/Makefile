# Nombre del modulo 
obj-m += timestamps.o

# all = al realizar el comando make all, compila el archivo .c y genera todos los archivos
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) 

# clean = 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
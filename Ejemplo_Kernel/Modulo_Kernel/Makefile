# Como generar el build
obj-m += timestamps.o

# Crear el modulo kernel
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) 

# Limpiar el modulo kernel
modulesclean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
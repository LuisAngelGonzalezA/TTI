#Archivo MAakefile simple
all:  muestreo salida

elimina:
	rm *.o
	rm muestreo
	rm seno.dat

salida:
	./muestreo
	chmod +x mando

muestreo.o: muestreo.c
	gcc -c muestreo.c -Wall

archivo.o: archivos.c
	gcc -c archivos.c -Wall


procesamiento.o: procesamiento.c
	gcc -c procesamiento.c -Wall

muestreo: muestreo.o procesamiento.o archivos.o
	gcc muestreo.o procesamiento.o archivos.o -o muestreo -lm




.PHONY: clean

install: all
	if [ ! -d /usr/local/bin ] ; then \
		sudo mkdir /usr/local/bin; \
	fi; \
	sudo cp mando /usr/local/bin
uninstall:
	sudo rm /usr/local/bin/mando


clean:

	rm -f *.o muestreo



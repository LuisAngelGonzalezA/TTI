PROYECTO=UART_DATOS
DESTDIR=/usr/local/bin
CFLAGS=`mysql_config --cflags` `mysql_config --libs` -Wall 
CC=gcc
FILES := $(patsubst %.c, %.o, $(wildcard *.c))

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(FILES)
	$(CC) $^ -o $@ $(CFLAGS)

	
#EN FILES se obtienen todos los archivos con la terminación .c gracias a $(wildcard *-c), 
#luego se sustituye con patsubst,
#se buscan las cadenas con .c y cambia por .o dentro de lo que contiene la variable con wildcard
#con eso tenemos lo siguente:
#$(PROYECTO): muestreo.o procesamiento.o archivos.o
#	$(CC) $^ -o $@ $(LDFLAGS)

#EQUIVALENTE A LO DE ARRIBA
#$(PROYECTO): muestreo.o procesamiento.o archivos.o
#	$(CC) muestreo.o procesamiento.o archivos.o -o $(PROYECTO) $(CFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)
	


uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)

#Archivo Makefile con onjetivos falsos y valriables
Datos_seno=seno.dat
comodin=$(patsubst %.c,%.o,$(wildcard *.c))
PROYECTO=muestreo
CFLAGS=-Wall
DESTDIR=/usr/local/bin
LDFLAGS=-lm
CC=gcc

all: $(PROYECTO)

<<<<<<< HEAD
=======
%.o : %.c
	$(CC) -c $< $(CFLAGS)

>>>>>>> 9d3a144ce152df2dc1b67d094b964bbc2d2b7b36
$(PROYECTO): $(comodin)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO) $(Datos_seno)
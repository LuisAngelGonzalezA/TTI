#!/bin/bash

#Este programa configura el BCM_GPIO 17 usando el FHS y un script de shell

#export - Sirve para exportar el control del GPIO desde el kernel al espacio de usuario,
#escribiendo su número al archivo.
echo "17" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio17/direction

echo "18" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio18/direction


echo "27" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio27/direction


echo "22" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio22/direction


echo "23" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio23/direction


echo "24" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio24/direction

echo "25" > /sys/class/gpio/export
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio
echo "out" > /sys/class/gpio/gpio25/direction



GPIO=(17 18 27 22 23 24 25)
LETRA_h=(0 1 1 0 1 1 1)



#value - Atributo que permite escribir un valor digital al GPIO
while [ 1 ]
do

	for i in $(seq 1 5); do
	  echo $i
	done



do
  read INPUT_STRING
  case $INPUT_STRING in
	hello)
		echo "Hello yourself!"
		;;
	bye)
		echo "See you again!"
		break
		;;
	*)
		echo "Sorry, I don't understand"
		;;
  esac
done




	echo "1" > /sys/class/gpio/gpio17/value
	
	


	
	sleep 1

	echo "0" > /sys/class/gpio/gpio17/value
	echo "0" > /sys/class/gpio/gpio18/value
	echo "0" > /sys/class/gpio/gpio27/value
	echo "0" > /sys/class/gpio/gpio22/value
	echo "0" > /sys/class/gpio/gpio23/value
	echo "0" > /sys/class/gpio/gpio24/value
	echo "0" > /sys/class/gpio/gpio25/value
	
	sleep 1
done

#unexport - Revierte el efecto de exportar al espacio de usuario,
#escribiendo su número al archivo.
echo "17" > /sys/class/gpio/unexport
echo "18" > /sys/class/gpio/unexport
echo "27" > /sys/class/gpio/unexport
echo "22" > /sys/class/gpio/unexport

exit 0


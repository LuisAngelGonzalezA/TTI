#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	
	/*
	 * Recordatorio el servicio esta en 
	 * /etc/system/system
	 * 
	 * 
	 * Y por lo tanto con el sgueinte codigo podemos saber en que estado
	 * se encuentra el servicio 
	 * 
	 * 0	=	Esta activo
	 * 0	> 	Esta desactivado a lo cual, nos indica que esta desactivcado
	 * 
	 * 
	 * 
	 * 
	 * 
	 * */
	 
	
	int i=system("sudo systemctl is-active pwm_calculado.service");
	printf("\nEl valor del servicivio es =%d\n",i);
	return 0;
	
}

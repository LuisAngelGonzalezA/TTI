#ifndef INICIAR_SERIAL_H
#define INICIAR_SERIAL_H


//Configuración del uart con micro
int config_serial ( char *, speed_t );

/*
 * 
 * Converción de los datos recibidos del uart
 * 
 * */
void hexadecimal_a_voltaje(int voltaje_alto,int voltaje_bajo);
void hexadecimal_a_corriente(int corriente_alto,int corriente_bajo);
void hexadecimal_a_corriente_descarga(int corriente_alto,int corriente_bajo);
void hexadecimal_a_temperatura(int temperatura_alto,int temperatura_bajo);

/*
 * 
 * Consulta a las base de datos
 * 
 * */

void insert_voltaje(char *voltaje);
double mysql_corriente_bateria();

/*
 * 
 * Procesamiento de los datos obtenido de los micros
 * 
 * */
void procesar_datos(int * datos_recibidos_UART,unsigned char dato_envio);
void guardar_datos_voltaje(int * datos_recibidos_UART);
void guardar_datos_bateria(int * datos_recibidos_UART);
void guardar_datos_bateria_descarga(int * datos_recibidos_UART);
void recibir_valores_de_modulos(unsigned char dato_envio);
int etapa_de_bateria();

/*
 * 
 *Hilo para la espera de conexión de los micros por algun siniestro en la comunicacón
 * 
 * */
void * espera(void *arg);

#endif

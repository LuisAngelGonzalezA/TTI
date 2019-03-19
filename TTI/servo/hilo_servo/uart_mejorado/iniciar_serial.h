#ifndef INICIAR_SERIAL_H
#define INICIAR_SERIAL_H

int config_serial ( char *, speed_t );
void hexadecimal_a_voltaje(int voltaje_alto,int voltaje_bajo);
void hexadecimal_a_corriente(int corriente_alto,int corriente_bajo);
void hexadecimal_a_temperatura(int temperatura_alto,int temperatura_bajo);
void insert_voltaje(char *voltaje);
void procesar_datos(int * datos_recibidos_UART,unsigned char dato_envio);
void guardar_datos_voltaje(int * datos_recibidos_UART);
void guardar_datos_bateria(int * datos_recibidos_UART);
void guardar_datos_bateria_descarga(int * datos_recibidos_UART);
void recibir_valores_de_modulos(unsigned char dato_envio);
void * espera(void *arg);

#endif

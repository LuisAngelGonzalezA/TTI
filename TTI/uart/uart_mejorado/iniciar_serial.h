#ifndef INICIAR_SERIAL_H
#define INICIAR_SERIAL_H

int config_serial ( char *, speed_t );
void hexadecimal_a_voltaje(int voltaje_alto,int voltaje_bajo);
void hexadecimal_a_corriente(int corriente_alto,int corriente_bajo);
void hexadecimal_a_temperatura(int temperatura_alto,int temperatura_bajo);

#endif
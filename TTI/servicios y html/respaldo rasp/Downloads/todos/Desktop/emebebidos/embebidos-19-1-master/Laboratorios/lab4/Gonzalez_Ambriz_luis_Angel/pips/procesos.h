#ifndef PROCESOS_H
#define PROCESOS_H

void proceso_padre( int pipefd[] );
void proceso_hijo( int np, int datos[], int pipefd[] );

#endif

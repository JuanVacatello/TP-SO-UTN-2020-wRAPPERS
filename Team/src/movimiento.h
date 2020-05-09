#ifndef MOVIMIENTO_H_
#define MOVIMIENTO_H_

#include "entrenador.h"


#include <stdio.h>
#include <stdlib.h>

void moverse_izquierda(t_posicion* posicion, t_config* config);
void moverse_derecha(t_posicion* posicion,t_config* config);
void moverse_arriba(t_posicion* posicion,t_config* config);
void moverse_abajo(t_posicion* posicion, t_config* config);
_Bool sePuedeMover(int posicion);

#endif /* MOVIMIENTO_H_ */

/*
 * metadata.h
 *
 *  Created on: 11 jun. 2020
 *      Author: utnso
 */

#ifndef UTILS_METADATA_H_
#define UTILS_METADATA_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/config.h>
#include<commons/collections/list.h>
#include<commons/string.h>

#include"configGameCard.h"

t_config* metadata_tall_grass;

void leer_metadata_tall_grass();
int obtener_cantidad_bloques();
int obtener_tamanio_bloques();

t_config* leer_metadata_pokemon(char* path_metadata);
char** obtener_bloques_pokemon(t_config* metadata);
int obtener_cantidad_bloques_pokemon(t_config* metadata);
int archivo_esta_abierto(t_config* metadata);
int obtener_tamanio_archivo(t_config* metadata);


#endif /* UTILS_METADATA_H_ */
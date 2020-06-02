#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/collections/dictionary.h>
#include<string.h>
#include<pthread.h>
#include "entrenador.h"


//DEFINO VARIABLES GLOBALES

t_list* lista_de_entrenadores;

t_dictionary* objetivo_global;

t_dictionary* atrapados_global;

t_list* lista_de_entrenadores_ready;

t_list* pokemones_requeridos;

pthread_t* hilo_planificador;



typedef enum
{
	SUSCRIBIRSE=0,
	NEW_POKEMON=1,
	APPEARED_POKEMON=2,
	CATCH_POKEMON=3,
	CAUGHT_POKEMON=4,
	GET_POKEMON=5,
	LOCALIZED_POKEMON=6,
	MENSAJE = 7
} op_code;


//////////////////////////////////////////////SOCKETS//////////////////////////////////////////////////////




#endif /* CONEXIONES_H_ */

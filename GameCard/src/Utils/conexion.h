
#ifndef UTILS_CONEXION_H_
#define UTILS_CONEXION_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/collections/list.h>
#include<stdint.h>
#include<pthread.h>
#include<semaphore.h>

#include"configGameCard.h"
#include"metadata.h"
#include"conexion.h"
#include"bitmap.h"
#include"logGameCard.h"
#include"bloques.h"

typedef enum{
	SUSCRIPTOR=0,
	NEW_POKEMON=1,
	APPEARED_POKEMON=2,
	CATCH_POKEMON=3,
	CAUGHT_POKEMON=4,
	GET_POKEMON=5,
	LOCALIZED_POKEMON=6,
	MENSAJE=7
}op_code;

typedef struct{
	uint32_t size;
	void* stream;
} t_buffer;

typedef struct{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

pthread_t thread;

sem_t MUTEX_MENSAJES_GB;
sem_t MUTEX_SUB;
sem_t MUTEX_NEW_POKEMON;
sem_t MUTEX_NEW;
sem_t MUTEX_CATCH;
sem_t MUTEX_GET;


// Crear conexion (para Broker)
int crear_conexion(char* ip, char* puerto);

// Esperar y recibir mensajes de Gameboy
void iniciar_espera_mensajes_Gameboy(void);
void esperar_gameboy(int socket_servidor);
void serve_client(int* socket_cliente);
void process_request(op_code cod_op, int socket_cliente);

// Conexion con Broker y espera de mensajes
void new_pokemon_broker();
void catch_pokemon_broker();
void get_pokemon_broker();

// Suscripciones a las colas de Broker
int suscribirse_globalmente(op_code cola_a_suscribirse);
void* suscribirse_a_cola(int socket_broker, uint32_t cola_a_suscribirse, int* tamanio_paquete);

// Recibir mensajes de GameBoy y Broker
void recibir_new_pokemon(int socket_cliente);
void recibir_catch_pokemon(int socket_cliente);
void recibir_get_pokemon(int socket_cliente);
void responder_ack(uint32_t mensaje_id, int socket_broker);
//
void new_pokemon(char* pokemon,int posX,int posY, int cantidad);
int catch_pokemon(char* pokemon,int posX,int posY);
void* get_pokemon(char* pokemon, uint32_t* tamanio_void);
// Enviar mensaje a Broker
void recibir_mensaje_id(int socket_broker);
void enviar_appeared_pokemon(char* pokemon, uint32_t posX, uint32_t posY, uint32_t id_mensaje_correlativo);
void* iniciar_paquete_serializado_AppearedPokemon(int* tamanio_paquete, char* pokemon, uint32_t posX, uint32_t posY, uint32_t id_mensaje_correlativo);
void enviar_caught_pokemon(uint32_t id_mensaje_correlativo, uint32_t se_pudo_atrapar);
void* iniciar_paquete_serializado_CaughtPokemon(int* tamanio_paquete, uint32_t id_mensaje_correlativo, uint32_t se_pudo_atrapar);
void enviar_localized_pokemon(void* cantidad_y_posiciones, uint32_t tamanio_void, char* pokemon, uint32_t id_mensaje_correlativo);
void* iniciar_paquete_serializado_LocalizedPokemon(int* tamanio_paquete, uint32_t id_mensaje_correlativo, char* pokemon, void* cantidad_y_posiciones, uint32_t tamanio_void);

// Auxiliares
void* serializar_paquete(t_paquete* paquete, int *bytes);
char* recibir_mensaje(int socket_broker);

#endif /* UTILS_CONEXION_H_ */

#include "servidor.h"

#include <pthread.h>

int cantidadProcesosregistrados = 0;
cola_mensaje newPokemon, appearedPokemon, catchPokemon, caughtPokemon, getPokemon, localizedPokemon;

void iniciar_servidor(void)
{
	iniciar_logger();
	completar_logger("me creo","BROKER",LOG_LEVEL_INFO);
	int socket_servidor;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(IP, PUERTO, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next){
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }
        break;
    }

	if(listen(socket_servidor, SOMAXCONN) == -1){
		close(socket_servidor);
		exit(6);
	}

    freeaddrinfo(servinfo);

    completar_logger("termino de establecer socket","BROKER",LOG_LEVEL_INFO);

    while(1)
    	esperar_cliente(socket_servidor); // hacerlo con select, NUNCA ESPERA ACTIVA
}

void esperar_cliente(int socket_servidor)
{
	struct sockaddr_in dir_cliente;

	int tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

	pthread_create(&thread,NULL,(void*)serve_client,&socket_cliente);
	pthread_detach(thread);
}

void serve_client(int* socket)
{
	completar_logger("Se conectó proceso al Broker", "BROKER", LOG_LEVEL_INFO); // LOG OBLIGATORIO

	op_code cod_op;
	if(recv(*socket, &cod_op, sizeof(op_code), MSG_WAITALL) == -1)
		cod_op = -1;

	char* mensaje = string_from_format("El codigo de operacion es: %d.", cod_op);
	completar_logger(mensaje, "Broker", LOG_LEVEL_INFO);

	process_request(cod_op, *socket);
}

void process_request(op_code cod_op, int socket_cliente) {
	void* a_enviar;
	int tamanio_paquete = 0;

	if(cod_op == 0){
		atenderSuscripcion(socket_cliente);
	}
	switch (cod_op) {
		case 0:
			break;
		case 1:
			recibir_new_pokemon(socket_cliente);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			a_enviar = recibir_caught_pokemon(socket_cliente,&tamanio_paquete); //el unico q anda bien xq no tiene pokemon

			for(int i = 0; i < list_size(caughtPokemon.suscriptores); i++){
				proceso* suscriptor = list_get(caughtPokemon.suscriptores, i);
				int socket_suscriptor = suscriptor->socket_cliente;
				send(socket_suscriptor,a_enviar,tamanio_paquete,0);
			}

			break;
		case 5:
			break;
		case 6:
			break;
		case -1:
			pthread_exit(NULL);
			break;
		}
}

/*void* recibir_mensaje(int socket_cliente, int* size)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	void* buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}
*/
void* recibir_caught_pokemon(int socket_cliente, int* tamanio_paquete){
//abrirlo y meterlo en otro paquete, serializarlo y mandarlo. no se si esta bien esto:

	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = CAUGHT_POKEMON;
	paquete->buffer = malloc(sizeof(t_buffer));

	recv(socket_cliente, &(paquete->buffer->size), sizeof(uint32_t), MSG_WAITALL);
	recv(socket_cliente, paquete->buffer->stream, paquete->buffer->size, MSG_WAITALL);

	*tamanio_paquete = (paquete->buffer->size)+sizeof(op_code)+sizeof(uint32_t);

	void* a_enviar;
	//paquete recibido listo para mandar a los procesos suscriptos a caught_pokemon
	return a_enviar;
}

void recibir_new_pokemon(int socket_cliente)
{
	uint32_t tamanio_buffer;
	recv(socket_cliente, &tamanio_buffer, sizeof(uint32_t), MSG_WAITALL);

	char* m1 = string_from_format("El tamanio del buffer es: %d.", tamanio_buffer);
	completar_logger(m1, "BROKER", LOG_LEVEL_INFO);

	uint32_t caracteresPokemon;
	recv(socket_cliente, &caracteresPokemon, sizeof(uint32_t), MSG_WAITALL);

	char* m2 = string_from_format("Los caracteres de pokemon son: %d.", caracteresPokemon);
	completar_logger(m2, "BROKER", LOG_LEVEL_INFO);

	uint32_t posX;
	recv(socket_cliente, &posX, sizeof(uint32_t), MSG_WAITALL);

	char* m3 = string_from_format("La posicion en X es: %d", posX);
	completar_logger(m3, "BROKER", LOG_LEVEL_INFO);

	uint32_t posY;
	recv(socket_cliente, &posY, sizeof(uint32_t), MSG_WAITALL);

	char* m4 = string_from_format("La posicion en Y es: %d", posY);
	completar_logger(m4, "BROKER", LOG_LEVEL_INFO);

	uint32_t cantidad;
	recv(socket_cliente, &cantidad, sizeof(uint32_t), MSG_WAITALL);

	char* m5 = string_from_format("La cantidad de pokemons es: %d.", cantidad);
	completar_logger(m5, "BROKER", LOG_LEVEL_INFO);

	char* pokemon;
		int retorno = recv(socket_cliente, &pokemon, sizeof(caracteresPokemon), MSG_WAITALL);
		char* m6 = string_from_format("Retorno: %d.", retorno);
		completar_logger(m6, "BROKER", LOG_LEVEL_INFO);
	completar_logger(pokemon, "BROKER", LOG_LEVEL_INFO);

	/*
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = NEW_POKEMON;
	completar_logger("recibo new pokemon","Broker",LOG_LEVEL_INFO);

	paquete->buffer = malloc(sizeof(t_buffer));

	recv(socket_cliente, &(paquete->buffer->size), sizeof(int), MSG_WAITALL);
*/
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void devolver_mensaje(void* payload, int size, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = NEW_POKEMON;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = size;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, payload, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void atenderSuscripcion(int socket_cliente)
{
	proceso* suscriptor = modelarProceso(socket_cliente);
	suscribirseAColas(suscriptor, socket_cliente);
}

proceso* modelarProceso(int socket){
	proceso* suscriptor = malloc(sizeof(proceso));
	recv(socket, &(suscriptor->id), sizeof(uint32_t), MSG_WAITALL); // el id le llega PRIMERO con el socket, luego las colas
	suscriptor -> socket_cliente = socket;
	return suscriptor;
}

void suscribirseAColas(proceso* suscriptor, int socket){
	int size;
	recv(socket, &size, sizeof(int), MSG_WAITALL);

	for(int cantidad_colas = size/sizeof(op_code); cantidad_colas >0; cantidad_colas--){
		op_code cola_mensaje;

		recv(socket, &cola_mensaje,sizeof(op_code), MSG_WAITALL);
		switch(cola_mensaje){
			case 0:
				break; //OPCION SUSCRIBIRSE
			case 1:
				list_add(newPokemon.suscriptores, suscriptor);
				break;
			case 2:
				list_add(appearedPokemon.suscriptores, suscriptor);
				break;
			case 3:
				list_add(catchPokemon.suscriptores, suscriptor);
				break;
			case 4:
				list_add(caughtPokemon.suscriptores, suscriptor);
				break;
			case 5:
				list_add(getPokemon.suscriptores, suscriptor);
				break;
			case 6:
				list_add(localizedPokemon.suscriptores, suscriptor);
				break;
			}
	}
}

/* mensaje prueba

void atenderMensajePrueba(int socket_cliente){
	uint32_t tamanio_buffer;
	recv(socket_cliente, &tamanio_buffer, sizeof(uint32_t), MSG_WAITALL);

	uint32_t numero;

	recv(socket_cliente, &numero, tamanio_buffer, MSG_WAITALL);

	char* mensajeTamanio = string_from_format("El tamanio es: %d.", tamanio_buffer);
	completar_logger(mensajeTamanio, "Broker", LOG_LEVEL_INFO);

	char* mensajeNumero = string_from_format("El numero es: %d.", numero);
	completar_logger(mensajeNumero, "Broker", LOG_LEVEL_INFO);

} */
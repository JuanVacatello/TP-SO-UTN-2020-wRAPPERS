#include "memoria.h"

void guardar_mensaje_en_memoria(void* bloque_a_agregar_en_memoria, uint32_t tamanio_a_agregar){

	char* esquema_de_administracion = obtener_algoritmo_memoria();

	memcpy(memoria_principal, &bloque_a_agregar_en_memoria, tamanio_a_agregar); //usar semaforos xq es variable global

	char* mostrar_memoria;
	memcpy(mostrar_memoria, memoria_principal, tamanio_a_agregar);

	puts(mostrar_memoria);

	//if(!(strcmp(esquema_de_administracion, "PARTICIONES"))){
	//	administracion_de_memoria_particiones(bloque_a_agregar_en_memoria,tamanio_a_agregar);
	//}
}

void administracion_de_memoria_particiones(void* bloque_a_agregar_en_memoria, uint32_t tamanio_a_agregar){

	char* algoritmo_particion_libre = obtener_algoritmo_particion_libre();

	if(!(strcmp(algoritmo_particion_libre, "FF"))){

	}

	if(!(strcmp(algoritmo_particion_libre, "BF"))){

	}



}
#include<stdio.h>
#include<stdlib.h>

#include "Team.h"
#include "entrenador.h"
#include "utils.h"
#include "configTeam.h"
#include "logTeam.h"
#include "conexiones.h"



int main(void) {

		leer_config();
		iniciar_logger();


		iniciar_vg();

/*
		t_entrenador* entrenador;
		char* pokemonn;

		for(int i = 0; i < cantidad_entrenadores(); i++){
			entrenador = list_get(lista_de_entrenadores,i);
			for(int j = 0; j <list_size(entrenador->objetivo); j ++){
				pokemonn = list_get(entrenador->objetivo, j);
				puts(pokemonn);
			}
			puts("");
		}

 	 	int algoritmo;
		char* logFile;
		int retardo, tiempoReconexion, estimacion, quantum;// alpha;

		retardo = obtener_retardo_ciclo_cpu();
		printf("Retardo: %d\n",retardo);
		tiempoReconexion = obtener_tiempo_reconexion();
		printf("Tiempo de reconexion: %d\n",tiempoReconexion);
		estimacion = obtener_estimacion_inicial();
		printf("Estimacion: %d\n",estimacion);
		quantum = obtener_quantum();
		printf("Quantum: %d\n",quantum);
		logFile = obtener_log_file();
		puts("Log path:");
		puts(logFile);
		algoritmo = obtener_algoritmo_planificacion();
		printf("Algoritmo de planificacion: %d\n",algoritmo);
		alpha = obtener_alpha();
		printf("%d\n",alpha);
*/
		puts("aca entra1");
		puts("hola");

		pthread_create(&hilo_servidor, NULL , iniciar_servidor ,NULL);
		pthread_detach(hilo_servidor);

		pthread_create(&hilo_appeared_pokemon, NULL , appeared_pokemon_broker ,NULL);
		pthread_detach(hilo_appeared_pokemon);

		pthread_create(&hilo_caught_pokemon, NULL , caught_pokemon_broker ,NULL);
		pthread_detach(hilo_caught_pokemon);

		pthread_create(&hilo_localized_pokemon, NULL , localized_pokemon_broker ,NULL);
		pthread_detach(hilo_localized_pokemon);

		pthread_create(&hilo_planificador, NULL , planificacion ,NULL);
		pthread_join(hilo_planificador,NULL);

		puts("chau");

		return 0;
}


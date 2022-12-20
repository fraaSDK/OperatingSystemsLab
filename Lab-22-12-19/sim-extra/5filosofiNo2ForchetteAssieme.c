/* file:  5filosofiNo2ForchetteAssieme.c  */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 
#include "printerror.h"
#include "DBGpthread.h"

#define NUMFILOSOFI 5

/* variabili da proteggere */
/* la forchetta a sinistra di un filosofo
   ha lo stesso indice del filosofo.
	 */
int forchettaoccupata[NUMFILOSOFI];

/* variabili per la sincronizzazione */
pthread_mutex_t	 mutexForchetta[NUMFILOSOFI]; 

/* gli indici dei filosofi crescono in senso orario, da 0 a NUMFILOSOFI-1 
	indice	indiceforchAsinistra  indiceforcAdestra
	0		0		4
	1		1		0
	2		2		1
	3		3		2
	4		4		3
	indice	indiceprimaforc	  indicsecondaforc
	0		0		4    <--inversione contro deadlock
	1		0		1
	2		1		2
	3		2		3
	4		3		4

queste 2 funzioni qui sotto servono per implementare
la versione anti-deadlock che usa l'inversione 
della prima forchetta presa
*/
int get_fork_index_l(const int index_filosofo) {
	return index_filosofo == 0 ? 0 : index_filosofo - 1;
}

int get_fork_index_r(const int index_filosofo) {
	return index_filosofo == 0 ? NUMFILOSOFI - 1 : index_filosofo;
}

/* gli indici  dei filosofi crescono in senso orario, da 0 a NUMFILOSOFI-1 
*/
void *filosofo (void *arg) 
{ 
	char Flabel[128];
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Flabel,"F%d",indice);

	
	while(1) {
		int indiceforchetta1 = get_fork_index_l(indice);
		int indiceforchetta2 = get_fork_index_r(indice);
		printf("filosofo %s sta pensando \n", Flabel ); 
		fflush(stdout);
		/* il filosofo pensa per 1/2 di sec piu o meno */
		DBGnanosleep( 500000000+indice*1000000, Flabel );

		/* il filosofo prende le due forchette NON IN MANIERA ATOMICA */
		/* AGGIUNGERE CODICE */
		printf("filosofo %s [?] la forchetta sx %i.\n", Flabel, indiceforchetta1);
		DBGpthread_mutex_lock(&mutexForchetta[indiceforchetta1], Flabel);
		printf("filosofo %s [+] la forchetta sx %i.\n", Flabel, indiceforchetta1);
		sleep(2);
		
		printf("filosofo %s [?] la forchetta dx %i.\n", Flabel, indiceforchetta2);
		DBGpthread_mutex_lock(&mutexForchetta[indiceforchetta2], Flabel);
		printf("filosofo %s [+] la forchetta dx %i.\n", Flabel, indiceforchetta2);
		sleep(2);

		/* FINE AGGIUNTA CODICE */

		/*  FILOSOFO MANGIA */
		printf("filosofo %s MANGIA \n", Flabel ); 
		fflush(stdout);
		/* il filosofo mangia per circa 11 sec */
		DBGnanosleep( 11000000000+indice*1000000, Flabel );
		printf("filosofo %s FINISCE DI MANGIARE \n", Flabel ); 
		fflush(stdout);

		/* il filosofo rilascia le forchette */
		/* AGGIUNGERE CODICE */
		DBGpthread_mutex_unlock(&mutexForchetta[indiceforchetta1], Flabel);
		printf("filosofo %s [-] la forchetta sx %i.\n", Flabel, indiceforchetta1);
		DBGpthread_mutex_unlock(&mutexForchetta[indiceforchetta2], Flabel);
		printf("filosofo %s [-] la forchetta dx %i.\n", Flabel, indiceforchetta2);
		





		/* FINE AGGIUNTA CODICE */

	}
	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc, i, *intptr;

	for(i=0;i<NUMFILOSOFI;i++) {
		rc = pthread_mutex_init( &mutexForchetta[i], NULL); 
		if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	}

	for(i=0;i<NUMFILOSOFI;i++) {
		intptr=malloc(sizeof(int));
		if( !intptr ) { printf("malloc failed\n");exit(1); }
		*intptr=i;
		rc=pthread_create( &th,NULL,filosofo,(void*)intptr); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
} 
  
  
  

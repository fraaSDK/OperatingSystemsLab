/* file:   attacchinicontimer_semplice.c
*/ 

/* la 	#define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <semaphore.h>
#include <stdint.h>	/* uint64_t intptr_t */
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h> 

#include "DBGpthread.h"

#define NUMATTACCHINI 2

int numAttacchiniInAttesaDiLavorare;	/* num attacchini in attesa di lavorare */
int OrologioFaiWait;
pthread_mutex_t  mutex;
pthread_cond_t condAttesaArrivoAttacchino2;	/* attesa per arrivo del secondo attacchino */
pthread_cond_t condOrologioCominciaCountdown;	/* orologio attende di contare i secondi */
pthread_cond_t condAttesaSuonoOrologio;	/* attesa per fine del lavoro */


void* Attacchino (void *arg) 
{ 
	intptr_t indice;
	char Alabel[128];

	indice=(intptr_t)arg;
	sprintf(Alabel,"A%" PRIiPTR "", indice);

	while(1) {

		/* prendo la mutua esclusione sulle variabili */
		DBGpthread_mutex_lock( &mutex, Alabel );
		numAttacchiniInAttesaDiLavorare++;

		printf("Attacchino %s vorrebbe lavorare\n", Alabel ); 
		fflush(stdout);

		/* se sono l'attacchino arrivato per primo, devo aspettare il secondo attacchino */
		if( numAttacchiniInAttesaDiLavorare==1) {

			/* DA COMPLETARE */
			DBGpthread_cond_wait(&condAttesaArrivoAttacchino2, &mutex, Alabel);
		}
		else {	/* numAttacchiniInAttesaDiLavorare==2 
			se sono l'attacchino arrivato per secondo, devo svegliare il primo 
			*/

			/* DA COMPLETARE */
			DBGpthread_cond_signal(&condAttesaArrivoAttacchino2, Alabel);

			/* e devo far partire il timer */

			/* DA COMPLETARE */
			OrologioFaiWait = 0;	/* Clock needs to start, no waiting. */
			DBGpthread_cond_signal(&condOrologioCominciaCountdown, Alabel);

		}
		/* DA COMPLETARE */
		numAttacchiniInAttesaDiLavorare--;

		printf("Attacchino %s comincia ad attaccare manifesti\n", Alabel ); 
		fflush(stdout);

		/* attendo il suono dell'orologio */
		/* DA COMPLETARE */
		DBGpthread_cond_wait(&condAttesaSuonoOrologio, &mutex, Alabel);


		/* DA COMPLETARE */
		DBGpthread_mutex_unlock(&mutex, Alabel);


		/* QUI L' ATTACCHINO VA A PRENDERE ALTRI MANIFESTI */
		printf("Attacchino %s prende altri manifesti e colla\n", Alabel ); 
		fflush(stdout);
	}
	pthread_exit(NULL); 
} 

void* Orologio (void *arg) 
{ 
	char Olabel[128];

	sprintf(Olabel,"Orologio");

	while(1) {
		DBGpthread_mutex_lock(&mutex,Olabel); 

		if( OrologioFaiWait ) {
			DBGpthread_cond_wait( &condOrologioCominciaCountdown, &mutex, Olabel );
		}
		OrologioFaiWait=1;
	  	DBGpthread_mutex_unlock(&mutex,Olabel); 

		sleep(5);

		printf("Orologio avvisa gli attacchini\n" ); 
		fflush(stdout);

		DBGpthread_mutex_lock(&mutex,Olabel); 
		DBGpthread_cond_broadcast( &condAttesaSuonoOrologio, Olabel);
	  	DBGpthread_mutex_unlock(&mutex,Olabel); 
	}
	exit(0); 
} 

int main (int argc, char* argv[] ) 
{ 
	int rc;
	intptr_t i;

	rc = pthread_mutex_init(&mutex, NULL ); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	rc = pthread_cond_init(&condAttesaArrivoAttacchino2, NULL ); 
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&condAttesaSuonoOrologio, NULL ); 
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&condOrologioCominciaCountdown, NULL ); 
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	OrologioFaiWait=1; /* la prima volta l'orologio deve aspettare */
	numAttacchiniInAttesaDiLavorare=0;	/* all'inizio nessuno attacchino in attesa di lavorare */

	for(i=0;i<NUMATTACCHINI;i++) {
		pthread_t th;

		rc=pthread_create( &th,NULL,Attacchino,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	Orologio(NULL);
	exit(0);
} 
  

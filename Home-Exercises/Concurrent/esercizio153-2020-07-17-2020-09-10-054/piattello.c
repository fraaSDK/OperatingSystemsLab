/* file:  piattello.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMTIRATORI 10
#define DELAYTRADUEPIATTELLI8sec 8

/* dati da proteggere - AGGIUNGETE QUELLO CHE VI SERVE */
int num_piattelli = 0;
int piattello_colpito = 0;

/* variabili per la sincronizzazione - AGGIUNGETE QUELLO CHE VI SERVE */
pthread_mutex_t mutex;
pthread_cond_t wait_for_target_cond;

void attendi( int min, int max) {
	int secrandom=0;
	if( min > max ) return;
	else if ( min == max ) 
		secrandom = min;
	else
		secrandom = min + ( random()%(max-min+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 ) 
			{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
	return;
}

void *Tiratore (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Tiratore%" PRIiPTR "",indice);

	/*  da completare  */

	while ( 1 ) {

		/*  da completare  */
		DBGpthread_mutex_lock(&mutex, Plabel);

		/* il tiratore  attende l'inizio del volo del piattello */
		printf("tiratore %s attende piattello \n", Plabel);
	        fflush(stdout);

		/*  da completare  */
		DBGpthread_cond_wait(&wait_for_target_cond, &mutex, Plabel);

		printf("tiratore %s mira e .... \n", Plabel);
	        fflush(stdout);

		/*  da completare  */


		/* il tiratore si prepara a sparare impiegando da 2 a 4 secondi */
		attendi( 2, 4 );


		/*  da completare  */
		if (num_piattelli == 1) {
			piattello_colpito++;
			printf("tiratore %s ha colpito il piattello.\n", Plabel);
		}

		/* il tiratore finisce il tentativo di sparare al piattello in volo */
		printf("tiratore %s è arrivato tardi\n", Plabel);
	        fflush(stdout);


		/*  da completare  */
		DBGpthread_mutex_unlock(&mutex, Plabel);
	}
	pthread_exit(NULL); 
}


void *Piattello (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Piattello%" PRIiPTR "",indice);


	/*  da completare  */
	DBGpthread_mutex_lock(&mutex, Plabel);
	if (num_piattelli == 1) {
		printf("piattello %s termina, c'è già un piattello.\n", Plabel);
		pthread_exit(NULL);
	}

	num_piattelli++;
	printf("piattello %s inizia volo\n", Plabel);
        fflush(stdout);

	/*  da completare  */
	DBGpthread_cond_broadcast(&wait_for_target_cond, Plabel);
	DBGpthread_mutex_unlock(&mutex, Plabel);

	/* il piattello vola per tre secondi */
	attendi( 3, 3 );


	/*  da completare  */
	DBGpthread_mutex_lock(&mutex, Plabel);
	num_piattelli--;

	if (piattello_colpito > 0) {
		printf("piattello %s è stato colpito %d volte.\n", Plabel, piattello_colpito);
		piattello_colpito = 0;
	}

	printf("piattello %s finisce volo e termina\n", Plabel);
       	fflush(stdout);

	/*  da completare  */
	DBGpthread_mutex_unlock(&mutex, Plabel);

	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	uintptr_t i=0;
	int seme;
	/* aggiungete eventuali vostre variabili */


	seme=time(NULL);
        srandom(seme);

	/* INIZIALIZZATE LE VOSTRE VARIABILI CONDIVISE e tutto quel che serve - fate voi */
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&wait_for_target_cond, NULL);

	/* all'inizio non c'e' nessun piattello in volo */

	/* CREAZIONE PTHREAD dei tiratori */
	for(i=0;i<NUMTIRATORI;i++) {
		rc=pthread_create(&th,NULL,Tiratore,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* CREAZIONE NUOVO PIATTELLO OGNI 8 secondi */
	i=0;
	while(1) {
		/* un nuovo piattello ogni 8 secondi */
		attendi( DELAYTRADUEPIATTELLI8sec, DELAYTRADUEPIATTELLI8sec );
		i++;
		/* crea pthread piattello - completate voi */
		rc = pthread_create(&th, NULL, Piattello, (void*)i);
		if (rc) PrintERROR_andExit(rc, "pthread_created failed for Piattello.");
	}

	pthread_exit(NULL);
	return(0); 
} 
  

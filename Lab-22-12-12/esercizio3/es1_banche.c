/* file:  es1_banche.c DA COMPLETARE */


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t intptr_t */
#include <inttypes.h>	/* uint64_t  PRIiPTR */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <time.h>	/* nanosleep()    struct timespec */
#include <pthread.h> 

#include "printerror.h"

#define NUMBANCHE 2
#define NUMDEPOSITIPERBANCA 3
#define NUMPRELIEVIPERBANCA 2

typedef struct struttura {
	int indicebanca;
	int indicethread;
} STRUTTURA;

/* variabili da proteggere */
double T[NUMBANCHE];
int    N[NUMBANCHE];

/* variabile per la mutua esclusione */
pthread_mutex_t    mutex;

void *Depositi (void *arg) 
{ 
	char Clabel[128];
	int indicebanca;
	int indicethread;

	indicebanca=((STRUTTURA*)arg)->indicebanca;
	indicethread=((STRUTTURA*)arg)->indicethread;
	sprintf(Clabel,"D%iB%i" , indicethread, indicebanca);

	free(arg);

	while(1) 
	{
		int rc;
                struct timespec ts={0, 400000000L }; /* 4/10 sec */

		sleep(1);

		/* DEVO ENTRARE IN SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER ENTRARE IN SEZIONE CRITICA */
		rc = pthread_mutex_lock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_lock failed in Deposit.");

		/* FINE AGGIUNTA */

		/* MODIFICO TOTALE DI BANCA E STAMPO VALORI */ 
		T[indicebanca] += 10.0;
		N[indicebanca] ++;
		printf("Deposito %s: N %d  T %f \n", Clabel, N[indicebanca], T[indicebanca] );
		fflush(stdout);
		nanosleep(&ts,NULL);

		/* ESCO DALLA SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER USCIRE DALLA SEZIONE CRITICA */
		rc = pthread_mutex_unlock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_unlock failed in Deposit.");

		/* FINE AGGIUNTA */

	}
	pthread_exit(NULL); 
} 

void *Prelievi (void *arg) 
{ 
	char Clabel[128];
	int indicebanca;
	int indicethread;

	indicebanca=((STRUTTURA*)arg)->indicebanca;
	indicethread=((STRUTTURA*)arg)->indicethread;
	sprintf(Clabel,"P%iB%i" , indicethread, indicebanca);

	free(arg);

	while(1) 
	{
		int rc;
                struct timespec ts={0, 400000000L }; /* 4/10 sec */

		sleep(1);

		/* DEVO ENTRARE IN SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER ENTRARE IN SEZIONE CRITICA */
		rc = pthread_mutex_lock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_lock failed in Withdraw.");

		/* FINE AGGIUNTA */

		/* MODIFICO TOTALE DI BANCA E STAMPO VALORI */ 
		T[indicebanca] -=9.0 ;
		N[indicebanca] ++;
		printf("Prelievo %s: N %d  T %f \n", Clabel, N[indicebanca], T[indicebanca] );
		fflush(stdout);
		nanosleep(&ts,NULL);

		/* ESCO DALLA SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER USCIRE DALLA SEZIONE CRITICA */
		rc = pthread_mutex_unlock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_unlock failed in Withdraw.");

		/* FINE AGGIUNTA */
	}
	pthread_exit(NULL); 
} 

void *BancadItalia (void *arg) 
{ 
	char Clabel[128];

	sprintf(Clabel,"BancadItalia" );

	while(1) 
	{
		int rc;
		int i;  int Num=0; double sum=0.0;

		/* DEVO ENTRARE IN SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER ENTRARE IN SEZIONE CRITICA */
		rc = pthread_mutex_lock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_lock failed in BancadItalia.");

		/* FINE AGGIUNTA */

		/* CALCOLO LA SOMMA DEI DEPOSITI DI TUTTE LE BANCHE
		   ED IL NUMERO DI OPERAZIONI TOTALI FATTE
		   e le metto in var locali 
		*/
		for( i=0; i<NUMBANCHE; i++ ) {
			Num += N[i];
			sum += T[i];
		}

		/* ESCO DALLA SEZIONE CRITICA */
		/* AGGIUNGERE CODICE PER USCIRE DALLA SEZIONE CRITICA */
		rc = pthread_mutex_unlock(&mutex);
		if (rc) PrintERROR_andExit(rc, "pthread_mutex_unlock failed in BancadItalia.");

		/* FINE AGGIUNTA */

		/* STAMPO SOMMA CALCOLATA */ 
		printf("Report BancaDItalia: Num %d  sum %f \n", Num, sum);
		fflush(stdout);

		sleep(30);
	}
	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	pthread_t   th; 
	int  rc;
	int i,k;
	STRUTTURA *ptr;

	/* INIZIALIZZO VAR MUTEX */
	rc = pthread_mutex_init( &mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	/* INIZIALIZZO VAR Totale e Contatori operazioni */
	for( i=0; i<NUMBANCHE; i++ ) {
		T[i]=0.0;
		N[i]=0;
	}


	/* FACCIO PARTIRE pthread  */
	for(i=0;i<NUMBANCHE;i++) {
		/* lancio  thread Depositi */
		for(k=0;k<NUMDEPOSITIPERBANCA;k++) {
			ptr=malloc( sizeof(STRUTTURA) );
			if( !ptr ) 
				{ printf("malloc failed\n");fflush(stdout);exit(9); }
			ptr->indicebanca=i;
			ptr->indicethread=k;
			rc=pthread_create( &th, NULL,Depositi,(void*)ptr); 
			if(rc) PrintERROR_andExit(rc,"pthread_create failed");
		}
		/* lancio  thread Prelievi */
		for(k=0;k<NUMPRELIEVIPERBANCA;k++) {
			ptr=malloc( sizeof(STRUTTURA) );
			if( !ptr ) 
				{ printf("malloc failed\n");fflush(stdout);exit(9); }
			ptr->indicebanca=i;
			ptr->indicethread=k;
			rc=pthread_create( &th, NULL,Prelievi,(void*)ptr); 
			if(rc) PrintERROR_andExit(rc,"pthread_create failed");
		}
	}

	/* lancio thread BancadItalia */
	rc=pthread_create( &th, NULL,BancadItalia,(void*)NULL ); 
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");

	pthread_exit(NULL); 

	return(0); 
} 
  
  
  

#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
pthread_cond_t cond;

int current_threads = 0;
int current_turn = 0;
int ret;

/* Simple error handling function. */
void handle_error(const int ret, const char* err_type, const char* th_name) {
    if (ret == 0) return;
    printf("[!] %s FAILED IN %s\n", err_type, th_name);
    pthread_exit(NULL);
}

void *thread(void *arg) {

    int turn = (intptr_t)arg;

    ret = pthread_mutex_lock(&mutex);
    handle_error(ret, "pthread_mutex_lock", "thread");

    /* If its not our turn, we signal the other threads*/
    while (turn != current_turn) {
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &mutex);
    }
    current_turn++;

    printf("[+] T%d is active\n", turn);
    sleep(1);

    current_threads++;

    if (current_threads == NUM_THREADS) {
        pthread_cond_signal(&cond);
    }

    /* Waiting for the other threads to arrive before exiting. */
    pthread_cond_wait(&cond, &mutex);

    printf("[-] T%d is ending.\n", turn);

    /* Waking next thread. */
    pthread_cond_signal(&cond);

    ret = pthread_mutex_unlock(&mutex);
    handle_error(ret, "pthread_mutex_unlock", "thread");

    pthread_exit(NULL);
}

int main() {

    pthread_t th;
    intptr_t i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        ret = pthread_create(&th, NULL, thread, (void*)i);
        handle_error(ret, "pthread_create", "thread");
    }

    pthread_exit(NULL);
    return 0;
}
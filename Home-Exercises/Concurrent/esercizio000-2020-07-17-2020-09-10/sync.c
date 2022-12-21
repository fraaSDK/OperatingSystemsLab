#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
pthread_cond_t cond;

int current_threads = 0;
int turn = 0;
int ret;

/* Simple error handling function. */
void handle_error(const int ret, const char* err_type, const char* th_name) {
    if (ret == 0) return;
    printf("[!] %s FAILED IN %s\n", err_type, th_name);
    pthread_exit(NULL);
}

void *thread(void *arg) {

    int index = (intptr_t)arg;
    int th_turn;

    ret = pthread_mutex_lock(&mutex);
    handle_error(ret, "pthread_mutex_lock", "thread");

    /* Assigning a turn to each thread. */
    th_turn = turn;
    turn++;
    printf("[T%d]: assigned turn %d starts.\n", index, th_turn);

    current_threads++;
    sleep(1);

    /*
     * All threads are waiting.
     * Starting the exit cascade
     * based by turn.
    */
    if (current_threads == 5) {
        pthread_cond_signal(&cond);
    }

    /* Waiting for all threads. */
    pthread_cond_wait(&cond, &mutex);

    pthread_cond_signal(&cond);

    /* Exit all threads by turn. */
    printf("[T%d]: assigned turn %d ends.\n", index, th_turn);

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
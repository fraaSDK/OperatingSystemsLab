#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL_CARS 10
#define MAX_CARS_ON_BRIDGE 5

pthread_mutex_t bridge_mutex;
pthread_cond_t wait_cars_cond;

/* Variables to protect. */
int cars_waiting = 0;
int cars_on_bridge = 0;

int ret;
intptr_t i;

/* Simple error handling function. */
void handle_error(const int ret, const char* err_type, const char* th_name) {
    if (ret == 0) return;
    printf("[!] %s FAILED IN %s\n", err_type, th_name);
    pthread_exit(NULL);
}

void *bridge(void *arg) {
    while (1) {
        ret = pthread_mutex_lock(&bridge_mutex);
        handle_error(ret, "pthread_mutex_lock", "bridge_th");

        /*
         * Until we reach the required amount of cars on the bridge at once,
         * we wait for the car thread to wake us up.
        */
        while (cars_waiting < MAX_CARS_ON_BRIDGE) {
            pthread_cond_wait(&wait_cars_cond, &bridge_mutex);
        }

        printf("[B] Current cars waiting: %d\n", cars_waiting);

        /*
         * There are MAX_CARS_ON_BRIDGE or more, the bridge is awaken
         * and we let 5 cars pass.
        */
        printf("[!] On the bridge...\n");
        sleep(MAX_CARS_ON_BRIDGE);
        cars_waiting -= MAX_CARS_ON_BRIDGE;

        printf("[B] Current cars waiting: %d\n", cars_waiting);

        /*
         * The bridge is not busy, waking up all waiting cars.
         * If more than 5 cars are already waiting, they will be allowed
         * to cross the bridge, otherwise the bridge will wait until
         * the requirement is reached.
        */
        pthread_cond_broadcast(&wait_cars_cond);

        ret = pthread_mutex_unlock(&bridge_mutex);
        handle_error(ret, "pthread_mutex_unlock", "bridge_th");
    }
}

void *car(void *arg) {
    int car_index = (intptr_t)arg;

    while (1) {
        ret = pthread_mutex_lock(&bridge_mutex);
        handle_error(ret, "pthread_mutex_lock", "car_th");

        /* Keeping track on how many cars are waiting. */
        cars_waiting++;
        printf("[C%d] [+] Cars waiting: %d\n", car_index, cars_waiting);

        /* If we have at least 5 cars waiting we wake up the bridge. */
        if (cars_waiting >= MAX_CARS_ON_BRIDGE) {
            pthread_cond_signal(&wait_cars_cond);
        }

        /*
         * We have more cars that can cross the bridge,
         * we wait for the bridge to signal us that we can
         * resume the thread.
         * 
         * In other words, when the number of cars waiting
         * is greater than the maximum allowed, the car thread
         * will go to sleep and wait for the bridge thread
         * to signal it to resume execution.
         * When the bridge thread signals the car thread to resume,
         * the car thread will check the value of cars_waiting again.
         * If the number of cars waiting is still greater
         * than the maximum allowed, the car thread will go back to sleep
         * and wait for the bridge thread to signal it again.
         * This process will continue until the number of cars waiting
         * is less than or equal to the maximum allowed, at which point
         * the car thread will exit the while loop and continue execution.
        */
        while (cars_waiting > MAX_CARS_ON_BRIDGE) {
            pthread_cond_wait(&wait_cars_cond, &bridge_mutex);
        }

        ret = pthread_mutex_unlock(&bridge_mutex);
        handle_error(ret, "pthread_mutex_unlock", "car_th");
    }
}

int main() {

    pthread_t bridge_th;
    pthread_t car_th[TOTAL_CARS];

    pthread_mutex_init(&bridge_mutex, NULL);
    pthread_cond_init(&wait_cars_cond, NULL);

    ret = pthread_create(&bridge_th, NULL, bridge, NULL);

    /* Creating car threads. */
    for (i = 0; i < TOTAL_CARS; i++) {
        ret = pthread_create(&car_th[i], NULL, car, (void*)i);
        handle_error(ret, "pthread_create", "car_th");
    }

    pthread_exit(NULL);
    return 0;
}

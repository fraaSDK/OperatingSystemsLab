#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>

/* Requirement: Students > Forms. */
#define FORMS_NUM 4
#define STUDENT_NUM 7

pthread_mutex_t forms_mutex;            /* Mutex used to block the access to the form number variable.                */
pthread_cond_t refill_cond;             /* Cond for waiting/signaling the need to refill the forms.                   */
pthread_cond_t student_turn_cond;       /* Cond for waiting/signaling the student who is waiting for their turn.      */
pthread_cond_t student_refill_cond;     /* Cond for waiting/signaling the student while the forms are being refilled. */

int ret;        /* Return value for pthread error handling. */
intptr_t i;     /* Index used to use as a student id. Used intptr_t type because it has to be casted to (void*). */

/* Global variables to protect with mutex. */
int current_forms_num = FORMS_NUM;
int current_student = 0;

/* Simple error handling function. */
void handle_error(const int ret, const char* err_type, const char* th_name) {
    if (ret == 0) return;
    printf("[!] %s FAILED IN %s\n", err_type, th_name);
    pthread_exit(NULL);
}

void *secretary(void *arg) {
    
    while(1) {
        ret = pthread_mutex_lock(&forms_mutex);
        handle_error(ret, "pthread_mutex_lock", "secretary");

        pthread_cond_wait(&refill_cond, &forms_mutex);
        /* Refilling the forms back to max. */
        printf("Current forms: %d\t Refilling... ", current_forms_num);
        current_forms_num = FORMS_NUM;
        printf("[Now: %d]\n", current_forms_num);
        
        pthread_cond_signal(&student_refill_cond);

        ret = pthread_mutex_unlock(&forms_mutex);
        handle_error(ret, "pthread_mutex_unlock", "secretary");
    }
}

void *student(void *arg) {
    
    int index = (intptr_t)arg;
    while (1) {
        ret = pthread_mutex_lock(&forms_mutex);
        handle_error(ret, "pthread_mutex_lock", "student");

        /* Checking if its the student's turn. */
        while (current_student != index) {
            if (current_student != index) pthread_cond_wait(&student_turn_cond, &forms_mutex);
        }

        /* Not enough forms, waking up secretary. */
        while (current_forms_num == 0) {
            pthread_cond_signal(&refill_cond);
            pthread_cond_wait(&student_refill_cond, &forms_mutex);
        }

        /* Filling the form... */
        printf("[Student%d] START\t Current Forms: %d\n", index, current_forms_num);
        sleep(1);
        current_forms_num--;
        printf("[Student%d] END  \t Current Forms: %d\n", index, current_forms_num);

        /* Updating current student turn and waking up the student threads. */
        current_student = (current_student + 1) % STUDENT_NUM; 
        pthread_cond_broadcast(&student_turn_cond);
        
        ret = pthread_mutex_unlock(&forms_mutex);
        handle_error(ret, "pthread_mutex_unlock", "student");
    }
}

int main() {
    
    pthread_t secretary_th;
    pthread_t student_th[STUDENT_NUM];

    pthread_mutex_init(&forms_mutex, NULL);

    /* Creating thread for the secretary. */
    ret = pthread_create(&secretary_th, NULL, secretary, NULL);
    handle_error(ret, "pthread_create", "secretary");

    /* Creating threads for the student */
    for (i = 0; i < STUDENT_NUM; i++) {
        ret = pthread_create(&student_th[i], NULL, student, (void*)i);
        handle_error(ret, "pthread_create", "student");
    }

    pthread_exit(NULL);
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>

#define FORMS_NUM 4
#define STUDENT_NUM 7

pthread_mutex_t forms_mutex;
pthread_cond_t refill_cond;
pthread_cond_t student_turn_cond;

int ret;
intptr_t i;

/* Global variables to protect with mutex. */
int current_forms_num = FORMS_NUM;
int current_student = 0;

void *secretary(void *arg) {
    
    while(1) {
        ret = pthread_mutex_lock(&forms_mutex);
        if (ret) {
            printf("pthread_mutex_lock failed in secretary.\n");
            pthread_exit(NULL);
        }

        pthread_cond_wait(&refill_cond, &forms_mutex);
        /* Refilling the forms back to max. */
        printf("Current forms: %d\tRefilling... ", current_forms_num);
        current_forms_num = FORMS_NUM;
        printf("[Now: %d]\n", current_forms_num);
        
        pthread_cond_signal(&student_turn_cond);

        ret = pthread_mutex_unlock(&forms_mutex);
        if (ret) {
            printf("pthread_mutex_unlock failed in secretary.\n");
            pthread_exit(NULL);
        }
    }
}

void *student(void *arg) {
    
    int index = (intptr_t)arg;
    while (1) {
        ret = pthread_mutex_lock(&forms_mutex);
        if (ret) {
            printf("pthread_mutex_lock failed in student.\n");
            pthread_exit(NULL);
        }

        /* Not enough forms, waking up secretary. */
        while (current_forms_num == 0) {
            pthread_cond_signal(&refill_cond);
            pthread_cond_wait(&student_turn_cond, &forms_mutex);
        }

        printf("[Student%d] FILL\t Forms: %d\n", index, current_forms_num);
        /* Filling the form... */
        sleep(1);
        current_forms_num--;
        
        /*current_student = (current_student + 1) % STUDENT_NUM;*/
        printf("[Student%d] DONE\t Forms: %d\n", index, current_forms_num);

        /* current_student = (current_student + 1) % STUDENT_NUM; */
        
        ret = pthread_mutex_unlock(&forms_mutex);
        if (ret) {
            printf("pthread_mutex_unlock failed in student.\n");
            pthread_exit(NULL);
        }
    }
}

int main() {
    
    pthread_t secretary_th;
    pthread_t student_th[STUDENT_NUM];

    pthread_mutex_init(&forms_mutex, NULL);

    /* Creating thread for the secretary. */
    ret = pthread_create(&secretary_th, NULL, secretary, NULL);
    if (ret) {
        printf("pthread_create failed for secretary.\n");
        return 1;
    }

    /* Creating threads for the student */
    for (i = 0; i < STUDENT_NUM; i++) {
        ret = pthread_create(&student_th[i], NULL, student, (void*)i);
        if (ret) {
            printf("pthread_create failed for student.\n");
            return 1;
        }
    }

    /* pthread_mutex_destroy(&forms_mutex); */
    pthread_exit(NULL);
    return 0;
}
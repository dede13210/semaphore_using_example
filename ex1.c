#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

/* Global variables */
int x = 0;
sem_t *sync_1;
sem_t *sync_2;
/* Thread function */
void a1(){
    printf("a1,X = %d\n", x);
    x=55;
    sleep(2);
}
void a2(){
    printf("a2,X = %d\n", x);
    x=55;
    sleep(2);
}
void b1(){
    printf("b1,X = %d\n", x);
}
void b2(){
    printf("b2,X = %d\n", x);
}
void *p1(void *arg)
{
    a1();
    /* send signal to the created thread */
    
    sem_post(sync_1);
    sem_wait(sync_2);
    a2();

}


void *p2(void *arg)
{
    sem_wait(sync_1);
    b1();
    /* wait for signal from main thread */
    
    sem_post(sync_2);
    b2();
}



void main () {
    pthread_t thread1, thread2;
    /* semaphore sync should be initialized by 0 */
    sync_1=sem_open("sync_1",O_CREAT,0644,0);
    sync_2=sem_open("sync_2",O_CREAT,0644,0);
    if (sem_init(sync_1, 0, 0) == -1 && sem_init(sync_2, 0, 0) == -1) {
        perror("Could not initialize mylock semaphore");
        exit(2);
    }
    if (pthread_create(&thread1, NULL, p1, NULL) < 0) {
        perror("Error: thread cannot be created");
        exit(1);
    }
    if (pthread_create(&thread2, NULL, p2, NULL) < 0) {
        perror("Error: thread cannot be created");
        exit(1);
    }
    /* wait for created thread to terminate */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    /* destroy semaphore sync */
    sem_destroy(sync_1);
    sem_destroy(sync_2);
    exit(0);
}

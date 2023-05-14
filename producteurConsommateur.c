#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define MAX_MESSAGE_LENGTH 100

char global_message[MAX_MESSAGE_LENGTH];
sem_t* sprod;
sem_t* scons;
int k;

//on écrit dans la variable en parametre un message
void Produire(char* message) {
    sprintf(message, "Message : %d", k++);
}

//on met le message en majuscule et on l'affiche
void Consommer(char* message) {
    for(int i = 0; message[i]; i++){
        message[i] = toupper(message[i]);
    }
    printf("%s\n", message);
}

//copie la variable en parametre dans la variable global
void Deposer(char* message) {
    strcpy(global_message, message);
}

//copie la variable en parametre dans la variable global
void Retirer(char* message) {
    strcpy(message, global_message);
}
//boucle infinie qui permet la synchronisation avec le consommateur
void* Production(void* arg) {
    while (1) {
        char message[MAX_MESSAGE_LENGTH];
        Produire(message);
        sem_wait(sprod);
        Deposer(message);
        sem_post(scons);
    }
    return NULL;
}

//boucle infinie qui permet la synchronisation avec le consommateur
void* Consommation(void* arg) {
    while (1) {
        char message[MAX_MESSAGE_LENGTH];
        sem_wait(scons);
        Retirer(message);
        sem_post(sprod);
        Consommer(message);
    }
    return NULL;
}

int main() {
    //on intitialise k à 0
    k=0;
    //On initialise les threads
    pthread_t prodThread, consThread;

    //on intialise le premier semaphore à 1 et le deuxieme à 0 
    sprod=sem_open("sprod",O_CREAT,0644,1);
    scons=sem_open("scons",O_CREAT,0644,0);

    //on creer nos deux thread avec les fonction Production et consommation respectivement
    pthread_create(&prodThread, NULL, Production, NULL);
    pthread_create(&consThread, NULL, Consommation, NULL);

    //on attend que les thread se termine
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    //on detruit les semaphore
    sem_destroy(sprod);
    sem_destroy(scons);

    return 0;
}
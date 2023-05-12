#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

/* Global variables */
char* message = NULL;
sem_t semDeposer, semRetirer;

/* Producteur */
/* Producteur */
/* Producteur */
void Produire()
{
    static int k = 0;
    k++;
    if (message != NULL) {
        free(message);
        message = NULL;
    }
    int size = snprintf(NULL, 0, "Message: %d", k);
    message = malloc(size + 1);
    sprintf(message, "Message: %d", k);
}

/* Consommateur */
void Consommer()
{
    printf("Message reçu : %s\n", message);
    // Mettre le message en majuscules (traitement)
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = message[i] - 32; // Convertir en majuscules
        }
    }
    printf("Message traité : %s\n", message);
    free(message);
    message = NULL;
}


/* Fonction du producteur */
void* Producteur(void* arg)
{
    while (1) {
        Produire();
        sem_wait(&semRetirer); // Attendre que le consommateur retire le message précédent
        sem_post(&semDeposer); // Indiquer au consommateur que le message est disponible
    }
    pthread_exit(NULL);
}

/* Fonction du consommateur */
void* Consommateur(void* arg)
{
    while (1) {
        sem_wait(&semDeposer); // Attendre que le producteur dépose un message
        Consommer();
        sem_post(&semRetirer); // Indiquer au producteur que le message a été traité
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threadProducteur, threadConsommateur;

    sem_init(&semDeposer, 0, 0);
    sem_init(&semRetirer, 0, 1);

    pthread_create(&threadProducteur, NULL, Producteur, NULL);
    pthread_create(&threadConsommateur, NULL, Consommateur, NULL);

    pthread_join(threadProducteur, NULL);
    pthread_join(threadConsommateur, NULL);

    sem_destroy(&semDeposer);
    sem_destroy(&semRetirer);

    return 0;
}

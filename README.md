# tp4_systeme
# Compte rendu tp3 système

Dans ce TP nous allons utiliser des sémaphores pour implanter un modèle producteur/

consommateur similaire à celui que vous avez vu en TD.

Question 1 : on corrige les erreurs!

Question 2 :

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b117605d-6487-448f-a906-05cfb2e2ee60/Untitled.png)

On initialise sem_1 = 0 et sem_2 = 0.

L’algorithme précédent est autobloquant car le processus 1  attend sem_2 et le processus 2 attend sem_1.

Voici la solution que je propose:

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f6d436b1-d826-471b-93a6-4f1822e6e7b0/Untitled.png)

Question 3:

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/afe5da0e-2d50-4d6e-9736-751ab382417b/Untitled.png)

Ce pseudo code garatie l’exclusion mutuelle car le mutex est initialisé à 1, ainsi il ne peut y avoir que un seul thread de lancé à la fois

Voici le résultat de ex2 corriger:

# Compte rendu tp3 système

Dans ce TP nous allons utiliser des sémaphores pour implanter un modèle producteur/

consommateur similaire à celui que vous avez vu en TD.

Question 1 : on corrige les erreurs!

Question 2 :

![Untitled](Compte%20rendu%20tp3%20syste%CC%80me%20eaa8169b170143e7b113605cb24e2147/Untitled.png)

On initialise sem_1 = 0 et sem_2 = 0.

L’algorithme précédent est autobloquant car le processus 1  attend sem_2 et le processus 2 attend sem_1.

Voici la solution que je propose:

![Untitled](Compte%20rendu%20tp3%20syste%CC%80me%20eaa8169b170143e7b113605cb24e2147/Untitled%201.png)

Question 3:

![Untitled](Compte%20rendu%20tp3%20syste%CC%80me%20eaa8169b170143e7b113605cb24e2147/Untitled%202.png)

Ce pseudo code garatie l’exclusion mutuelle car le mutex est initialisé à 1, ainsi il ne peut y avoir que un seul thread de lancé à la fois

Voici le résultat de ex2 corriger:

![Untitled](Compte%20rendu%20tp3%20syste%CC%80me%20eaa8169b170143e7b113605cb24e2147/Untitled%203.png)
***Pour la compilation du ce projet avec Mingw il faut utiliser les commandes suivantes:

	gcc -c fonction.c
	gcc -c main.c
	gcc main.o fonction.o -o jeuKalah.exe

***Explication du fonctionnement du jeu:

Aprés avoir faire la compilation du projet,un executable "jeu.exe" sera généré.En ouvrant cet exécutable,un menu
du jeu s'affiche:
	 Welcome to the Mancala Game
-------------------Menu du jeu--------------------
1-Jouer une nouvelle partie
2-Restaurer une partie
3-Comment Jouer?
4-Quitter le jeu
--------------------------------------------------
Si vous choisissez du jouer une nouvelle partie le jeu vous demande le nombre de boules que vous voulez placer
dans les cases du plateau mais avec des limitation bien sur:
--------------------------------------------------
choisir le nombre du boules pour initialiser les cases: 4 , 5 ou 6 : 4
--------------------------------------------------
Au cours du jeu,à chaque coup le plateau du jeu s'affiche avec le numéro du joueur qui doit jouer:

---------------Debut de la partie------------------

                     Player 1

kalah1   6     5     4     3     2     1
-------------------------------------------------
|    0|    4|    4|    4|    4|    4|    4|     |
       -----------------------------------
|     |    4|    4|    4|    4|    4|    4|    0|
-------------------------------------------------
         1     2     3     4     5     6   kalah2

                     Player 2
___________________________________________________
Player 1
choisissez une case entre 1 et 6 :



//les directives preprocesseurs:

#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

//-------------------------------------------------------------------------------

//le programme principale du jeu:
int main()
{
    int choix,choix1;
    do
    {
        choix=menu();//choix du menu
        if (choix==4) break;
        if (choix==1 || choix==2)//si l utilisateur veut jouer ou veut restaurer une partie
        {
            if (choix==1)
            {
                table *t=CreateTable();
                t=Init(t);
                turnGame(t,0);
                return 0;
            }
            else
            {
                table *t;
                t=restoreGame();
                if (t->stateGame!=1)//si il existe une sauvegarde d une partie en cours
                {
                    turnGame(t,1);
                    return 0;
                }
                else//s il n est existe pas
                {
                    printf("Desole,pas de sauvegarde en cours,veuillez commencer une nouvelle partie.\n");
                    choix1=1;//pour revenir au menu du jeu
                }
            }

        }
        if (choix==3)//si l utilisateur veut apprendre les regles du jeu
        {
            howPlay();
            printf("\n1-Revenir au menu du jeu\n2-Quitter le jeu\n");
            printf("--------------------------------------------------\n");
            printf("Votre choix: ");
            scanf("%d",&choix1);
            printf("________________________________________________________________________________________\n");
        }

    }while (choix1!=2);
    if (choix==4 || choix1==2)//si l utilisateur veut quitter le jeu
    {
        printf("\nFin du jeu\nAu revoir.\n\n");
        exit(EXIT_SUCCESS);
    }
}

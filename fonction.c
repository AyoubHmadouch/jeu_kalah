#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"


//----------------------------------------------------------------------------------------
//la fonction qui affiche les informations et le menu du jeu:

int menu()
{
    int choix;
    printf("           Welcome to the Mancala Game\n");
    printf("-------------------Menu du jeu--------------------\n");
    printf("1-Jouer une nouvelle partie\n2-Restaurer une partie\n3-Comment Jouer?\n4-Quitter le jeu\n");
    printf("--------------------------------------------------\n");
    printf("Entrer votre choix : ");
    scanf("%d",&choix);
    while (choix>4 || choix<1)
    {
        printf("Votre choix est errone,veuillez ressayer : ");
        scanf("%d",&choix);
    }
    return choix;
}
//----------------------------------------------------------------------------------------
//la fonction qui explique comment jouer le Mancala:

void howPlay()
{
    printf("________________________________________________________________________________________\n");
    printf("pour jouer le Mancala veuillez respecter les etapes suivantes:\n");
    printf("1-L objectif du jeu est de collecter autant de pions que possible avant que l autre joueur ne le fasse de son cote.\n");
    printf("2-Commencez par choisir le nombre de pierres dans chaque petit creux.\n");
    printf("3-Votre Mancala est le grand creux a votre droite.\n");
    printf("4-Choisissez une case valide de votre plateau.\n");
    printf("5-Jouez dans le sens inverse des aiguilles d une montre.\n");
    printf("6-Les joueurs peuvent mettre des pierres dans leur propre Mancala, mais pas dans le Mancala de leur adversaire.\n");
    printf("7-Si votre dernière pierre tombe dans votre Mancala, rejouez un tour.\n");
    printf("8-Si la derniere pierre que vous déposez se retrouve dans un creux vide de votre cote, gagnez cette pierre ainsi que celles du creux adverse place en face de celui-ci.\n");
    printf("9-Quand les six receptacles d un joueur sont completement vides, le jeu se termine.\n");
    printf("________________________________________________________________________________________\n");
}
//----------------------------------------------------------------------------------------
//la fonction qui fait l'allocation de la memoire pour la table :

table *CreateTable()
{
    int k;
    table *t=(table *)malloc(sizeof(table));
    printf("choisir le nombre du boules pour initialiser les cases: 4 , 5 ou 6 : ");
    scanf("%d",&k);
    t->ballNumber=k;
    while (k>MAXBOULES || k<MINBOULES)
    {
        printf("Votre choix est errone,veuillez ressayer : ");
        scanf("%d",&k);
        t->ballNumber=k;
    }
    return t;
}
//-----------------------------------------------------------------------------------------------
//la fonction qui fait l'initialisation des cases de la table:

table *Init(table *t)
{
    int i;
    if (t==NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (i=0;i<14;i++)
    {
        if (i==0 || i==7)
        {
            t->kalah[i]=0;
        }
        else
        {
            t->kalah[i]=t->ballNumber;
        }
    }

    return t;
}
//----------------------------------------------------------------------------
//la fonction qui genere un nombre aleatoire: 0 ou 1:
int randomNumber()
{
    srand(time(NULL));
    int Max=1,Min=0;
    int nbAleatoire=(rand()%(Max-Min+1))-Min;
    return nbAleatoire;
}
// la fonction qui fait la selection de joueur qui va commencer la partie au hasard:

int choixJoueur()
{
    float n;
    n=randomNumber();
    if (n==0)
    {
        return 1;//joueur 1
    }
    else
    {
        return 2;//joueur 2
    }
}
//----------------------------------------------------------------------------------------

//la fonction qui fait la mise a jour de la table apres un tour:

table *updateTable(table *t,int caseSelect1,int Nplayer)
{
    int count,i;
    int caseSelect=choiceCase(caseSelect1,Nplayer);
    if (t==NULL) exit(EXIT_FAILURE);
    count=t->kalah[caseSelect];
    t->kalah[caseSelect]=0;
    if (Nplayer==2)
    {
        do
        {
            for (i=caseSelect+1;i<14 && count!=0 ;i++)
            {
                t->kalah[i]+=1;
                count--;
            }
            caseSelect=i;
            if (count!=0)
            {
                for (i=1;i<14 && count!=0;i++)
                {
                    t->kalah[i]+=1;
                    count--;
                }
                caseSelect=i;
            }

        }while(count!=0);
        t->lastBall=i-1;//recuperer le numero de la derniere case d un coup
    }
    if (Nplayer==1)
    {
        do
        {
            for (i=caseSelect+1;i<14 && count!=0 ;i++)
            {
                t->kalah[i]+=1;
                count--;
            }
            caseSelect=i;
            if (count!=0)
            {
                for (i=0;i<14 && count!=0;i++)
                {
                    if (i!=7)
                    {
                        t->kalah[i]+=1;
                        count--;
                    }

                }
                caseSelect=i;
            }
        }while(count!=0);
        t->lastBall=i-1;//recuperer le numero de la derniere case du jeu
    }
    return t;
}
//---------------------------------------------------------------------------------
//la fonction qui teste l'etat du jeu :

void state_game(table *t)
{
    int state;
    state=check_zeros(t);
    if (state)
    {
        t->stateGame=1;//game over
    }
    else
    {
        t->stateGame=0;//game not over
    }
}

//la fonction qui teste l'existence des cases vides:

int check_zeros(table *t)
{
    int i,player1=1,player2=1;
    for (i=1;i<7;i++)
    {
        if (t->kalah[i]!=0)
        {
            player2=0;
            break;
        }
    }
    for (i=8;i<14;i++)
    {
        if (t->kalah[i]!=0)
        {
            player1=0;
            break;
        }
    }
    //la recuperation de tous les boules dans le kalah du gagnant:
    if (player2==1)
    {
        for (i=1;i<7;i++)
        {
            t->kalah[0]+=t->kalah[i];
        }
    }
    if (player1==1)
    {
        for (i=8;i<14;i++)
        {
            t->kalah[7]+=t->kalah[i];
        }
    }
    if (player1 || player2)
    {
        if (t->kalah[0]<t->kalah[7])
        {
            t->winPlayer=2;//le joueur 2 gagne
        }
        else
        {
            t->winPlayer=1;//le joueur 1 gagne
        }
        return 1;//game over
    }
    else
    {
        return 0;//game end
    }
}
//-----------------------------------------------------------------------------------------
//la fonction qui fait l'affichage de la table apres un tour:

void printTable(table *t)
{
    int b[14];
    memcpy(b,t->kalah,sizeof(t->kalah));
    printf("                     Player 1\n\n");
    printf("kalah1   6     5     4     3     2     1\n");
	printf("-------------------------------------------------\n");
	printf("|%5d|%5d|%5d|%5d|%5d|%5d|%5d|%5s|\n", b[0], b[13], b[12], b[11], b[10], b[9], b[8], "");
	printf("       -----------------------------------\n");
	printf("|%5s|%5d|%5d|%5d|%5d|%5d|%5d|%5d|\n", "", b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
	printf("-------------------------------------------------\n");
	printf("         1     2     3     4     5     6   kalah2\n\n");
	printf("                     Player 2\n");
}
//------------------------------------------------------------------------------------
//la fonction qui fait la convertion de choix du joueur en convention du jeu:

int choiceCase(int choise,int Nplayer)
{
    if (Nplayer==2)
    {
        return choise;
    }
    if (Nplayer==1)
    {
        return choise+7;
    }
}

//------------------------------------------------------------------------------------
//la fonction qui capture le contenu de la case de l adversaire:

void capture(table *t,int Nplayer)
{
    int Case;
    Case=t->lastBall;
    if (Nplayer==2 && Case<=6 && Case>=1 && t->kalah[Case]==1)
    {
        t->kalah[7]+=t->kalah[14-Case]+1;
        t->kalah[14-Case]=0;
        t->kalah[Case]=0;
    }
    if (Nplayer==1 && Case<=13 && Case>=8 && t->kalah[Case]==1)
    {
         t->kalah[0]+=t->kalah[14-Case]+1;
         t->kalah[14-Case]=0;
         t->kalah[Case]=0;
    }
}

//-----------------------------------------------------------------------------------
//la fonction qui teste si la derniere boule tombe dans la case Kalah
int caseKalah(table *t,int Nplayer)
{
    int lastCase;
    lastCase=t->lastBall;
    if (Nplayer==2 && lastCase==7)
    {
        return 1; //il doit rejouer
    }
    else if (Nplayer==1 && lastCase==0)
    {
        return 1;//il doit rejouer
    }
    else return 0;//le tour passe a l autre joueur
}

//------------------------------------------------------------------------------------
//la fonction qui fait la gestion d'une partie du jeu (Moteur du jeu):

void turnGame(table *t,int state)//state=0 si on veut commemncer une nouvelle partie,state=1 si on veut restaurer
{
    int Nplayer,Case,CaseConvertit,coup;
    if (state==0)
    {
        Nplayer=choixJoueur();//le choix au hasard du joueur qui va commence
        t->playerTurn=Nplayer;
        printf("---------------Debut de la partie------------------\n\n");
    }
    else
    {
        Nplayer=t->playerTurn;
    }
    printTable(t);//l affichage du la table
    printf("___________________________________________________\n");
    state_game(t);//Pour initilaliser l etat du jeu
    int flag=0;//variable sert a la gestion d une boucle
    while ( t->stateGame!=1 )//si le jeu n est encore termine
    {
        do
        {
             flag=0;
             saveGame(t);//pour sauvegarder le jeu pour la premiere fois
             printf("Player %d\n",Nplayer);
             printf("choisissez une case entre 1 et 6 : ");
             scanf("%d", &Case);
             while (Case<1 || Case>6)
             {
                printf("Il faut choisir une case entre 1 et 6 :");
                scanf("%d", &Case);
             }
             CaseConvertit=choiceCase(Case,Nplayer);
             while (t->kalah[CaseConvertit]==0)
             {
                printf("Il faut choisir une case non vide : ");
                scanf("%d", &Case);
                CaseConvertit=choiceCase(Case,Nplayer);
             }
             updateTable(t,Case,Nplayer);
             state_game(t);//sauvegader l etat du jeu

             if(t->stateGame==1)//pour gerer un cas particulier
             {
                 break;
             }

             if (t->kalah[t->lastBall]==1 && t->kalah[14-t->lastBall]!=0)
             {
                 if (Nplayer==2 && t->lastBall<=6 && t->lastBall>=1)
                 {
                     capture(t,Nplayer);
                     printf("Bravo,vous avez capturer les boules de ton adversaire.\n");
                 }
                 if (Nplayer==1 && t->lastBall>=8 && t->lastBall<=13)
                 {
                     capture(t,Nplayer);
                     printf("Bravo,vous avez capturer les boules de ton adversaire.\n");
                 }
             }
             printf("___________________________________________________\n");
             printTable(t);
             printf("___________________________________________________\n");
             printf("Player %d\n",Nplayer);
             printf("1-Valider le coup\n2-Annuler le coup\nVotre choix : ");
             scanf("%d",&coup);
             if (coup==2)
             {
                 t=restoreGame();
                 printf("___________________________________________________\n");
                 printTable(t);
                 printf("___________________________________________________\n");
                 flag=1;
             }
             else
             {
                printf("___________________________________________________\n");
             }
             saveGame(t);//pour memoriser la structure
        }while (caseKalah(t,Nplayer)==1 || flag==1);
        if (flag==1)
        {
            continue;
        }

        //changer le joueur:
        if (Nplayer==1)
        {
            t->playerTurn=2;
        }

        if (Nplayer==2)
        {
            t->playerTurn=1;
        }
        Nplayer=t->playerTurn;//le joueur qui va jouer apres
        saveGame(t);//pour memoriser la structure et le changement du joueur
    }
    if (t->stateGame==1) // la fin de la partie
    {
        printf("Bravo,le joueur %d a gagne la partie\n",t->winPlayer);
    }
}



//----------------------------------------------------------------------------------------
//les fonctions qui faire la gestion des sauvegardes et des restaurations du jeu:

//sauvgarder le jeu:
void saveGame(table *t)
{
    FILE *sauvegarde=NULL;
    sauvegarde=fopen("sauvegarder.txt","wb");
    if (sauvegarde==NULL)
    {
        exit(EXIT_FAILURE);
    }
    fwrite(t,sizeof(table),1,sauvegarde);
    fclose(sauvegarde);
}
//restaurer la sauvegarde:
table *restoreGame()
{
    table *t=(table *)malloc(sizeof(table));
    FILE *sauvegarde=NULL;
    sauvegarde=fopen("sauvegarder.txt","rb");
    if (sauvegarde==NULL)
    {
        exit(EXIT_FAILURE);
    }
    fread(t,sizeof(table),1,sauvegarde);
    fclose(sauvegarde);
    return t;
}

//---------------------------------------------------------------------------------------------











#ifndef headers
#define headers

//les constantes:

#define MAXBOULES 6
#define MINBOULES 4

//la structure du jeu:

typedef struct table
{
    int kalah[14];//case 0:playerKalah1,case 7:playerKalah2
    int stateGame;//stateGame=1 if game over,0 else
    int ballNumber;// le nombre du boules pour initialiser les cases
    int playerTurn;//=1si le tour du joueur 1,=2 sinon
    int lastBall;// le numero de la derniere case de chaque tour
    int winPlayer;//1 if player 1 win 2 else
}table;

//les prototypes des fonctions:

int menu();
void howPlay();
table *CreateTable();
table *Init(table *t);
int randomNumber();
int choixJoueur();
void printTable(table *t);
table *updateTable(table *t,int k,int Nj);
int check_zeros(table *t);
void state_game(table *t);
int choiceCase(int choise,int Nplayer);
void capture(table *t,int Nplayer);
int caseKalah(table *t,int Nplayer);
void turnGame(table *t,int state);
void saveGame(table *t);
table *restoreGame();



#endif

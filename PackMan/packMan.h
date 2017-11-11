#include<iostream>
#include<fstream>

//numeri dei fantasmi
#define NumFanstasmi 4 
//numero frutti da creare
#define NumeriFrutti 5
//probabilità creazione frutto
#define ProbCreazioneFrutto 15
using namespace std;
typedef unsigned int nat;

//codifica della struttura
enum simboliDir { SUCOD = 0, GIUCOD = 1, DESTRACOD = 2, SINISTRACOD = 3 };

// TIPI DI DATO
struct Personaggio
{
	bool visibile;
	nat riga;
	nat colonna;
	simboliDir direzione;
};

struct Frutto
{
	nat riga;
	nat colonna;
	nat punti;
	char simbolo;
	bool attivo;
};



// COSTANTI
/*costanti modificabili*/
//nome del file di default
const string MAZEFILE = "maze.cfg";

/*costanto non modificabili*/

//dimentione campo 
// Se si vuole usare il file maze.cfg fornito, size deve essere 15
const nat mazeSizeR = 15;
const nat mazeSizeC = 15;

/******FORMATTAZIONE TABELLA*****/
//simbli letti dal file
const char MUROFILE = '#'; // MURO
const char PALLINOFILE = '.';  // PALLINO
const char SPAZIOFILE = ' '; //SPAZIIO

							 //siboli usati nella matrice 
enum simboliMatrice { SPAZIO = 0, MURO = 1, PALLINO = 2 };

/*****CODIFICA******
MUROFILE -> MURO
PALLINOFILE -> PALLINO
SPAZIOFILE -> SPAZIOFILE
*******************/

/***FORMATTAZIONE DISPLAY****/

//costanti di movimento stampate su video
const char SU = 'v'; //su
const char GIU = '^';  //giu
const char DESTRA = '<';  //destra
const char SINISTRA = '>';//sinista

						  /*****CODIFICA******
						  SUCOD -> SU
						  GIUCOD -> GIU
						  DESTRACOD -> DESTRA
						  SINISTRACOD -> SINISTRA
						  *******************/


						  // FUNZIONI DEL GIOCO

						  /******FRUTTI CASUALI*******/
						  //crea un frutto casuale con diverso punteggio
						  //e funzionaleità il frutto resta attivo per un numero
						  //fissato passi. la creazione dei frutti è casuale.
						  //in base a quanto vale il punteggio dei frutti associo un 
						  //tempo di visibilità
void creaFrutto(Frutto &frut, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, nat punteggio, Personaggio pacman, Personaggio fantasmino[]);

/******Funzione per la festione dei fantasmi*****/
//setta inizialmente i fantasmini con valore casuali
void SettagioFanstasmini(simboliMatrice maze[][mazeSizeC], Personaggio fantasmino[], nat sizeRiga, nat sizeColonna);

//genera un numero casuale, se compreso in un range si cambia la direzione dei fantasmini.
//altrimenti prosegueo con quella precedente.
void cambiaDirezione(simboliMatrice maze[][mazeSizeC], Personaggio fantasmino[], nat SizeRiga, nat SizeColonna);

//data una direzione, muove il fantasmino nella direzione definita.
//se non si puo muovere in quella direzione allora si muove in una
//delle direzioni possibili.
void moveFantasmino(simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio fantasmino[]);


/****Gestione campo******/

//Inizializza leggendo schema da file (assumendolo corretto) e lo trasferisce 
//in una matrice codificando i caratteri con numeri
bool init(string nomeFile, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna);

// Legge input da tastiera
char input();

// Disegna lo stato corrente del gioco
void display(simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio pacman, nat punteggio, Personaggio fantasmino[], Frutto frut);


/*****Funzione gestione Pacman*****/

//setta dei valori predefiniti
void settaggioPacman(Personaggio &pacman);

// Esegue una mossa 
// Il pac-man viene modificato, quindi deve essere passato per riferimento
// Anche il labirinto viene modificato, ma e' un array 
// e gli array sono sempre "passati per riferimento"
void move(char wasd, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio &pacman, nat &punteggio, Frutto &frut);


/***Gestione fine partita****/
//in due casi puo terminare il gioco 1)se finiscono i punti 2 se il fantasmino ti mangia
int ControlloFinePartita(Personaggio pacman, Personaggio fantasmino[], nat punteggioAtt, Frutto frut);



#include "packMan.h"
#include <cstdlib>
#include <ctime>
//#define DEBUGINIT
//#define DEBUGCHECK
//#define DEBUGSETFANT
//#define DEBUGMOVE
//#define DEBUGcambiaDirezione
//#define DEBUGmoveFantasmino
//#define DEBUGSCreaFrutto

//variabile usata per il conteggio di fine partita
static nat palliniRimasti = 0;
//usata per la generazione dei frutti
static nat metaPallini;
//tempo di attivazione del frutto
static nat passi;

static bool sePossoMangiare = false;

//inizializzazione di pacman
void settaggioPacman(Personaggio &pacman)
{
	pacman.riga = 0;
	pacman.colonna = 0;
	pacman.direzione = DESTRACOD;
	pacman.visibile = true;
}

//Funzione di default
// FUNZIONE "PRIVATA", usata solo in pacman.cpp, senza prototipo in pacman.h
// Verifica validita' di una coppia di coordinate in un labirinto:
// - i valori devono essere entro i limiti di dimensioni [0,size)
// - il labirinto non deve contenere un muro in (X,Y)
bool check(int x, int y, simboliMatrice maze[][mazeSizeC], nat sizeRiga, nat sizeColonna)
{
#ifdef DEBUGCHECK 
	cout << "valore x:" << x << endl;
	cout << "valore y:" << y << endl;
	cout << "(x>=0 && x < sizeRiga):" << (x >= 0 && x < sizeRiga) << endl;
	cout << "y>=0 && y<sizeColonna" << (y >= 0 && y<sizeColonna) << endl;
	cout << "maze[x][y]!=MURO" << (maze[x][y] != MURO) << endl;
#endif
	//controllo che le coordinate passate non escano dal range
	//e che a quelle cordinate non corrisponda un muro in maze
	if ((x >= 0 && x < sizeRiga) && (y >= 0 && y<sizeColonna) && maze[x][y] != MURO)
		return true;
	return false;

}




//funzione che genera i frutti
void creaFrutto(Frutto &frut, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, nat punteggio, Personaggio pacman, Personaggio fantasmino[])
{
	//flag della creazione del frutto
	bool flag = true;
	//decide se posso creare il frutto
	nat creazione;
	//se c'è un frutto attivo allora non lo creo
	//se i pallini rimasti sono maggiori della meta non lo creo
	if (palliniRimasti<metaPallini && frut.attivo == false && sePossoMangiare == false)
	{
		srand(time(NULL));
		//genero un numero casuale, se il 
		//resto e minore di un certo valore creo il frutto
		creazione = rand() % ProbCreazioneFrutto;
		//probabilita per la creazine del frutto
		if (creazione<(ProbCreazioneFrutto / 2))
			do
			{
				flag = false;
				//genero la posizione del frutto
				frut.riga = rand() % SizeRiga;
				frut.colonna = rand() % SizeColonna;

#ifdef DEBUGSCreaFrutto
				cout << "riga: " << frut.riga;
				cout << "  colonna: " << frut.colonna << endl;
				cout << "  maze: " << maze[frut.riga][frut.colonna] << endl;
				cout << "  pacman.riga: " << pacman.riga;
				cout << "  pacman.colonna: " << pacman.colonna << endl;
				for (nat index = 0; index<NumFanstasmi; index++)
				{
					cout << "Fantasmino";
					cout << "fan.riga: " << fantasmino[index].riga;
					cout << "fan.colonna: " << fantasmino[index].colonna << endl;
				}
#endif

				//le coordinate del frutto devono corrispondere
				//ad uno spazio se messe in maze
				if (maze[frut.riga][frut.colonna] == SPAZIO)
					//se coordinate del frutto non devono corrispondere 
					//con quelle di pacman
					if (frut.riga != pacman.riga && frut.colonna != pacman.colonna)
					{
						flag = true;
						//le coordinate del frutto non devono corrispondere
						//con quelle dei fantasmi
						for (nat index = 0; index<NumFanstasmi && flag == true; index++)
							if (frut.riga == fantasmino[index].riga && frut.colonna == fantasmino[index].colonna)
								flag = false;
						//se tutto cio non accade
						//non creo il frutto, flag = false
					}
				//se ho superato i controlli allora 
				//posso creare il frutto flag = true
				if (flag == true)
				{
					//posso creare il frutto, casualmente decido
					//quale frutto creare
					switch (rand() % NumeriFrutti)
					{
					case 0:
						//frutto da 1000 punti
						frut.punti = 1000;
						frut.simbolo = '*';
						//tempo di attivazione del frutto
						passi = 5;
						break;
					case 1:
						//frutto da 300 punti
						frut.punti = 300;
						frut.simbolo = 'o';
						//tempo di attivazione del frutto
						passi = 10;
						break;
					case 2:
						//frutto da 100 punti
						frut.punti = 100;
						frut.simbolo = '@';
						//tempo di attivazione del frutto
						passi = 15;
						break;
					case 3:
						//frutto da 50 punti
						frut.punti = 50;
						frut.simbolo = '-';
						//tempo di attivazione del frutto
						passi = 20;
						break;
					case 4:
						//frutto da 100 punti
						//questo frutto ci permette di mangiare i 
						//fantasmi
						frut.punti = 100;
						frut.simbolo = 'W';
						passi = 20;
						break;

					}
					cout << "\n\nFRUTTO BONUS CREATO";
					//attivo la visibilita del frutto
					frut.attivo = true;
				}
			} while (flag == false);
	}

#ifdef DEBUGSCreaFrutto
	cout << "Frutto" << endl;
	cout << "riga: " << frut.riga;
	cout << "  colonna: " << frut.colonna;
	cout << "  simbolo: " << frut.simbolo;
	cout << "  punteggio: " << frut.punti;
	cout << "  attivo: " << frut.attivo;
	cout << "  palliniRimasti: " << palliniRimasti;
	cout << "  pallini meta: " << metaPallini;
	cout << endl;
#endif
}


//dato un numero compreso tra 0 e 3
//mi restituisce un carattere la direzione
char convertMouve(nat cod)
{
	switch (cod)
	{
	case 0:
		return SU;
	case 1:
		return GIU;
	case 2:
		return DESTRA;
	case 3:
		return SINISTRA;
	}
}


//dato un numero compreso tra 0 e 3
//mi restituisce il corrispondete codice simboloDir
simboliDir convertMouveFan(nat cod)
{
	switch (cod)
	{
	case 0:
		return SUCOD;
	case 1:
		return GIUCOD;
	case 2:
		return DESTRACOD;
	case 3:
		return SINISTRACOD;
	}
}

//controlla che gli indici passati non corrispondano ad un fantasma
bool controlloSeFanstasmi(nat i, nat j, Personaggio fantasmino[], nat MAX)
{
	for (nat indx = 0; indx < MAX; indx++)
		if (fantasmino[indx].riga == i && fantasmino[indx].colonna == j && fantasmino[indx].visibile == true)
			return true;
	return false;

}

//setti i vari parametri dei fantasmini in modo casuale 
void SettagioFanstasmini(simboliMatrice maze[][mazeSizeC], Personaggio fantasmino[], nat sizeRiga, nat sizeColonna)
{
	nat x, y;
	nat cont = 0;
	bool flag = true;
	srand(time(NULL));
	do
	{
		flag = true;
		//genero due numeri casuali compresi 
		//uno tra 0 e sizeRiga
		//due tra 0 e sizeColonna
		x = rand() % sizeRiga;
		y = rand() % sizeColonna;
		//controllo che ad un fantasma non sia gia 
		//data la posizione appena generata
		if (controlloSeFanstasmi(x, y, fantasmino, cont) == true)
			//se cosi fosse metto un flag a false il quale mi fa saltare if dopo
			flag = false;
		//se tutti i controlli non hanno avuto errori
		//e nella posizione non c'è ne il muro ne pacman
		//la salvo nel fantasmino
		if (maze[x][y] != MURO && x != 0 && y != 0 && flag == true)
		{
			fantasmino[cont].riga = x;//setto la riga
			fantasmino[cont].colonna = y;	//setto la colonna
			fantasmino[cont].direzione = convertMouveFan(rand() % NumFanstasmi); //setto la direzione
			fantasmino[cont].visibile = true; //setto la visibilità
			cont++;
		}
		//esco dal ciclo solo se ho settato tutti i fantasmini
	} while (cont < NumFanstasmi);

#ifdef DEBUGSETFANT 
	for (nat i = 0; i < NumFanstasmi; i++)
	{
		cout << "Fantasma " << i + 1 << endl;
		cout << "riga: " << fantasmino[i].riga;
		cout << "  colonna: " << fantasmino[i].colonna;
		cout << "  direzione: " << fantasmino[i].direzione;
		cout << "  visibile: " << fantasmino[i].visibile;
		cout << endl;
	}
#endif
}

//decide in modo casuale se cambiare la direzione o meno
void cambiaDirezione(simboliMatrice maze[][mazeSizeC], Personaggio fantasmino[], nat SizeRiga, nat SizeColonna)
{

	srand(time(NULL));
	//genero un numero casuale il quale mi dira
	//se cambiare o meno la direzione ai fantasmi
	float cambiaDir = (float)rand() / (float)RAND_MAX;
	simboliDir direzioneNuova;
	//se il valore generato è minore di
	//0.4 allora cambio la direzione
	if (cambiaDir<0.4)
	{
		//cambio la direzione a tutti e 4 i fantasmi
		//generando dei caratteri casuali
		for (nat i = 0; i < NumFanstasmi; i++)
		{
			srand(time(NULL));
			//controllo che la nuova direzione non
			//sia uguale a quella precedente
			//se è uguale ne calcolo un altra
			do {
				direzioneNuova = convertMouveFan(rand() % NumFanstasmi);
			} while (direzioneNuova == fantasmino[i].direzione);

#ifdef DEBUGcambiaDirezione
			cout << "Fantasma " << i + 1 << endl;
			cout << "dopo while " << endl;
			cout << "direzione nuova: " << direzioneNuova << endl;
			cout << "direzione vecchia: " << fantasmino[i].direzione << endl;
			cout << endl;
#endif		
			//setto la nuova direzione
			fantasmino[i].direzione = direzioneNuova;

#ifdef DEBUGcambiaDirezione
			cout << "dopo move " << endl;
			cout << "direzione : " << fantasmino[i].direzione << endl;
			cout << "riga: " << fantasmino[i].riga << endl;
			cout << "colonna: " << fantasmino[i].colonna << endl;
			cout << endl;
#endif	
		}
	}
}


//muove il fantasmino
void moveFantasmino(simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio fantasmino[])
{

	for (nat i = 0; i<NumFanstasmi; i++)
	{
		//controllo per uscire dalla nuova mossa
		bool flag = false;
		//forza l'uscita del cliclo		
		nat exit = 0;
#ifdef DEBUGmoveFantasmino
		cout << "fantasmino prima switch " << i + 1 << endl;
		cout << "direzione : " << fantasmino[i].direzione << endl;
		cout << "riga: " << fantasmino[i].riga << endl;
		cout << "colonna: " << fantasmino[i].colonna << endl;
		cout << endl;
#endif
		//finche non faccio una mossa sto nel while
		//esco che i fantasmini si sono mossi
		//per forza
		if (fantasmino[i].visibile == true)
		{
			while (flag == false)
			{
				switch (fantasmino[i].direzione)
				{
				case SUCOD:
					fantasmino[i].direzione = SUCOD;
					//se non mi posso muove allora vado al case dopo
					if (check(fantasmino[i].riga - 1, fantasmino[i].colonna, maze, SizeRiga, SizeColonna))
					{
						if (controlloSeFanstasmi(fantasmino[i].riga - 1, fantasmino[i].colonna, fantasmino, NumFanstasmi) == false)
						{
							fantasmino[i].riga--;
							flag = true;
							break;
						}
					}
					exit++;
					if (exit>4)
					{
						flag = true;
						break;
					}



				case SINISTRACOD:
					fantasmino[i].direzione = SINISTRACOD;
					//se non mi posso muove allora vado al case dopo
					if (check(fantasmino[i].riga, fantasmino[i].colonna - 1, maze, SizeRiga, SizeColonna))
					{
						if (controlloSeFanstasmi(fantasmino[i].riga, fantasmino[i].colonna - 1, fantasmino, NumFanstasmi) == false)
						{
							fantasmino[i].colonna--;
							flag = true;
							break;
						}
					}
					exit++;
					if (exit>4)
					{
						flag = true;
						break;
					}


				case DESTRACOD:
					fantasmino[i].direzione = DESTRACOD;
					//se non mi posso muove allora vado al case dopo
					if (check(fantasmino[i].riga, fantasmino[i].colonna + 1, maze, SizeRiga, SizeColonna))
					{
						if (controlloSeFanstasmi(fantasmino[i].riga, fantasmino[i].colonna + 1, fantasmino, NumFanstasmi) == false)
						{
							fantasmino[i].colonna++;
							flag = true;
							break;
						}
					}

					exit++;
					if (exit>4)
					{
						flag = true;
						break;
					}

				case GIUCOD:
					fantasmino[i].direzione = GIUCOD;
					//se non mi posso muove allora vado al case dopo
					if (check(fantasmino[i].riga + 1, fantasmino[i].colonna, maze, SizeRiga, SizeColonna))
					{
						if (controlloSeFanstasmi(fantasmino[i].riga + 1, fantasmino[i].colonna, fantasmino, NumFanstasmi) == false)
						{
							fantasmino[i].riga++;
							flag = true;
							break;
						}
					}
					exit++;
					if (exit>4)
					{
						flag = true;
						break;
					}

				default:
					//potrei incominciare lo switch a meta
					//qiundi se etrno qua, qualche case non è stato contemplato
					//in questo modo ricomincio da capo lo switch
					//dal primo caso
					fantasmino[i].direzione = SUCOD;
					flag = false;
				}
			}
		}
#ifdef DEBUGmoveFantasmino
		cout << "dopo switch " << endl;
		cout << "direzione : " << fantasmino[i].direzione << endl;
		cout << "riga: " << fantasmino[i].riga << endl;
		cout << "colonna: " << fantasmino[i].colonna << endl;
		cout << endl;
#endif
	}
}

//Contrrolla se il gioco termina
int ControlloFinePartita(Personaggio pacman, Personaggio fantasmino[], nat punteggioAtt, Frutto frut)
{	//se non ci sono piu puntini da mangiare hai visto ritorno 1
	if (palliniRimasti == 0)
		return 1;
	//se sei stato mangaito hai perso ritorno -1
	for (nat indx = 0; indx < NumFanstasmi; indx++)
		if (fantasmino[indx].riga == pacman.riga && fantasmino[indx].colonna == pacman.colonna && fantasmino[indx].visibile == true)
			if (frut.simbolo == 'W' && sePossoMangiare == true)
				//se posso mangiare un fanstasmino lo "cancello"
				fantasmino[indx].visibile = false;
			else
				return -1;
	//sei ancora in partita
	return 0;
}


// Legge lo schema del labirinto da un file con nome predefinito "maze.cfg"
// Restituisce false se il file non si trova
// Assume che il file contenga almeno size*size caratteri
bool init(string nomeFile, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna)
{
	ifstream fIn(nomeFile.c_str());
	char temp;
	// se c'e un errore in apertura
	//file interrompo il la funzione
	if (!fIn)
		return false;

	for (nat i = 0; i < SizeRiga; i++)
		for (nat j = 0; j< SizeColonna; j++)
		{
			//leggo i caratteri del file 
			//e li codifico con una codifica standard
			fIn >> temp;
			switch (temp)
			{
			case MUROFILE: //se muro
				maze[i][j] = MURO;
				break;
			case PALLINOFILE: //se punto
				maze[i][j] = PALLINO;
				palliniRimasti++;
				break;
			default: //se spazio 
				maze[i][j] = SPAZIO;
				break;
			}
			//forse inutile
			if (fIn.eof())//da controllare
				maze[i][j] = SPAZIO;

		}
	//calcolo per la genstione dei frutti
	metaPallini = palliniRimasti / 2;
	fIn.close();
#ifdef DEBUGINIT 
	cout << "Matrice codificata\n";
	for (nat i = 0; i < SizeRiga; i++)
	{
		for (nat j = 0; j< SizeColonna; j++)
			cout << maze[i][j];
		cout << "\n";
	}
	cout << "Pallini totali" << palliniRimasti;
	cout << "Pallini mexxo" << metaPallini;
#endif

	return true;

}

//Funzione default
// Legge e restituisce un carattere
char input()
{
	char cLetto;
	while (true)
	{
		cout << "digita un carattere:\n [q]:quit     [w]:su \n [a]=sinistra [s]=giu  [d]=destra : ";
		cin >> cLetto;
		cLetto = tolower(cLetto);
		//controllo che il carattere letto sia corretto
		if (cLetto == 'w' || cLetto == 'a' || cLetto == 's' || cLetto == 'd' || cLetto == 'q')
			return cLetto;
		cout << "Errore di inserimento...";
	}
}



//Funzione default
// Visualizza il labirinto con il personaggio e i fantasmini
void display(simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio pacman, nat punteggio, Personaggio fantasmino[], Frutto frut)
{
	cout << "\n";
	cout << "Punteggio attuale:" << punteggio << endl;
	//prima di stampare la matrice controllo
	//che in i,j non ci sia un fantasma o
	//pacman

	//per borsi esterni
	for (nat i = 0; i < SizeRiga + 2; i++)
		cout << "#";
	cout << "\n";

	for (nat i = 0; i < SizeRiga; i++)
	{
		//per borsi esterni
		cout << '#';
		for (nat j = 0; j< SizeColonna; j++)
		{	//se le cordinate corrispondi al fantasma stampo il fanstasmino
			if (controlloSeFanstasmi(i, j, fantasmino, NumFanstasmi) == true)
				if (sePossoMangiare == true)
					//se lo posso mangiare stampo W 
					cout << 'W';
				else
					//se non lo posso mangiare stampo M
					cout << 'M';
			else
				//se le coordinate corrispondono a pacman stampo Pacman
				if (pacman.riga == i && pacman.colonna == j)
					cout << convertMouve(pacman.direzione);
				else
					//se le coordinate corrispondono al frutto ed
					//è attivo lo stampo
					if (frut.riga == i && frut.colonna == j && frut.attivo == true)
						cout << frut.simbolo;
					else
						//altrienti stampo la tabella
						switch (maze[i][j])
						{
						case MURO:
							cout << MUROFILE;
							break;
						case PALLINO:
							cout << PALLINOFILE;
							break;
						case SPAZIO:
							cout << SPAZIOFILE;
							break;
						}
		}
		//per borsi esterni
		cout << '#';
		cout << "\n";
	}
	//per borsi esterni
	for (nat i = 0; i < SizeRiga + 2; i++)
		cout << "#";
	cout << "\n";
}



// Esegue mossa (se possibile), aggiornando personaggio e labirinto
// Dove si trova il personaggio, il puntino viene mangiato
void move(char wasd, simboliMatrice maze[][mazeSizeC], nat SizeRiga, nat SizeColonna, Personaggio &pacman, nat &punteggio, Frutto &frut)
{
#ifdef DEBUGMOVE
	cout << "wasd:" << wasd << endl;
#endif
	switch (wasd)
	{
	case 'w':
		if (check(pacman.riga - 1, pacman.colonna, maze, SizeRiga, SizeColonna))
			pacman.riga--;
		pacman.direzione = SUCOD;
		break;
	case 's':
		if (check(pacman.riga + 1, pacman.colonna, maze, SizeRiga, SizeColonna))
			pacman.riga++;
		pacman.direzione = GIUCOD;
		break;
	case 'a':
		if (check(pacman.riga, pacman.colonna - 1, maze, SizeRiga, SizeColonna))
			pacman.colonna--;
		pacman.direzione = SINISTRACOD;
		break;
	case 'd':
		if (check(pacman.riga, pacman.colonna + 1, maze, SizeRiga, SizeColonna))
			pacman.colonna++;
		pacman.direzione = DESTRACOD;
		break;
	}
	//se nella casella in cui sono andato c'era un pallino 
	//lo mangio e ci metto uno spazio
	//aggiorno il punteggio
	if (maze[pacman.riga][pacman.colonna] == PALLINO)
	{
		maze[pacman.riga][pacman.colonna] = SPAZIO;
		punteggio = punteggio + 10;
		palliniRimasti--;
	}

	if (pacman.riga == frut.riga && pacman.colonna == frut.colonna && frut.attivo == true)
	{

		punteggio = punteggio + frut.punti;
		frut.attivo = false;
		if (frut.simbolo == 'W')
		{//se mangio il frutto 
		 //reisetto il tempo a 20
			sePossoMangiare = true;
			passi = 20;
		}
	}
	//decremento il tempo
	passi--;
	if (passi == 0)
	{//se è finito il tempo disattivo 
	 //il frutto e il suo effetto
		sePossoMangiare = false;
		frut.attivo = false;
	}
}

// FINE FILE pacman.cpp

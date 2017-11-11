#include "packMan.h"
#include <string>
// Il programma principale inizializza il gioco e mostra lo stato iniziale,
// poi esegue il ciclo di interazione LEGGI - ESEGUI - MOSTRA RISULTATO
// finche' l'utente non inserisce q o Q



int main()
{
	// Qui si definiscono le variabili: stato del pac-man e del labirinto
	string nomeFile;
	//stampa il messaggio finale
	string finale;
	simboliMatrice maze[mazeSizeR][mazeSizeC];
	Frutto frut;

	Personaggio pacman;
	Personaggio fantasmino[NumFanstasmi];
	char cLetto;
	nat punteggio = 0;



	cout << "Digita il nome del file(digita 0 per file di default \"maze.cfg\" ): ";
	cin >> nomeFile;
	if (nomeFile == "0")
		nomeFile = MAZEFILE;



	if (!init(nomeFile, maze, mazeSizeR, mazeSizeC))
	{
		cout << "file errato";
		return 0;
	}


	frut.attivo = false;
	//settaggio pacman
	settaggioPacman(pacman);
	//settaggio fantasmini
	SettagioFanstasmini(maze, fantasmino, mazeSizeR, mazeSizeC);

	display(maze, mazeSizeR, mazeSizeC, pacman, punteggio, fantasmino, frut);


	do
	{
		cLetto = input();
		move(cLetto, maze, mazeSizeR, mazeSizeC, pacman, punteggio, frut);

		cambiaDirezione(maze, fantasmino, mazeSizeR, mazeSizeC);
		creaFrutto(frut, maze, mazeSizeR, mazeSizeC, punteggio, pacman, fantasmino);
		switch (ControlloFinePartita(pacman, fantasmino, punteggio, frut))
		{
		case -1:
			finale = "\n\nSEI STATO MANGIATO";
			cLetto = 'q';
			break;
		case 1:
			finale = "\n\n HAI VINTO LA PARTITA";
			cLetto = 'q';
			break;
		case 0:
			moveFantasmino(maze, mazeSizeR, mazeSizeC, fantasmino);
			if (ControlloFinePartita(pacman, fantasmino, punteggio, frut) == -1)
			{
				finale = "\n\nSEI STATO MANGIATO";
				cLetto = 'q';
			}
			break;
		}
		display(maze, mazeSizeR, mazeSizeC, pacman, punteggio, fantasmino, frut);
	} while (cLetto != 'q');
	cout << finale;
	cout << "\n\nPARTITA TERMINATA\n";
}


// FINE FILE main.cpp

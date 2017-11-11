#include<iostream>
#include<fstream>
#include<time.h>
#include <stdlib.h>
using namespace std;
#define MAX 15
/*
MAZE

',' = 1
'#' = 2

*/

void stampaFile(int a[][MAX]);

void creaMaze(int a[][MAX])
{
	int randxosx;//variabile che uso: 0 sx 1 dx
	int randmove;//quante colonne mi devo spostare(orizzontale)
	int qntvoltmove = (rand() % (MAX / 2) + 8);//indica il numero di righe dove andro' a creare i puntini
	int colonna = 0;//inizialmente a zero perche' il readme richiede che il pacman sia assegnato alle coordinate (0,0)
	int k = 0;//flag che indica la riga della matrice
	while (qntvoltmove >= 0 && qntvoltmove--)
	{
		randmove = (rand() % (MAX / 2) + 8);
		if (k == 0)//nel caso (0,0) 
		{
			//dx
			for (int i = 0; i<randmove && (colonna + i)<MAX; i++)
			{
				a[k][colonna + i] = 1;
				int mimuovo = (rand() % (3));
				if (mimuovo<2)//creo puntini verticali?
				{
					int randmove2 = (rand() % ((MAX / 2)) + 8);//indica il numero di volte in cui devo muovermi verticalmente
					int randxosx2 = (rand() % (2));//0 su o 1 giu
					if (randxosx2 == 0)	//su
						for (int i2 = 0; i2<randmove2 && (k - i2) >= 0; i2++)//creo dei puntini verso l'alto
						{
							a[k - i2][colonna + i] = 1;
						}
					else	//giu
					{
						for (int i2 = 0; i2<randmove2 && (k + i2)<MAX; i2++)//creo dei puntini verso il basso
						{
							a[k + i2][colonna + i] = 1;
						}
					}
				}
			}
		}
		colonna = (rand() % (MAX / 2) + 8);
		//scelgo se dx o sx
		randxosx = (rand() % (2));
		if (randxosx == 0)	//sx   mi sposto verso sinistra
			for (int i = 0; i<randmove && (colonna - i) >= 0; i++)
			{
				a[k][colonna - i] = 1;
				int mimuovo = (rand() % (3));
				if (mimuovo<2)//creo puntini verticali?
				{
					int randmove2 = (rand() % (4) + 4);//indica il numero di volte in cui devo muovermi verticalmente
					int randxosx2 = (rand() % (2));//0 su o 1 giu
					if (randxosx2 == 0)	//su
						for (int i2 = 0; i2<randmove2 && (k - i2) >= 0; i2++)//creo dei puntini verso l'alto
						{
							a[k - i2][colonna - i] = 1;
						}
					else
					{
						for (int i2 = 0; i2<randmove2 && (k + i2)<MAX; i2++)//creo dei puntini verso il basso
						{
							a[k + i2][colonna - i] = 1;
						}
					}
				}

			}
		else
		{	//dx   mi sposto verso destra
			for (int i = 0; i<randmove && (colonna + i)<MAX; i++)//indica il numero di volte in cui devo muovermi verticalmente
			{
				a[k][colonna + i] = 1;
				int mimuovo = (rand() % (3));
				if (mimuovo<2)//creo puntini verticali?
				{
					int randmove2 = (rand() % (4) + 4);//qnt righe di righe
					int randxosx2 = (rand() % (2));//0 su o 1 giu
					if (randxosx2 == 0)	//su
						for (int i2 = 0; i2<randmove2 && (k - i2) >= 0; i2++)//creo dei puntini verso l'alto
						{
							a[k - i2][colonna + i] = 1;
						}
					else
					{
						for (int i2 = 0; i2<randmove2 && (k + i2)<MAX; i2++)//creo dei puntini verso il basso
						{
							a[k + i2][colonna + i] = 1;
						}
					}
				}
			}
		}

		k++;
	}

}

int main()
{
	int a[MAX][MAX];
	srand(time(NULL));
	for (int i = 0; i<MAX; i++)
		for (int j = 0; j<MAX; j++)
			a[i][j] = 2;
	creaMaze(a);
	stampaFile(a);
}

void stampaFile(int a[][MAX])
{
	ofstream fout;
	fout.open("../PackMan/maze11.cfg");
	for (int i = 0; i<MAX; i++)
	{
		for (int j = 0; j<MAX; j++)
		{
			if (a[i][j] == 1)
				fout << ".";
			else
				fout << "#";
		}
		fout << endl;
	}
}







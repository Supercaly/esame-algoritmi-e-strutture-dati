/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di main*/

/*librerie standard*/
#include <stdio.h>
#include <stdlib.h>
/*librerie personali*/
#include "grafo.h"				/*libreria per l'acquisizione dati*/
#include "ordinamento.h"	/*libreria per le ricerche*/
#include "statistiche.h"	/*libreria delle statistiche*/
/*macro che segnala eventuali errori nel menu*/
#define ERRORE_3(grafo_p)											 \
if (grafo_p == NULL)													 \
{																							 \
	printf("Il grafo è vuoto si consiglia di "); \
	printf("eseguire prima l'operazione 1.\n");	 \
}

/*dichiarazione delle funzioni*/
int menu(void);

/*definizione della funzione main*/
int main(void)
{
	vertice_grafo_t *grafo_p = NULL;
	grafo_t app_p;
	int operazione;

	do
	{
		/*stampa il menu di scelta*/
		operazione = menu();

		switch (operazione)
		{
			case 1:
				/*prende i dati da file*/
				app_p = prendi_file(&grafo_p);
				break;
			case 2:
				/*visita il ampiezza*/
				ERRORE_3(grafo_p);
				avvia_visita_grafo_amp(grafo_p);
				break;
			case 3:
				/*visita in profondità*/
				ERRORE_3(grafo_p);
				avvia_visita_grafo_prof(grafo_p);
				break;
			case 4:
				/*calcola le statistiche*/
				ERRORE_3(grafo_p);
				calcola_dati(grafo_p, app_p);
				break;
			case 5:
				/*esce dal programma*/
				break;
		}
	}
	while(operazione != 5);

	return 0;
}

/*
* Stampa a schermo il menu di scelta delle operazioni,
* attende un numero come risposta e segnala errore nel
* caso il numero non sia nell'elenco delle scelte.
*/
int menu(void)
{
	int operazione,
			rimosso,
			controllo;

		printf("\n\t\tMENU'\n");
		printf("\n-------------------------");
		printf("---------------------------\n");
		printf(" Quale operazione compiere?\n");
		printf("1. Prendi dati da file 'grafo.txt'\n");
		printf("2. Visita in ampiezza\n");
		printf("3. Visita in profondità\n");
		printf("4. Calcola statistiche sui pesi ");
		printf("degli archi del grafo\n");
		printf("5. Esci\n");
		printf("-------------------------");
		printf("---------------------------\n");

	do
	{
		controllo = scanf("%d", &operazione);
		if ((controllo != 1) || (operazione < 1 || operazione > 5))
		{
			printf("Attenzione! Tasto non valido\n");
			do
			rimosso = getchar();
			while (rimosso != '\n');
		}
	}
	while ((controllo != 1) || (operazione < 1 || operazione > 5));

	return operazione;
}

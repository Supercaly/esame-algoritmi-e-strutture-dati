/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di libreria 'grafo.c'*/

#include <stdio.h>
#include <stdlib.h>
#define FILE_GRAFO "grafo.txt" /*file da cui acquisire i dati del grafo*/
/*macro che definisce la dimensione massima degli array d'appoggio*/
#define DIM_MAX(tot) (tot * (tot - 1))
/*macro che segnalano la presenza di errori durante l'acquisizione del file*/
#define ERRORE_1(cont, err, arg)								 \
{																							   \
	if (cont != arg)															 \
	{																						   \
		err = 1;																		 \
	}																							 \
}
#define ERRORE_2(err)														 \
{																								 \
	if (err == 1)																	 \
	{																						   \
		printf("Attenzione! Sembrerebbe esserci ");  \
		printf("qualcosa che non va con il file\n"); \
		}																						 \
}
/****************/
/*strutture dati*/
/****************/
/*
* Definizione del tipo di dato 'colore' da utilizzare nella BFS.
* i colori sono: bianco (vertice mai visitato), grigio (vertice
* con vertici adiacenti ancora bianchi), nero (vertice con vertici
* adiacenti tutti già visitati).
*/
typedef enum {bianco, grigio, nero} colore_t;
/*
* Lista primaria.
*/
typedef struct vertice_grafo
{
	int valore;														/*valore secondo cui è ordinata la lista*/
	struct vertice_grafo *vertice_succ_p; /*puntatore all'elemento successivo*/
	struct arco_grafo *lista_archi_p;     /*puntatore al primo elemento della lista degli archi*/
	colore_t colore;											/*colore del vertice(per BFS e DFS)*/
	int distanza,													/*distanza dal vertice di partenza (per BFS)*/
			inizio,														/*inizio (per DFS)*/
			fine;															/*fine (per DFS)*/
	struct vertice_grafo *padre_p;				/*puntatore al vertice padre (per BFS e DFS)*/
} vertice_grafo_t;
/*
* Lista secondaria associata ad un vertice.
*/
typedef struct arco_grafo
{
	double peso;													 /*peso dell'arco tra i due vertici*/
	struct vertice_grafo *vertice_adiac_p; /*puntatore al secondo vertice dell'arco*/
	struct arco_grafo *arco_succ_p;				 /*puntatore all'arco successivo*/
} arco_grafo_t;
/*
* Struttura di appoggio.
*/
typedef struct
{
	int	vert_tot,		/*vertici totali*/
			tot_vert,		/*mantiene la dimensione degli array tra i loop*/
			*vert_coll,	/*[array] vertici collegati ad ogni vertice*/
			*vert2;			/*[array] secondo vertice*/
	double *peso;		/*[array] peso dell'arco*/
} grafo_t;

/******************************/
/*dichiarazione delle funzioni*/
/******************************/
grafo_t prendi_file(vertice_grafo_t **);

grafo_t prendi_dati(FILE 					 *,
										vertice_grafo_t **);

int inserisci_in_lista_primaria(vertice_grafo_t **,
																int 						);

int inserisci_in_lista_secondaria(arco_grafo_t 		**,
																	vertice_grafo_t **,
																  double			    );

vertice_grafo_t *cerca_in_lista(vertice_grafo_t *,
															 	int						 	);
/****************************/
/*definizione delle funzioni*/
/****************************/
/*acquisisci i dati da file*/
/*
* Apre il file in lettura "r" ed esegue la funzione
* che acquisisce i dati e li mette all'iterno della struttura;
* nel caso in cui nessun file si chiami come il contenuto
* della costante FILE_GRAFO segnala l'errore.
*/
grafo_t prendi_file (vertice_grafo_t **valore)
{
	grafo_t app_p;	/*variabile della struttura grafo_t*/
	FILE * file;		/*variabile del file grafo.txt*/

	/*apro il file in sola lettura*/
  file = fopen(FILE_GRAFO, "r");

	/*se il file esiste avvia l'acquisizione normalmente*/
	if(file != NULL)
	{
		/*corpo centrale dell'acquisizione*/
		app_p = prendi_dati(file, valore);
		/*chiude il file*/
		fclose(file);
	}
	/*altrimenti segna un errore*/
	else
	{
		perror("ERROR");
		printf("Per terminare il programma digitare 'Ctrl-c'");
	}
	return app_p;
}
/*
* Inizialmente si acquisiscono dal file tutti i valori che vengono poi messi
* dentro degli array specifici, poi tutti i dati sono inseriti, tramite gli
* algoritmi di inserimento nelle liste, nella lista di adiacenza che definisce
* il grafo.
*/
grafo_t prendi_dati(FILE *file, vertice_grafo_t **grafo_p)
{
	grafo_t app_p;	/*struttura d'appoggio da inserire nella lista*/
	app_p.tot_vert = 0; /*tot vert è inizializzato a 0*/
	vertice_grafo_t *testa_sec_p, /*una copia della testa*/
	 								*v_adiac_p;			/*elemento cercato nella lista*/
	int	vert1; 			/*primo vertice (variabile temporanea)*/
	int i,		 			/*contatore loop di carica esterno e secondo loop*/
			j,		 			/*contatore loop di carica interno*/
			controllo,	/*controllo delle fscanf*/
			errore = 0;	/*segnala la presenza di errori*/

	/*prende il numero totale dei vertici*/
	controllo = fscanf(file, "%d", &app_p.vert_tot);
	ERRORE_1(controllo, errore, 1);

	/*allocazione dinamica degli array della struttura*/
	app_p.vert_coll = (int *)calloc(app_p.vert_tot, sizeof(int));
	app_p.vert2 = (int *)calloc(DIM_MAX(app_p.vert_tot), sizeof(int));
	app_p.peso = (double *)calloc(DIM_MAX(app_p.vert_tot), sizeof(double));

	/*loop che carica i valori negli array*/
	for(i = 0; (i < app_p.vert_tot); i++)
	{
		controllo = fscanf(file, "%d", &app_p.vert_coll[i]);
		ERRORE_1(controllo, errore, 1);
		for(j = 0; (j < app_p.vert_coll[i]); j++, app_p.tot_vert++)
		{
			controllo = fscanf(file, "%d %d %lf",
			       						 &vert1,
						 					 	 &app_p.vert2[app_p.tot_vert],
						  				 	 &app_p.peso[app_p.tot_vert]);
			ERRORE_1(controllo, errore, 3);
		}
	}
	/*se nel loop di carica c'erano errori li segnala*/
	ERRORE_2(errore);

 	/*azzero nuovamente tot_vert*/
	app_p.tot_vert = 0;
	/*inserisco i dati degli array nella lista di adiacenza*/
	/*creo la lista primaria*/
	for (i = 0; i < app_p.vert_tot; i++)
		inserisci_in_lista_primaria(grafo_p,
											  				i+1);
	/*la copia diventa uguale alla lista primaria appena creata*/
	testa_sec_p = *grafo_p;
	/*creo la lista secondaria*/
	for (i = 0; i < app_p.vert_tot; i++)
	{
		for (j = 0; j < app_p.vert_coll[i]; j++)
		{
		v_adiac_p = cerca_in_lista(*grafo_p, app_p.vert2[j + app_p.tot_vert]);
		inserisci_in_lista_secondaria(&testa_sec_p->lista_archi_p,
																	&v_adiac_p, app_p.peso[j + app_p.tot_vert]);
		}
		testa_sec_p = testa_sec_p->vertice_succ_p;
		app_p.tot_vert += app_p.vert_coll[i];
	}

	if (errore == 0)
		printf("Acquisizione avvenuta con successo\n");
	return app_p;
}

/*inserisce un elemento nella lista primaria*/
/*
* Partendo dalla testa della lista si scorrono tutti gli elementi
* fino a trovare la posizione in cui inserire l'elemento. Si alloca
* spazio per l'elemento e gli si attribuiscono valore e puntatore a
* elemento successivo.
*/
int inserisci_in_lista_primaria(vertice_grafo_t **testa_p,
																int 						valore)
{
	int inserito;
	vertice_grafo_t *corr_p,
									*prec_p,
									*nuovo_p;

	for (corr_p = prec_p = *testa_p;
		 	 ((corr_p != NULL) && (corr_p->valore < valore));
			 prec_p = corr_p, corr_p = corr_p->vertice_succ_p);
	if ((corr_p != NULL) && (corr_p->valore == valore))
		inserito = 0;
	else
	{
		inserito = 1;
		nuovo_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
		nuovo_p->valore = valore;
		nuovo_p->vertice_succ_p = corr_p;
		if (corr_p == *testa_p)
			*testa_p = nuovo_p;
		else
			prec_p->vertice_succ_p = nuovo_p;
	}
	return inserito;
}

/*inserisce un elemento nella lista secondaria*/
/*
* Partendo dalla testa si scorrono tutti gli elementi fino
* ad arrivare alla fine (in modo da inserire il nuovo elemento
* sempre per ultimo); in seguito si alloca memoria per il nuovo
* elemento e gli si da il peso, il puntatore al vertice a cui
* è collegato l'arco e il puntatore all'arco successivo.
*/
int inserisci_in_lista_secondaria(arco_grafo_t    **testa_p,
																	vertice_grafo_t **v_adiac_p,
																  double 			  	peso)
{
	int inserito;
	arco_grafo_t *corr_p,
							 *prec_p,
							 *nuovo_p;

	for (corr_p = prec_p = *testa_p;
	     (corr_p != NULL);
		 	 prec_p = corr_p, corr_p = corr_p->arco_succ_p);
	if ((corr_p != NULL) && (corr_p->peso == peso))
		inserito = 0;
	else
	{
		inserito = 1;
		nuovo_p = (arco_grafo_t *)malloc(sizeof(arco_grafo_t));
		nuovo_p->peso = peso;
		nuovo_p->arco_succ_p = corr_p;
		nuovo_p->vertice_adiac_p = *v_adiac_p;
		if (corr_p == *testa_p)
			*testa_p = nuovo_p;
		else
			prec_p->arco_succ_p = nuovo_p;
	}
	return inserito;
}

/*cerca un elemento nella lista*/
/*
* Scorre tutta la lista fino a quando non trova il valore cercato
* poi ne restituisce l'indirizzo.
*/
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
																int							valore)
{
	vertice_grafo_t *elem_p;

	for (elem_p = testa_p;
			 ((elem_p != NULL) && (elem_p->valore != valore));
			 elem_p = elem_p->vertice_succ_p);

	return elem_p;
}

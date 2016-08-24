/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di libreria 'ordinamento.c'*/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
/****************/
/*strutture dati*/
/****************/
/*
* Struttura coda per la ricerca in ampiezza.
*/
typedef struct elem_lista_vertici
{
	vertice_grafo_t *valore;
	struct elem_lista_vertici *succ_p;
} elem_lista_vertici_t;

/******************************/
/*dichiarazione delle funzioni*/
/******************************/

void avvia_visita_grafo_amp(vertice_grafo_t *);

void visita_grafo_amp(vertice_grafo_t *);

void avvia_visita_grafo_prof(vertice_grafo_t *grafo_p);

void visita_grafo_prof(vertice_grafo_t *vertice_p,
											 int 						 *tempo);

void metti_in_coda(elem_lista_vertici_t **,
									 elem_lista_vertici_t **,
								 	 vertice_grafo_t 			*  );

elem_lista_vertici_t *togli_da_coda(elem_lista_vertici_t **,
 																		elem_lista_vertici_t **);

void elabora(int);

/****************************/
/*definizione delle funzioni*/
/****************************/
/*avvia la visia in ampiezza BFS*/
void avvia_visita_grafo_amp(vertice_grafo_t *grafo_p)
{
	vertice_grafo_t *vertice_p;

	for (vertice_p = grafo_p; vertice_p != NULL; vertice_p = vertice_p->vertice_succ_p)
	{
		vertice_p->colore = bianco;
		vertice_p->distanza = -1;
		vertice_p->padre_p = NULL;
	}
	for (vertice_p = grafo_p; vertice_p != NULL; vertice_p = vertice_p->vertice_succ_p)
	{
		if (vertice_p->colore == bianco)
		{
			visita_grafo_amp(vertice_p);
		}
	}
}

/*corpo centrale della visita BFS*/
void visita_grafo_amp(vertice_grafo_t *vertice_partenza_p)
{
	vertice_grafo_t *vertice_p;
	arco_grafo_t *arco_p;
	elem_lista_vertici_t *uscita_p,
											 *ingresso_p;

	vertice_partenza_p->colore = grigio;
	vertice_partenza_p->distanza = 0;
	uscita_p = ingresso_p = NULL;
	metti_in_coda(&uscita_p,
  							&ingresso_p,
								vertice_partenza_p);
	while (uscita_p != NULL)
	{
		vertice_p = togli_da_coda(&uscita_p,
															&ingresso_p)->valore;
		/*elaboro il vertice su cui mi trovo*/
	  elabora(vertice_p->valore);
		for (arco_p = vertice_p->lista_archi_p;
			 	 arco_p != NULL;
				 arco_p = arco_p->arco_succ_p)
			if (arco_p->vertice_adiac_p->colore == bianco)
			{
					arco_p->vertice_adiac_p->colore = grigio;
					arco_p->vertice_adiac_p->distanza = vertice_p->distanza + 1;
					arco_p->vertice_adiac_p->padre_p = vertice_p;
					metti_in_coda(&uscita_p,
												&ingresso_p,
												arco_p->vertice_adiac_p);
			}
			vertice_p->colore = nero;
	}
}
/*inserisce un elemento nella coda*/
void metti_in_coda(elem_lista_vertici_t **uscita_p,
									 elem_lista_vertici_t **ingresso_p,
								 	 vertice_grafo_t *valore)
{
	elem_lista_vertici_t *nuovo_p;

	nuovo_p = (elem_lista_vertici_t *)malloc(sizeof(elem_lista_vertici_t));
	nuovo_p->valore = valore;
	nuovo_p->succ_p = NULL;
	if (*ingresso_p != NULL)
		(*ingresso_p)->succ_p = nuovo_p;
	else
		*uscita_p = nuovo_p;
	*ingresso_p = nuovo_p;
}
/*rimuove un elemento dalla coda*/
elem_lista_vertici_t *togli_da_coda(elem_lista_vertici_t **uscita_p,
																		elem_lista_vertici_t **ingresso_p)
{
	elem_lista_vertici_t *elem_p;

	elem_p = *uscita_p;
	if (*uscita_p != NULL)
	{
		*uscita_p = (*uscita_p)->succ_p;
		if (*uscita_p == NULL)
			*ingresso_p = NULL;
	}
	return elem_p;
}

void elabora(int valore)
{
	printf("vertice numero: %d\n", valore);
}

/*Avvia la visita in profondità DFS*/
void avvia_visita_grafo_prof(vertice_grafo_t *grafo_p)
{
	vertice_grafo_t *vertice_p;
	int tempo;

	for (vertice_p = grafo_p;
			 (vertice_p != NULL);
			 vertice_p = vertice_p->vertice_succ_p)
	{
		vertice_p->colore = bianco;
		vertice_p->inizio = vertice_p->fine = -1;
		vertice_p->padre_p = NULL;
	}
	for (vertice_p = grafo_p, tempo = 0;
			 (vertice_p != NULL);
		 	 vertice_p = vertice_p->vertice_succ_p)
		if (vertice_p->colore == bianco)
			visita_grafo_prof(vertice_p,
												&tempo);
}

/*Corpo centrale della DFS*/
void visita_grafo_prof(vertice_grafo_t *vertice_p,
											 int 						 *tempo)
{
	arco_grafo_t *arco_p;

	vertice_p->colore = grigio;
	vertice_p->inizio = ++(*tempo);
	elabora(vertice_p->valore);
	for (arco_p = vertice_p->lista_archi_p;
			 (arco_p != NULL);
		 	 arco_p = arco_p->arco_succ_p)
	 if (arco_p->vertice_adiac_p->colore == bianco)
	 {
		 arco_p->vertice_adiac_p->padre_p = vertice_p;
		 visita_grafo_prof(arco_p->vertice_adiac_p,
		 									 tempo);
	 }
	vertice_p->colore = nero;
	vertice_p->fine = ++(*tempo);
}

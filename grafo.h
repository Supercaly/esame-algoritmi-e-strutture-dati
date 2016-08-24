/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di libreria 'grafo.h'*/

/*****************************/
/*struttura dati da esportare*/
/*****************************/
/*definizione del campo colore*/
typedef enum {bianco, grigio, nero} colore_t;
/*lista primaria*/
typedef struct vertice_grafo
{
	int valore;
	struct vertice_grafo *vertice_succ_p;
	struct arco_grafo *lista_archi_p;
	colore_t colore;
	int distanza,
			inizio,
			fine;
	struct vertice_grafo *padre_p;
} vertice_grafo_t;
/*lista secondaria associata ad un vertice*/
typedef struct arco_grafo
{
	double peso;
	struct vertice_grafo *vertice_adiac_p;
	struct arco_grafo *arco_succ_p;
} arco_grafo_t;
/*struttura d'appoggio*/
typedef struct
{
	int	vert_tot,
			tot_vert,
			*vert_coll,
			*vert2;
	double *peso;
} grafo_t;

/*********************************************/
/*ridichiarazione delle funzioni da esportare*/
/*********************************************/
extern grafo_t prendi_file(vertice_grafo_t **);

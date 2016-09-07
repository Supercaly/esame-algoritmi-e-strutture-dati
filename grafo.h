/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di libreria 'grafo.h'*/

/*****************************/
/*struttura dati da esportare*/
/*****************************/
/*
* definizione del campo colore
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

/*********************************************/
/*ridichiarazione delle funzioni da esportare*/
/*********************************************/
extern grafo_t prendi_file(vertice_grafo_t **);

/*
* Progetto di Algoritmi e Strutture dati sessione autunnale 2015/2016
* di Lorenzo Calisti matricola: 271250 email: l.calisti@campus.uniurb.it
*/
/*File di libreria 'statistiche.c'*/

#include <stdio.h>
#include "grafo.h"

/******************************/
/*Dichiarazione delle funzioni*/
/******************************/
void calcola_dati(vertice_grafo_t *,
                  grafo_t         );
void calcola_max_min(vertice_grafo_t *,
                     double          *,
                     double          *);
void calcola_media(vertice_grafo_t *,
                   double          *);
void calcola_mediana(double          *,
                     grafo_t         );
void quicksort(double *,
               int     ,
               int     );

/****************************/
/*Definizione delle finzioni*/
/****************************/
/*
* Alla funzione è passato il primo elemento della lista
* di adiacenza e con quello invoca le altre funzioni per
* calcolare le statistiche, infine stampa a schermo i
* valori ottenuti dal calcolo.
*/
void calcola_dati(vertice_grafo_t *grafo_p, grafo_t appoggio_p)
{
  double max,
         min,
         media,
         mediana;

  if (grafo_p != NULL)
  {
    /*calcola massimo e minimo*/
    calcola_max_min(grafo_p, &max, &min);
    calcola_media(grafo_p, &media);
    calcola_mediana(&mediana, appoggio_p);
    /*stampa i valori calcolati*/
    printf("Valori del peso:\n");
    printf("  Massimo: %.2f\n", max);
    printf("  Minimo:  %.2f\n", min);
    printf("  Media:   %.2f\n", media);
    printf("  Mediana: %.2f\n", mediana);
  }
}

/*calcola massimo e minimo*/
/*
* Alla funzione è passato il primo elemento della
* lista di adiacenza e i puntatori ai valori max e min;
* la funzione scorre tutta la lista di adiacenza e per
* ogni elemento verifica se è il massimo o il minimo,
* aggiornando la variabile apposita nel caso.
*/
void calcola_max_min(vertice_grafo_t *grafo_p,
                     double          *max,
                     double          *min)
{
  vertice_grafo_t *valore_p;
  arco_grafo_t *arco_p;

  valore_p = grafo_p;
  *max = valore_p->lista_archi_p->peso;
  *min = valore_p->lista_archi_p->peso;

  /*scorro la lista di adiacenza*/
  for (;
      (valore_p != NULL);
      valore_p = valore_p->vertice_succ_p)
  {
    for (arco_p = valore_p->lista_archi_p;
        (arco_p != NULL);
        arco_p = arco_p->arco_succ_p)
    {
      /*aggiorno le variabili max e min*/
      if (arco_p->peso > *max)
        *max = arco_p->peso;
      if (arco_p->peso < *min)
        *min = arco_p->peso;
    }
  }
}
/*calcola media*/
/*
* Alla funzione è passato il primo elemento della lista di
* adiacenza e il puntatore alla mediana; la funzione scorre
* tutta la lista di adiacenza sommando tutti i valori dei pesi
* e aggiornando il numero dei vertici, infine divide la somma
* totale per il numero dei vertici.
*/
void calcola_media(vertice_grafo_t *grafo_p, double *media)
{
  vertice_grafo_t *valore_p;
  arco_grafo_t *arco_p;
  int n_tot = 0;

  /*scorro la lista di adiacenza*/
  for (valore_p = grafo_p;
      (valore_p != NULL);
      valore_p = valore_p->vertice_succ_p)
  {
    for (arco_p = valore_p->lista_archi_p;
        (arco_p != NULL);
        arco_p = arco_p->arco_succ_p)
    {
      *media += arco_p->peso;
      n_tot++;
    }
  }
  *media /= n_tot;
}
/*calcola la mediana*/
/*
* Alla finzione è passato il primo elemento della lista di adiacenza,
* il puntatore a mediana e una variabile di tipo 'grafo_t' contenente
* il numero di vertici totali, l'array con tutti i pesi, ecc... generata
* durante l'acquisizione da file. Inizialmente si setta array = all'array
* dei pesi e n = al numero totale di vertici; si invoca il quick sort per
* ottenere, infine, la mediana data dall'elemento n/2 dell'array ordinato.
*/
void calcola_mediana(double *mediana, grafo_t appoggio_p)
{
  double *array;
  int n;

  array = appoggio_p.peso;
  n = appoggio_p.tot_vert;

  /*ordina_array(array, n);*/
  quicksort(array, 0, n - 1);
  /*calcola la mediana*/
  *mediana = array[n / 2];
}
/*algoritmo di quick sort*/
/*
* Utilizza un pivot e una variabile temporanea per ordinare
* tutti gli elemnti dell'array in modo ricorsivo
*/
void quicksort(double *array, int sx, int dx)
{
  double pivot,
         tmp;
  int i, j;

  for (pivot = array[(sx + dx) / 2], i = sx, j = dx;
       (i <= j);
       )
  {
    while (array[i] < pivot)
      i++;
    while (array[j] > pivot)
      j--;
    if (i <= j)
    {
      if (i < j)
      {
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
      i++;
      j--;
    }
  }

  if (sx < j)
    quicksort(array, sx, j);
  if (i < dx)
    quicksort(array, i, dx);
}

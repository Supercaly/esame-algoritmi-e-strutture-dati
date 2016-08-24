#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FILE_GRAFO "grafo.txt"

void genera_elem(FILE *file, int n_elementi);

int main(void)
{
  FILE * file;
  int n_elementi;

  file = fopen(FILE_GRAFO, "w");

  printf("Il programma genera un grafo completo di ");
  printf("V vertici ed E archi\n");
  printf("Inserire numero di vertici V da generare\n");
  scanf("%d", &n_elementi);

  genera_elem(file, n_elementi);

  fclose(file);
  return 0;
}

void genera_elem(FILE *file, int n_elementi)
{
  int i, j;
  int v1 = 1,
      v2 = 1;
  double peso = 0;

  fprintf(file, "%d\n", n_elementi);
  srand(time(NULL));
  for (i = 0; i < n_elementi; i++)
  {
    fprintf(file, "%d\n", n_elementi -1);
    for (j = 1; j < n_elementi; j++)
    {
      if (j != v1)
        v2 = j;
      else
        v2 = n_elementi;
      peso = (double)rand()/(n_elementi);
      fprintf(file, "%d %d %f\n", v1, v2, peso);
    }
    v1++;
  }
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main()
{
  double a[WYMIAR][WYMIAR];
  int n, i, j;

  for (i = 0; i < WYMIAR; i++)
    for (j = 0; j < WYMIAR; j++)
      a[i][j] = 1.02 * i + 1.01 * j;

  n = WYMIAR;

  // podwĂłjna pÄtla - sekwencyjnie
  double suma = 0.0;
  for (i = 0; i < WYMIAR; i++)
  {
    for (j = 0; j < WYMIAR; j++)
    {
      suma += a[i][j];
    }
  }

  printf("Suma wyrazĂłw tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwĂłjna pÄtla - docelowo rĂłwnolegle
  double suma_parallel = 0.0;
  
  /*
  // dekompozycja wierszowa
#pragma omp parallel for default(none) reduction(+: suma_parallel) shared(a) private(i,j) schedule(static, 2) ordered num_threads(3)
  for (i = 0; i < WYMIAR; i++)
  {
    int id_w = omp_get_thread_num();
    for (j = 0; j < WYMIAR; j++)
    {
      suma_parallel += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      //printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num());
      // dla dekompozycji 2D
      printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num());
    }
    printf("\n");
  }*/
  /*
  // dekopmpozycja kolumnowa - zrownoleglenie wewnetrznej
  omp_set_nested(1);
  for (i = 0; i < WYMIAR; i++)
  {
    int id_w = omp_get_thread_num();
#pragma omp parallel for default(none) reduction(+: suma_parallel) schedule(dynamic) ordered shared(a) private(j) firstprivate(i) num_threads(3)
    for (j = 0; j < WYMIAR; j++)
    {
      suma_parallel += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      //printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num());
      // dla dekompozycji 2D
      printf("(%1d,%1d)-W_%1d,%1d ",i,j,omp_get_thread_num());
    }
    printf("\n");
  }*/

  /*
  // dekompozycja kolumnowa - zrownoleglenie zewnetrznej
  #pragma omp parallel for default(none) schedule(static) shared(a, suma_parallel) private(i,j) ordered num_threads(3)
  for (i = 0; i < WYMIAR; i++)
  {
    int id_w = omp_get_thread_num();
    double suma = 0;
    for (j = 0; j < WYMIAR; j++)
    {
      suma += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      //printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num());
      // dla dekompozycji 2D
      printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num());
    }
    #pragma omp atomic
    suma_parallel += suma;
    #pragma omp ordered
    printf("\n");
  }*/

  // --- 4 ---- //

  #pragma omp parallel for default(none) schedule(static, 2) reduction(+:suma_parallel) shared(a) private(i,j) ordered num_threads(3)
  for(i = 0; i < WYMIAR; i++) {
    int id_w = omp_get_thread_num();
    #pragma omp ordered
    #pragma omp parallel for default(none) schedule(static, 2) reduction(+: suma_parallel) shared(a) firstprivate(i, id_w) ordered num_threads(2)
    for(j = 0; j < WYMIAR; j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      printf("(%1d,%1d)-W_%1d,%1d ", i, j, id_w, omp_get_thread_num());
    }
    #pragma omp ordered
    printf("\n");
  }

  printf("Suma wyrazĂłw tablicy rĂłwnolegle: %lf\n", suma_parallel);
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18
#define LICZBA_W 4

int main()
{
  double a[WYMIAR];
  int n, i;

  for (i = 0; i < WYMIAR; i++)
    a[i] = 1.02 * i;

  n = WYMIAR;

  // pÄtla sekwencyjna
  double suma = 0.0;
  for (i = 0; i < WYMIAR; i++)
  {
    suma += a[i];
  }

  printf("Suma wyrazĂłw tablicy: %lf\n", suma);

  // pÄtla do modyfikacji - docelowo rĂłwnolegĹa w OpenMP
  double suma_parallel = 0.0;
  // ...
  //#pragma omp parallel for default(none) reduction(+:suma_parallel) firstprivate(a) ordered
  //#pragma omp parallel for default(none) reduction(+: suma_parallel) firstprivate(a) ordered schedule(static, 3) num_threads(LICZBA_W)
  //#pragma omp parallel for default(none) reduction(+: suma_parallel) firstprivate(a) ordered schedule(static) num_threads(LICZBA_W)
  #pragma omp parallel for default(none) reduction(+: suma_parallel) firstprivate(a) ordered schedule(dynamic, 2) num_threads(LICZBA_W)
  //#pragma omp parallel for default(none) reduction(+: suma_parallel) firstprivate(a) ordered schedule(dynamic) num_threads(LICZBA_W)
  for (i = 0; i < WYMIAR; i++)
  {
    int id_w = omp_get_thread_num();
    // ...
    #pragma omp atomic
    suma_parallel += a[i];
    // ...
    #pragma omp ordered
    printf("a[%2d]->W_%1d  \n", i, id_w);
  }

  printf("\nSuma wyrazĂłw tablicy rĂłwnolegle (z klauzulÄ - ....: %lf\n",
         suma_parallel);
}
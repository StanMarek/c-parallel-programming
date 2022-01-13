#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <omp.h>

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagajÄ definiowania staĹej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(void)
{ // program obliczania przybliĹźenia PI za pomocÄ wzoru Leibniza
  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )

  int max_liczba_wyrazow = 0;
  printf("Podaj maksymalnÄ liczbÄ wyrazĂłw do obliczenia przybliĹźenia PI\n");
  scanf("%d", &max_liczba_wyrazow);

  // wzĂłr: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.
  SCALAR suma_plus = 0.0;
  SCALAR suma_minus = 0.0;

  //  double t = omp_get_wtime();

  int i = 0;
  //#pragma omp parallel for default(none) shared(max_liczba_wyrazow) reduction(+:suma_plus) reduction(+:suma_minus)
  for (i = 0; i < max_liczba_wyrazow; i++)
  {

    int j = 1 + 4 * i;

    suma_plus += 1.0 / j;
    suma_minus += 1.0 / (j + 2.0);

    //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
    //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
  }

  //  t = omp_get_wtime() - t;

  printf("PI obliczone: \t\t\t%20.15lf\n", 4 * (suma_plus - suma_minus));
  printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
  //  printf("Czas obliczeĹ: %lf\n", t);
}

// caĹka
/* h   = 1.0 / (SCALAR) n; */
/* sum = 0.0; */
/* for (i = 1; i <= n; i++) { */
/*   x = h * ((SCALAR)i - 0.5); */
/*   sum += 4.0 / (1.0 + x*x); */
/* } */
/* mypi = h * sum; */
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include"pomiar_czasu.h"

// tworzenie mutekxu
pthread_mutex_t muteks; 

double funkcja ( double x );

double funkcja ( double x ){ return( sin(x) ); }

double calka_sekw(double a, double b, double dx, int N);

double calka_zrownoleglenie_petli(double a, double b, double dx, int N);

double calka_dekompozycja_obszaru(double a, double b, double dx);

struct mstruktura {
    double a;
    double b;
    double dx;
    double result;
};

#define LICZBA_W_MAX 1000
int l_w_global=4; 

int main( int argc, char *argv[] ){

  // inicjalizacja mutexa
  pthread_mutex_init( &muteks, NULL);

  int i; 

  double t1,t2,t3;

  double a, b, dx, calka;

  printf("\nProgram obliczania całki z funkcji (sinus) metodą trapezów.\n");

  a = 0.0;
  //printf("\nPodaj lewy kraniec przedziału całkowania: "); scanf("%lf", &a);

  b = M_PI;
  //printf("\nPodaj prawy kraniec przedziału całkowania: "); scanf("%lf", &b);

  printf("\nPodaj wysokość pojedynczego trapezu:  "); scanf("%lf", &dx);

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezów: N = %d\n", N);

  //printf("\nPodaj liczbę wątków:  "); scanf("%d", &l_w_global);

  printf("\nPoczatek obliczeń sekwencyjnych\n");                                        ////////////sekwencyjnie
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  t1 = czas_zegara();

  calka = calka_sekw(a, b, dx_adjust, N);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen sekwencyjnych\n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

  printf("\nPoczatek obliczeń równoległych (zrównoleglenie pętli)\n");                  ////////////rownolegle
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  t1 = czas_zegara();

  calka = calka_zrownoleglenie_petli(a, b, dx_adjust, N);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  równoległych (zrównoleglenie pętli) \n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

  printf("\nPoczatek obliczeń równoległych (dekompozycja obszaru)\n");                  ////////////rownolegle (dekompozycja)
  t1 = czas_zegara();

   calka = calka_dekompozycja_obszaru(a, b, dx);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  równoległych (dekompozycja obszaru) \n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

}


double calka_sekw(double a, double b, double dx, int N){

  int i;
  double calka = 0.0;
  for(i=0; i<N; i++){

    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);

  }

  return(calka);
}


static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int N){
  calka_global = 0.0;
  a_global = a;
  b_global = b;
  dx_global = dx;
  N_global = N;
  //printf("a %lf, b %lf, dx %lf, n %d\n", a, b, dx, N);

  int l_w = l_w_global;

  // tworzenie struktur danych do obsługi wielowątkowości
  pthread_t watki[l_w];
  
  int indeksy[l_w]; ///////////////////////////////////////nadawanie wlasnych ID watkom
  for(int i=0;i<l_w;i++) indeksy[i]=i;

  // tworzenie wątków //////////////////////////// sekwencyjnie
  for(int i=0; i<l_w; i++ ) 
    pthread_create( &watki[i], NULL, calka_fragment_petli_w, (void *) &indeksy[i] );

  // oczekiwanie na zakończenie pracy wątków
  for(int i=0; i<l_w; i++ ) {
    pthread_join( watki[i], NULL );
  }

  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){
  int my_id = *( (int *) arg_wsk ); 
  double a, b, dx; 
  int N, l_w;      
  a = a_global;
  b = b_global;
  dx = dx_global;
  N = N_global;
  l_w = l_w_global;
  int el_na_watek = ceil((float) N / l_w_global);
  //dekompozycja cykliczna
  int my_start = my_id; 
  int my_end = N;
  int my_stride = l_w;
  // dekompozycja blokowa
  int my_start = el_na_watek * my_id;
  int my_end = el_na_watek * (my_id + 1);
  int my_stride = 1;
  printf("\nWątek %d\n", my_id);
  printf("my_start %d, my_end %d, my_stride %d\n", 
	  my_start, my_end, my_stride);
  int i;
  double calka = 0.0;
  for(i=my_start; i<my_end; i+=my_stride){
    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
  }
  pthread_mutex_lock(&muteks);
  calka_global += calka;
  pthread_mutex_unlock(&muteks);
}

void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx){


  //printf("a %lf, b %lf, dx %lf\n", a, b, dx);

  int l_w = l_w_global;
  //printf("\nPodaj liczbę wątków:  "); scanf("%d", &l_w);

  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości


  // tworzenie wątków


  // oczekiwanie na zakończenie pracy wątków


  return(calka_suma_local);
}




void* calka_podobszar_w(void* arg_wsk){

  struct mstruktura *wsk_do_mstruktura = arg_wsk;

  double a_local, b_local, dx_local;
  long int N_local;

  a_local = wsk_do_mstruktura->a;
  b_local = wsk_do_mstruktura->b;
  dx_local = wsk_do_mstruktura->dx;

  N_local = 
  ((b_local-a_local)/dx_local);
  double dx_adjust = (b_local-a_local)/N_local;

  //int my_id;
  //printf("\nWątek %d\n", my_id);
  printf("a_local %lf\t, b_local %lf\t, dx_local %lf\t, n_local %ld\t\n", 
	 a_local, b_local, dx_local, N_local);

  int i;
  double calka = 0.0;
  for(i=0; i<N_local; i++){

    double x1 = a_local + i*dx_adjust;
    calka += 0.5*dx_local*(funkcja(x1)+funkcja(x1+dx_adjust));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);
    
  }
  wsk_do_mstruktura->result = calka;

}
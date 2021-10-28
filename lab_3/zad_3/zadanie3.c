#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int P = 2;

typedef struct {
  char *imie;
  char *nazwisko;
  int index;
} Dane;

Dane daneGlobalne = {"Struktura", "Globalna", 0};

void *zadanie_watku(void* arg_wsk) {
  Dane daneLok = *((Dane*)arg_wsk);

  printf("Dane globalne w funkcji przed:\n %d\n %s\n %s\n", daneGlobalne.index, daneGlobalne.imie, daneGlobalne.nazwisko);
  printf("Dane lokalne w funkcji przed:\n %d\n %s\n %s\n", daneLok.index, daneLok.imie, daneLok.nazwisko);
  daneLok.imie = "s";
  daneLok.nazwisko = "m";
  daneLok.index = 0;
  daneGlobalne.imie += 1;
  daneGlobalne.nazwisko += 1;
  daneGlobalne.index += 1;
  printf("Dane globalne w funkcji po:\n %d\n %s\n %s\n", daneGlobalne.index, daneGlobalne.imie, daneGlobalne.nazwisko);
  printf("Dane lokalne w funkcji po\n %d\n %s\n %s\n", daneLok.index, daneLok.imie, daneLok.nazwisko);
}

int main() {
  pthread_t pthreads[P];
  
  Dane dane = {"Stanislaw", "Marek", 403515};
  printf("Dane lokalne w main przed:\n %d\n %s\n %s\n", dane.index, dane.imie, dane.nazwisko);
  printf("Dane globalne w main przed:\n %d\n %s\n %s\n", daneGlobalne.index, daneGlobalne.imie, daneGlobalne.nazwisko);

  for(int i = 0; i < P; i++){
    pthread_create(&pthreads[i], NULL, zadanie_watku, &dane);
  }

  // for(int i = 0; i < P; i++) {
  //   pthread_join(pthreads[i], NULL);
  // }

  printf("Dane lokalne w main po:\n %d\n %s\n %s\n", dane.index, dane.imie, dane.nazwisko);
  printf("Dane globalne w main po:\n %d\n %s\n %s\n", daneGlobalne.index, daneGlobalne.imie, daneGlobalne.nazwisko);
}
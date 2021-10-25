#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int P = 3;

typedef struct {
  char imie[10];
  char nazwisko[10];
  int index;
} Dane;

void *zadanie_watku(void* arg_wsk) {
  Dane daneLok = *((Dane*)arg_wsk);


  printf("Dane lokalne przed %d\n %s\n %s\n", daneLok.index, daneLok.imie, daneLok.nazwisko);
  daneLok = {"s", "m", 1};
  printf("Dane lokalne po %d\n %s\n %s\n", daneLok.index, daneLok.imie, daneLok.nazwisko);
}

int main() {
  pthread_t pthreads[P];

  Dane dane = {"Stanislaw", "Marek", 403515};

  int identyfikatory[P];
  for(int i = 0; i < P; i++){
    identyfikatory[i] = i;
  }

  for(int i = 0; i < P; i++){
    //printf("Numer iteracji: %d\t", i);
    pthread_create(&pthreads[i], NULL, zadanie_watku, &dane);
  }

  for(int i = 0; i < P; i++) {
    pthread_join(pthreads[i], NULL);
  }
}
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int P = 100;

void *zadanie_watku(void* arg_wsk) {
  int arg = *((int*)arg_wsk);

  printf("Numer watku: %d\n", arg);
}

int main() {
  pthread_t pthreads[P];

  int identyfikatory[P];
  for(int i = 0; i < P; i++){
    identyfikatory[i] = i;
  }

  for(int i = 0; i < P; i++){
    //printf("Numer iteracji: %d\t", i);
    pthread_create(&pthreads[i], NULL, zadanie_watku, &i);
  }

  for(int i = 0; i < P; i++) {
    pthread_join(pthreads[i], NULL);
  }
}
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t bariera_lock;
static pthread_cond_t bariera_cond;
int liczba_watkow_aktualnie;
int liczba_watkow_docelowo;

void bariera_init(int n){
  pthread_mutex_init(&bariera_lock, NULL);
  pthread_cond_init(&bariera_cond, NULL);
  liczba_watkow_aktualnie = 0;
  liczba_watkow_docelowo = n;
}

void bariera(){
  pthread_mutex_lock(&bariera_lock);
  liczba_watkow_aktualnie++;
  if(liczba_watkow_aktualnie != liczba_watkow_docelowo ) {
    pthread_cond_wait(&bariera_cond, &bariera_lock);
  } else {
    liczba_watkow_aktualnie = 0;
    pthread_cond_broadcast(&bariera_cond);
  }
  pthread_mutex_unlock(&bariera_lock);
}

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->czytelnia_mutex);
    if(czytelnia_p->liczba_pisarzy > 0 || czytelnia_p->liczba_czekajacych_pisanie > 0) {
        czytelnia_p->liczba_czekajacych_czytanie++;
        pthread_cond_wait(&czytelnia_p->kolejka_czytelnikow, &czytelnia_p->czytelnia_mutex);
        czytelnia_p->liczba_czekajacych_czytanie--;
    }
    czytelnia_p->liczba_czytelnikow++;
    pthread_cond_signal(&czytelnia_p->kolejka_czytelnikow);
    pthread_mutex_unlock(&czytelnia_p->czytelnia_mutex);

    if(czytelnia_p->liczba_pisarzy < 0) 
        printf("Liczba pisarzy mniej niz 0");
    if(czytelnia_p->liczba_czytelnikow < 0) 
        printf("Liczba czytelnikow mniej niz 0");
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
   pthread_mutex_lock(&czytelnia_p->czytelnia_mutex);
   czytelnia_p->liczba_czytelnikow--;
   pthread_mutex_unlock(&czytelnia_p->czytelnia_mutex);
   if(czytelnia_p->liczba_czytelnikow == 0) {
       pthread_cond_signal(&czytelnia_p->kolejka_pisarzy);
   }
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
  pthread_mutex_lock(&czytelnia_p->czytelnia_mutex);
  if(czytelnia_p->liczba_czytelnikow + czytelnia_p->liczba_pisarzy > 0) {
      czytelnia_p->liczba_czekajacych_pisanie++;
      pthread_cond_wait(&czytelnia_p->kolejka_pisarzy, &czytelnia_p->czytelnia_mutex);
      czytelnia_p->liczba_czekajacych_pisanie--;
  }
  czytelnia_p->liczba_pisarzy++;
  pthread_mutex_unlock(&czytelnia_p->czytelnia_mutex);

  if (czytelnia_p->liczba_pisarzy < 0)
      printf("Liczba pisarzy mniej niz 0");
  if (czytelnia_p->liczba_czytelnikow < 0)
      printf("Liczba czytelnikow mniej niz 0");
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->czytelnia_mutex);
    czytelnia_p->liczba_pisarzy--;
    pthread_mutex_unlock(&czytelnia_p->czytelnia_mutex);
    if(czytelnia_p->liczba_czekajacych_czytanie > 0) {
        pthread_cond_signal(&czytelnia_p->kolejka_czytelnikow);
    } else {
        pthread_cond_signal(&czytelnia_p->kolejka_pisarzy);
    }

    if (czytelnia_p->liczba_pisarzy < 0)
        printf("Liczba pisarzy mniej niz 0");
    if (czytelnia_p->liczba_czytelnikow < 0)
        printf("Liczba czytelnikow mniej niz 0");
}

void inicjuj(czytelnia_t* czytelnia_p){
    czytelnia_p->liczba_pisarzy = 0;
    czytelnia_p->liczba_czytelnikow = 0;
    czytelnia_p->liczba_czekajacych_pisanie = 0;
    czytelnia_p->liczba_czekajacych_czytanie = 0;
    pthread_cond_init(&czytelnia_p->kolejka_pisarzy, NULL);
    pthread_cond_init(&czytelnia_p->kolejka_czytelnikow, NULL);
    pthread_mutex_init(&czytelnia_p->czytelnia_mutex, NULL);
}

void czytam(czytelnia_t* czytelnia_p){
    if(czytelnia_p->liczba_pisarzy > 1 || (czytelnia_p->liczba_pisarzy == 1 && czytelnia_p->liczba_czytelnikow > 0)) {
        printf("blad");
        exit(1);
    }
    printf("czytelnicy: %d, pisarze: %d\n", czytelnia_p->liczba_czytelnikow, czytelnia_p->liczba_pisarzy);
    usleep(rand()%300000);
}

void pisze(czytelnia_t* czytelnia_p){
    if(czytelnia_p->liczba_pisarzy > 1 || (czytelnia_p->liczba_pisarzy == 1 && czytelnia_p->liczba_czytelnikow > 0)) {
        printf("blad");
        exit(1);
    }
    printf("czytelnicy: %d, pisarze: %d\n", czytelnia_p->liczba_czytelnikow, czytelnia_p->liczba_pisarzy);
    usleep(rand() % 300000);
}



#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 333

void * watek_klient (void * arg);

pthread_mutex_t mutex_kufel;
pthread_mutex_t mutex_kran;

int l_wkf; //liczba wolnych kufli
int l_pkf; //liczba pobranych kufli
int max_lkf; //maksymalna liczba kufli

int main( void ){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  l_wkf = max_lkf = l_kf;
  l_pkf = 0;
  l_kr = 100000;
  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  
  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;
  
  pthread_mutex_init(&mutex_kufel, NULL);
  pthread_mutex_init(&mutex_kran, NULL);

  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }

  if(l_wkf != l_kf) {
    printf("\nLiczba wolnych kufli nie zgadza sie: %d\n", l_wkf);
    exit(-1);
  }
  printf("\nZamykamy pub!\n");
  printf("\nLiczba wolnych kufli: %d\n", l_wkf); 
}


void * watek_klient (void * arg_wsk){
  int moj_id = * ((int *)arg_wsk);
  int i, j, kufel, result;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;
  //printf("\nKlient {%d}, wchodzi do pubu\n", moj_id); 
  for(i=0; i<ile_musze_wypic; i++){
    if(l_wkf > 0) {
      //printf("\nKlient {%d}, wybieram kufel\n", moj_id); 
      pthread_mutex_lock(&mutex_kufel);
      l_wkf--;
      l_pkf++;
      pthread_mutex_unlock(&mutex_kufel);
      if(l_pkf > max_lkf) {
        printf("\nZa duzo pobranych kufli");
        exit(-1);
      }
      j=0;
      pthread_mutex_lock(&mutex_kran);
      //printf("\nKlient {%d}, nalewam z kranu %d\n", moj_id, j); 
      usleep(30);
      pthread_mutex_unlock(&mutex_kran);
      
      //printf("\nKlient {%d}, pije\n", moj_id); 
      nanosleep((struct timespec[]){{0, 50000000L}}, NULL);
      
      //printf("\nKlient {%d}, odkladam kufel\n", moj_id); 
      pthread_mutex_lock(&mutex_kufel);
      l_wkf++;
      l_pkf--;
      pthread_mutex_unlock(&mutex_kufel);
    }
  }
  //printf("\nKlient {%d}, wychodzi z pubu\n", moj_id); 
  return(NULL);
} 


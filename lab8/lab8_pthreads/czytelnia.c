#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
 
#include"czytelnia.h"
 
/*** Implementacja procedur interfejsu ***/
 
// chce czytac
int my_read_lock_lock(czytelnia_t* czytelnia_p){
 
    pthread_mutex_lock(&czytelnia_p->mutex_czytelnia);
    if ( czytelnia_p->liczba_pis > 0 || czytelnia_p->liczba_czekajacych_na_pisanie > 0) {
        czytelnia_p->liczba_czekajacych_na_czytanie++;
        pthread_cond_wait(&czytelnia_p->kolejka_czytelnikow, &czytelnia_p->mutex_czytelnia);
        czytelnia_p->liczba_czekajacych_na_czytanie--;
    }
    czytelnia_p->liczba_czyt++;
    pthread_mutex_unlock(&czytelnia_p->mutex_czytelnia);
    pthread_cond_signal(&czytelnia_p->kolejka_czytelnikow);
	
	if ( czytelnia_p->liczba_pis < 0) printf("ERROR, liczba pisarzy < 0!\n");
	if ( czytelnia_p->liczba_pis > 0) printf("ERROR, liczba pisarzy > 0!\n");
	if ( czytelnia_p->liczba_czyt < 0) printf("ERROR, liczba czytelnikow < 0!\n");
}
 
// koniec czytania
int my_read_lock_unlock(czytelnia_t* czytelnia_p){
        pthread_mutex_lock(&czytelnia_p->mutex_czytelnia);
        czytelnia_p->liczba_czyt--;
        pthread_mutex_unlock(&czytelnia_p->mutex_czytelnia);
 
        if (czytelnia_p->liczba_czyt == 0)
            pthread_cond_signal(&czytelnia_p->kolejka_pisarzy);
}

// chce pisac
int my_write_lock_lock(czytelnia_t* czytelnia_p){
        
        pthread_mutex_lock(&czytelnia_p->mutex_czytelnia);
        
        if ( czytelnia_p->liczba_pis > 0 || czytelnia_p->liczba_czyt > 0 ) {
		    czytelnia_p->liczba_czekajacych_na_pisanie++;
            pthread_cond_wait(&czytelnia_p->kolejka_pisarzy, &czytelnia_p->mutex_czytelnia);
		    czytelnia_p->liczba_czekajacych_na_pisanie--;
	    }  
        czytelnia_p->liczba_pis++;
        
        pthread_mutex_unlock(&czytelnia_p->mutex_czytelnia);

	if ( czytelnia_p->liczba_pis < 0) printf("ERROR, liczba pisarzy < 0!\n");
	if ( czytelnia_p->liczba_pis > 1) printf("ERROR, liczba pisarzy > 1!\n");
	if ( czytelnia_p->liczba_czyt < 0) printf("ERROR, liczba czytelnikow < 0!\n");
	if ( czytelnia_p->liczba_czyt > 0) printf("ERROR, liczba czytelnikow > 0!\n");
}
 
// koniec pisania
int my_write_lock_unlock(czytelnia_t* czytelnia_p){
        pthread_mutex_lock(&czytelnia_p->mutex_czytelnia);        
        czytelnia_p->liczba_pis--;
        pthread_mutex_unlock(&czytelnia_p->mutex_czytelnia);
        if (czytelnia_p->liczba_czekajacych_na_czytanie > 0)    //jesli sa oczekujacy na czytanie
        	pthread_cond_signal(&czytelnia_p->kolejka_czytelnikow); //budzi czytelnikow
        else 
        	pthread_cond_signal(&czytelnia_p->kolejka_pisarzy); //jak nie ma czytelnikow to budzi pisarza
}
 
void inicjuj(czytelnia_t* czytelnia_p){
	//poczatkowe wartosci
        czytelnia_p->liczba_pis = 0;
        czytelnia_p->liczba_czyt = 0;
        czytelnia_p->liczba_czekajacych_na_czytanie = 0;
        czytelnia_p->liczba_czekajacych_na_pisanie = 0;
        pthread_mutex_init(&czytelnia_p->mutex_czytelnia, NULL);
        pthread_cond_init( &czytelnia_p->kolejka_czytelnikow, NULL );
        pthread_cond_init( &czytelnia_p->kolejka_pisarzy, NULL );
}
 //wyswietlenie stanu czytelni
void czytam(czytelnia_t* czytelnia_p){
	printf("Liczba czytelnikow: %d, Liczba pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pis);
	usleep(rand()%1000000);
}
 
void pisze(czytelnia_t* czytelnia_p){
	printf("Liczba czytelnikow: %d, Liczba pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pis);
	usleep(rand()%1000000);
}

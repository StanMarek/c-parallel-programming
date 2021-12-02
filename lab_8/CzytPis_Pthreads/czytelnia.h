#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typow zmiennych ***/
typedef struct
{
  // <- zasoby czytelni
} czytelnia_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(czytelnia_t *czytelnia_p);
void czytam(czytelnia_t *czytelnia_p);
void pisze(czytelnia_t *czytelnia_p);

int my_read_lock_lock(czytelnia_t *czytelnia_p);
int my_read_lock_unlock(czytelnia_t *czytelnia_p);
int my_write_lock_lock(czytelnia_t *czytelnia_p);
int my_write_lock_unlock(czytelnia_t *czytelnia_p);

#endif

/* zasoby
int liczba_czyt, liczba_czekajacych_na_czytanie;
int liczba_pis, liczba_czekajacych_na_pisanie;
pthread_mutex_t mutex_czytelnia;
pthread_cond_t kolejka_czytelnikow;
pthread_cond_t kolejka_pisarzy;
*/
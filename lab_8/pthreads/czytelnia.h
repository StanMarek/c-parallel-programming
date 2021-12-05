#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typow zmiennych ***/
typedef struct
{
  // <- zasoby czytelni
  int liczba_czytelnikow;
  int liczba_czekajacych_czytanie;
  int liczba_pisarzy;
  int liczba_czekajacych_pisanie;
  
  pthread_mutex_t czytelnia_mutex;
  pthread_cond_t kolejka_czytelnikow;
  pthread_cond_t kolejka_pisarzy;

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

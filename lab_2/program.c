#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>


#define STOS 1024*64
#define ITER 100000
int global = 0;

typedef struct {
  int index;
  char *imie;
  char *nazwisko;
} Dane;

void funkcja( void* argument )
{
  Dane arg;
  arg = *((Dane*)argument);

  printf("Dane %d\n %s\n %s\n", arg.index, arg.imie, arg.nazwisko);
}

int main() {
  int clone1, clone2;
  int local = 0;

  void* stos1 = malloc(STOS);
  void* stos2 = malloc(STOS);

  Dane dane;
  dane.imie = "STANISLAW";
  dane.nazwisko = "MAREK";
  dane.index = 403515;

  if(stos1 == 0 || stos2 ==  0) {
    exit(1);
  }

  clone1 = clone(&funkcja, (void *) stos1+STOS,
    CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &dane);
  clone2 = clone(&funkcja, (void *) stos2+STOS,
    CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &dane);

  waitpid(clone1, NULL, __WCLONE);
  waitpid(clone2, NULL, __WCLONE);

  free(stos1);
  free(stos2);
}



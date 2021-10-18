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

struct DANE{
  int index;
  char imie[10];
  char nazwisko[10];
};


void funkcja( void* argument )
{
  int arg;
  arg = *((int*)argument);

  for(int i = 0; i < ITER; i++){
    global++; 
    arg++;
  }

  // printf("Zmienna globalna: %d\n", global);
  // printf("Zmienna lokalna: %d\n", arg);
  struct DANE dane = {403515, "STANISLAW", "MAREK"};

  printf("Dane %d\n %s\n %s\n", dane.index, dane.imie, dane.nazwisko);

}

int main() {
  int clone1, clone2;
  int local = 0;

  void* stos1 = malloc(STOS);
  void* stos2 = malloc(STOS);

  if(stos1 == 0 || stos2 ==  0) {
    exit(1);
  }

  clone1 = clone(&funkcja, (void *) stos1+STOS,
    CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &local);
  clone2 = clone(&funkcja, (void *) stos2+STOS,
    CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &local);

  waitpid(clone1, NULL, __WCLONE);
  waitpid(clone2, NULL, __WCLONE);

  // printf("Globalna po: %d\n", global);
  // printf("Lokalna po: %d\n", local);

  free(stos1);
  free(stos2);
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <omp.h>

#include "mpi.h"

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif
int main( int argc, char** argv ){ // program obliczania przybliżenia PI za pomocą wzoru Leibniza
                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  
  int rank, size;
  MPI_Status status;
  
  MPI_Init( &argc, &argv ); 
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    
  // wzór: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.  
  
  if(size>1){
   
      int max_liczba_wyrazow=0;
      
      if(rank==0){
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
      }
      
      double suma_plus=0.0;
      double suma_minus=0.0;
      
      MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);
      
      
      int liczbaNaProces=ceil((float)max_liczba_wyrazow/(float)(size));
      //int ostatniProces=abs(max_liczba_wyrazow-liczbaNaProces*(size-1));
      
      int start;
      int end;
      //printf("liczba procesow %d, size %d\n", liczbaNaProces, size);
      if(rank==size-1){
          start=rank*liczbaNaProces;
          end=max_liczba_wyrazow;
      }
      else{
            start=liczbaNaProces*rank;
            end=start+liczbaNaProces;
      }
      
      for(double i=start; i<end; i++){
            double j = 1 + 4*i;
            suma_plus += 1.0f/j;
            suma_minus += 1.0f/(j+2.0f);
      }
      
      //printf("Proces %d - start %d, end %d\n", rank, start,end);
      double pi_loc=suma_plus-suma_minus;
      
      double pi=0.0;
      //printf("Proces %d - %lf\n", rank, wynik);
      MPI_Reduce(&pi_loc, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
      
      if(rank==0){
          printf("PI obliczone: \t\t\t%20.15lf\n", pi*4);
            printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
      }
      
      
  }
  
  MPI_Finalize(); 
}



  // całka
  /* h   = 1.0 / (SCALAR) n; */
  /* sum = 0.0; */
  /* for (i = 1; i <= n; i++) { */
  /*   x = h * ((SCALAR)i - 0.5); */
  /*   sum += 4.0 / (1.0 + x*x); */
  /* } */
  /* mypi = h * sum; */

# kompilator c
CCOMP = gcc

# konsolidator
LINKER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
pthreads_detach_kill: pthreads_detach_kill.o
	$(LINKER) -lpthread $(OPT) pthreads_detach_kill.o -o pthreads_detach_kill

# jak uzyskac plik moj_program.o ?
pthreads_detach_kill.o: pthreads_detach_kill.c
	$(CCOMP) -c $(OPT) pthreads_detach_kill.c

clean:
	rm -f *.o
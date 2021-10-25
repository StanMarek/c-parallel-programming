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
zadanie2: zadanie2.o
	$(LINKER) -lpthread $(OPT) zadanie2.o -o zadanie2

# jak uzyskac plik moj_program.o ?
zadanie2.o: zadanie2.c
	$(CCOMP) -c $(OPT) zadanie2.c

clean:
	rm -f *.o
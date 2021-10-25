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
zadanie3: zadanie3.o
	$(LINKER) -lpthread $(OPT) zadanie3.o -o zadanie3

# jak uzyskac plik moj_program.o ?
zadanie3.o: zadanie3.c
	$(CCOMP) -c $(OPT) zadanie3.c

clean:
	rm -f *.o
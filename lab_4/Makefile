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
pub_sym_1: pub_sym_1.o
	$(LINKER) -lpthread $(OPT) pub_sym_1.o -o pub_sym_1

# jak uzyskac plik moj_program.o ?
pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c

pub_sym_2: pub_sym_2.o
	$(LINKER) -lpthread $(OPT) pub_sym_2.o -o pub_sym_2

# jak uzyskac plik moj_program.o ?
pub_sym_2.o: pub_sym_2.c
	$(CCOMP) -c $(OPT) pub_sym_2.c

clean:
	rm -f *.o
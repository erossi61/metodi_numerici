# Makefile generico: da copiare identico in modulo1, modulo2, modulo3, prova_progetti
# Ogni file .c nella cartella e' considerato un main e diventa un eseguibile
# con lo stesso nome (es. pi_ss.c -> pi_ss), linkato con tutti i file di ../lib

CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror -pedantic -Wconversion -std=c99
INCDIR=../include
LIBDIR=../lib
CPPFLAGS=-I$(INCDIR)
LDLIBS=-lm

# main presenti nella cartella corrente
sources=$(wildcard *.c)
binaries=$(sources:.c=)

# librerie comuni in ../lib (gli .o vengono creati qui)
libsources=$(wildcard $(LIBDIR)/*.c)
libobjects=$(notdir $(libsources:.c=.o))
headers=$(wildcard $(INCDIR)/*.h)

all: $(binaries)

# compilazione delle librerie: ../lib/random.c -> random.o
%.o: $(LIBDIR)/%.c $(headers)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# compilazione e link di ogni main: pi_ss.c -> pi_ss
%: %.c $(libobjects) $(headers)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< $(libobjects) -o $@ $(LDLIBS)

# evita che make cancelli gli .o considerandoli intermedi
.SECONDARY: $(libobjects)

.PHONY: all clean cleanobj list
clean:
	rm -f $(binaries) *.o

cleanobj:
	rm -f *.o

# mostra cosa verrebbe compilato
list:
	@echo "main:     $(binaries)"
	@echo "librerie: $(libobjects)"
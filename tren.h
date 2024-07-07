/* SIMION George Constantin - 313CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declare lista dubla inlantuita = trenulet */
typedef struct celula2{
    char info;
    struct celula2 *pre, *urm;
} TCelula2, *TLista2;

/* Declare tipul trenulet cu santinela si mecanic */
typedef struct trenulet{
    TLista2 s;
    TLista2 mecanic;
} TCelulaTrenulet, *Trenulet;

/* Declarare lista dublu inlentuita = coada cu informatie de tip pointer */
typedef struct celulaCoada{
    char *info;
    struct celulaCoada *pre, *urm;
} TCelulaCoada, *TListaCoada;

/* Declarare coada de comenzi */
typedef struct coada{
    TListaCoada inc, sf;
} TcelulaCodita, *TCoada;

            /* Functii */
/* Functii de initializare + Input/Output + distrugere */
Trenulet InitTL2();
TCoada InitQ();
void IntrQ(TCoada comenzi, char *command);
void executeComanda(FILE *fout, TCoada comenzi, Trenulet tren);
char *extrageComanda(TCoada *comenzi);
void INPUT(FILE *fin, FILE *fout, TCoada comenzi, Trenulet tren);
void DistrugeCoada(TCoada comenzi);
void DistrugeTren(Trenulet tren);

/* Functii UPDATE */
Trenulet moveLeft(Trenulet tren);
Trenulet moveRight(Trenulet tren);
Trenulet newMecanic(Trenulet tren, char new_mecanic);
Trenulet clearCell(Trenulet tren);
Trenulet clearAll(Trenulet tren);
Trenulet insertLeft(FILE *fout, Trenulet tren, char new_mecanic);
Trenulet insertRight(Trenulet tren, char new_mecanic);

/* Functii QUERY */
void showCurent(FILE *fout, Trenulet tren);
void showAll(FILE *fout, Trenulet tren);
void SWITCH(TCoada *comenzi);

/* Functii SEARCH */
Trenulet SEARCH(FILE *fout, Trenulet tren, char *cautat);
Trenulet SEARCH_LEFT(FILE *fout, Trenulet tren, char *cautat);
Trenulet SEARCH_RIGHT(FILE *fout, Trenulet tren, char *cautat);

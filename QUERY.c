/* SIMION George Constantin - 313CB */

#include "QUERY.h"

void showCurent(FILE *fout, Trenulet tren)
/* Afisare elemnt de pe mecanic */
{
    fprintf(fout, "%c", tren->mecanic->info);
    fprintf(fout, "\n");                                    /* Afisam mecanicul de pe pozitia lui */
}

void showAll(FILE *fout, Trenulet tren)
/* Afisare tot trenulet */
{
    TLista2 aux = tren->s->urm;
    while (aux != tren->s) {
        if (aux == tren->mecanic) {
            fprintf(fout, "|%c|", aux->info);

        } else {
            fprintf(fout, "%c", aux->info);
        }                                                   /* Verificare daca e mecanic sau nu */

        aux = aux->urm;
    }
    fprintf(fout, "\n");
}

void SWITCH(TCoada *comenzi)
/* Schimbare ordine elemente din coada */
{
    TListaCoada current = (*comenzi)->inc;
    TListaCoada ant = NULL, urm = NULL;
    (*comenzi)->sf = (*comenzi)->inc;                       /* Pregatim anterior si urmator pentru a le putea schimba si schimbam finalul cozii cu inceputul */

    while (current != NULL) {
        urm = current->urm;
        current->urm = ant;
        current->pre = urm;

        ant = current;
        current = urm;                                      /* Schimbam pre si urm intre ele pentru fiecare comanda */
    }
    (*comenzi)->inc = ant;                                  /* Schimbam inceputul cozii cu finalul */
}
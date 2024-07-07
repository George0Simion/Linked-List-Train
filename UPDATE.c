/* SIMION George Constantin - 313CB */

#include "UPDATE.h"

Trenulet moveLeft(Trenulet tren)
/* Mutam mecanicul la stanga */
{
    if (tren->mecanic->pre != tren->s) {
        tren->mecanic = tren->mecanic->pre;
    }                                                                       /* Mutam mecanicul doar daca nu e pe primul vagon */

    return tren;
}

Trenulet moveRight(Trenulet tren)
/* Mutam mecanicul la dreapta */
{
    if (tren->mecanic->urm == tren->s) {
        TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
        if(!aux) return tren;

        aux->info = '#';

        aux->pre = tren->mecanic;
        aux->urm = tren->s;

        tren->mecanic->urm = aux;
        tren->s->pre = aux;

        tren->mecanic = aux;                                                /* Daca mecanicul e pe ultimul vagon cream un nou vagon, il legam si mutam mecanicul */
    } else {
        tren->mecanic = tren->mecanic->urm;                                 /* Daca nu e pe ultimu vagon, facem mecanicul sa pointeze una la dreapta */
    }

    return tren;
}

Trenulet newMecanic(Trenulet tren, char new_mecanic)
/* Actualizare informatie din mecanic */
{
    tren->mecanic->info = new_mecanic;

    return tren;
}

Trenulet clearCell(Trenulet tren)
/* Eliberare vagon */
{
    if (tren->mecanic->urm == tren->s) return tren;                         /* Daca mecanicul e singur nu eliberam nimic */
    else {
        TLista2 aux = tren->mecanic;
        tren->mecanic->pre->urm = tren->mecanic->urm;
        tren->mecanic->urm->pre = tren->mecanic->pre;

        if (tren->mecanic->pre == tren->s) tren->mecanic = tren->s->pre;
        else tren->mecanic = tren->mecanic->pre;                            /* Mutam mecanicul la stanga in functie de santinela, daca e santinela la stanga o ocolim */

        free(aux);
    }

    return tren;
}

Trenulet clearAll(Trenulet tren)
/* Eliberare tren */
{
    TLista2 aux = tren->s->urm;
    while (aux != tren->s) {
        TLista2 delete = aux;
        aux = aux->urm;
        free(delete);
    }
    
    tren->s->urm = tren->s;
    tren->s->pre = tren->s;                                                /* Eliberam tot trenul si ramanem doar cu santinela */

    TLista2 new_mecanic = (TLista2)malloc(sizeof(TCelula2));
    if(!new_mecanic) return tren;

    new_mecanic->info = '#';
    new_mecanic->pre = tren->s;
    new_mecanic->urm = tren->s;
    tren->s->urm = new_mecanic;
    tren->s->pre = new_mecanic;
    tren->mecanic = new_mecanic;                                            /* Cream un nou mecanic si il legam = aducem trenul in starea initiala */

    return tren;
}

Trenulet insertLeft(FILE *fout, Trenulet tren, char new_mecanic)
/* Inseram in stanga o noua celula si mutam mecanicul */
{
    if (tren->mecanic->pre == tren->s) fprintf(fout, "ERROR\n");            /* Nu putem insera in stanga daca e doar mecanicul */
    else {
        TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
        if(!aux) return tren;

        aux->info = new_mecanic;                                            /* Cream celula si ii punem in informatie noul mecanic */

        aux->pre = tren->mecanic->pre;
        aux->urm = tren->mecanic;

        tren->mecanic->pre->urm = aux;
        tren->mecanic->pre = aux;                                        /* Legam noul vagon de tren */

        tren->mecanic = aux;
    }

    return tren;
}

Trenulet insertRight(Trenulet tren, char new_mecanic)
/* Inseram in dreapta o noua celula si mutam mecanicul */
{
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if(!aux) return tren;

    aux->info = new_mecanic;                                                /* Cream celula si ii punem in informatie noul mecanic */

    aux->pre = tren->mecanic;
    aux->urm = tren->mecanic->urm;

    tren->mecanic->urm->pre = aux;
    tren->mecanic->urm = aux;

    tren->mecanic = aux;                                                    /* Legam celula noua de tren si mutam mecanicul */

    return tren;
}
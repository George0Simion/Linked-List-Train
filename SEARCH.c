/* SIMION George Constantin - 313CB */

#include "SEARCH.h"

int lungimeTren(Trenulet tren)
/* Functie care calculeaza numarul de vagoane din tren */
{
    TLista2 aux = tren->s->urm;
    int nrVagoane = 0;

    while (aux != tren->s) {
        aux = aux->urm;
        nrVagoane++;
    }

    return nrVagoane;
}

Trenulet SEARCH(FILE *fout, Trenulet tren, char *cautat)
/* Functia care cauta existenta unui substring in vagoanele trenului */
{
    int lenTren = lungimeTren(tren);
    int lenCautat = strlen(cautat);
    int sem = 0;

    if (lenTren < lenCautat) {
        fprintf(fout, "ERROR\n");
        return tren;
    }                                                                   /* Eroare in caz ca lungimea cuvantului e mai mare decat lungimea trenului */

    TLista2 copieTren = tren->mecanic;                                  /* Incepem cautarea de la mecanic */
    int i = 0;
    for (i = 0; i < lenTren && sem == 0; i++) {                     /* Verificam fiecare substring cu un nou inceput pornind de la mecanic  */

        char *sir = calloc((lenCautat + 1), sizeof(char));              /* Pentru fiecare substring alocam un nou sir de lungimea cuvantului cautat + '\0' */
        TLista2 aux = copieTren;                                        /* copieTren indica celula de pe care incepem crearea substringului */

        int j = 0;
        for (j = 0; j < lenCautat; j++) {
            if (aux == tren->s) {
                aux = tren->s->urm;
            }
            sir[j] = aux->info;
            aux = aux->urm;
        }                                                                /* Adaugam intr-un string fiecare informatie */

        if(strcmp(sir, cautat) == 0) {
            sem = 1;
            tren->mecanic = copieTren;
        }                                                                /* Comparam stringul nostru cu cel cautat si daca il gasim mutam mecanicul si schimbam semaforul pe 1 */

        free(sir);
        if (copieTren->urm == tren->s) copieTren = tren->s->urm;
        else copieTren = copieTren->urm;                                      /* Eliberam stringul creat si mutam copia pt urmatorul sir */
    }
    if (sem == 0) fprintf(fout, "ERROR\n");                              /* Daca semaforul e pe 0 inseamna ca string ul nu a fost gasit */

    return tren;
}

Trenulet SEARCH_RIGHT(FILE *fout, Trenulet tren, char *cautat)
/* Functie care cauta la dreapta un string dat */
{
    int lenCautat = strlen(cautat);
    int sem = 0;                                                                                /* Semafor de control */

    TLista2 aux;
    for (aux = tren->mecanic; aux != tren->s && sem == 0; aux = aux->urm) {             /* Parcurgem trenul pana gasim stringul cautat sau santinela */
        
        char *sir = calloc((lenCautat + 1), sizeof(char));
        TLista2 vagon = aux;

        int j;
        for (j = 0; j < lenCautat && vagon != tren->s; j++) {
            sir[j] = vagon->info;
            vagon = vagon->urm;
        }                                                   /* Iteram prin vagoane si cream un string de la vagonul respectiv pana la santinela / lungimea cuvantului cautat */

        if(strcmp(sir, cautat) == 0) {
            sem = 1;
            tren->mecanic = vagon->pre;
        }                                                                           /* Vedem daca am gasit string-ul si actualizam mecanicul cu finalul stringului */

        free(sir);
    }
    if (sem == 0) fprintf(fout, "ERROR\n");                                                      /* String-ul nu a fost gasit */

    return tren;
}

Trenulet SEARCH_LEFT(FILE *fout, Trenulet tren, char *cautat)
/* Functie care cauta la stanga un stringa dat */
{
    int lenCautat = strlen(cautat);
    int sem = 0;

    TLista2 aux;
    for (aux = tren->mecanic; aux != tren->s && sem == 0; aux = aux->pre) {             /* Parcurgem trenul pana la santinela sau pana gasim string-ul cautat invers */
        
        char *sir = calloc((lenCautat + 1), sizeof(char));
        TLista2 vagon = aux;

        int j;
        for (j = 0; j < lenCautat && vagon != tren->s; j++) {
            sir[j] = vagon->info;
            vagon = vagon->pre;
        }                                                   /* Iteram prin vagoane invers pana la intalnirea santinelei sau lungimea cuvantului cautat */

        if(strcmp(sir, cautat) == 0) {
            sem = 1;
            tren->mecanic = vagon->urm;
        }                                                                                       /* Daca am gasit string-ul actualizam semaforul si mecanicul */

        free(sir);
    }
    if (sem == 0) fprintf(fout, "ERROR\n");                                                     /* String-ul nu a fost gasit */

    return tren;
}
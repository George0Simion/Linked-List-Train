/* SIMION George Constantin - 313CB */

#include "tren.h"

Trenulet InitTL2()
/* Initializare trenulet */
{
    Trenulet tren = (Trenulet)malloc(sizeof(TCelulaTrenulet));
    if (!tren) return NULL;                                            /* Alocare memorie pentru tren, verificare alocare */

    tren->s = (TLista2)malloc(sizeof(TCelula2));
    if(!tren->s) {
        free(tren);
        return NULL;
    }
    tren->s->info = '#';                                /* Alocare memorie santinela, verificare alocare si o informatie random in santinela care nu va fi accesata */

    tren->mecanic = (TLista2)malloc(sizeof(TCelula2));
    if(!tren->mecanic) {
        free(tren->s);
        free(tren);
        return NULL;
    }
    tren->mecanic->info = '#';                                          /* Alocare memorie mecanic, verificare alocare si punere informatie in mecanic */

    tren->s->urm = tren->mecanic;
    tren->s->pre = tren->mecanic;
    tren->mecanic->urm = tren->s;
    tren->mecanic->pre = tren->s;                                       /* Legaturile initiale dintre mecanic si santinela */

    return tren;
}

TCoada InitQ()
/* Initializare coada comenzi */
{
    TCoada c = (TCoada)malloc(sizeof(TcelulaCodita));
    if (!c) return NULL;
    c->inc = NULL;
    c->sf = NULL;
    return c;                                               /* Alocare memorie pentru coada de comenzi, verificare alocare si initializat stanga si dreapta cu NULL */
}

void IntrQ(TCoada comenzi, char *command)
/* Introducere comanda in coada */
{
    TListaCoada aux = (TListaCoada)malloc(sizeof(TCelulaCoada));
    if(!aux) return;                                                    /* Alocare memorie in coada pentru o noua informatie */

    aux->info = strdup(command);                                        /* Alocare memorie + copiere comanda in noua celula din coada */

    if (comenzi->inc == NULL && comenzi->sf == NULL) {
        aux->urm = NULL;
        aux->pre = NULL;

        comenzi->inc = aux;
        comenzi->sf = aux;                                              /* Coada este goala, legam inceput si sfarsitul cu prima comanda */

    } else {
        aux->urm = NULL;
        aux->pre = comenzi->sf;

        comenzi->sf->urm = aux;
        comenzi->sf = aux;                                              /* Coada are elemente, legam elementul cu ultimul din lista si actualizam sfarsitul de coada */
    }
}

char *extrageComanda(TCoada *comenzi)
/* Extragere comanda din coada */
{
    TListaCoada aux = (*comenzi)->inc;;
    char *command = strdup(aux->info);                                  /* Scoatem prima comanda din coada, alocam + copiem intr-o noua variabila */

    if ((*comenzi)->inc == (*comenzi)->sf) {
        (*comenzi)->inc = NULL;
        (*comenzi)->sf = NULL;                                          /* Daca era singura comanda inceputul si sfarsitul nu mai pointeaza spre nimic */

    } else {
        (*comenzi)->inc = aux->urm;                                     /* Daca nu, facem inceputul cozii sa pointeze spre urmatorul element din coada */
    }
    free(aux->info);
    free(aux);

    return command;                                                     /* Eliberam memoria ocupata de celula din coada si returnam comanda */
}

void printQueue(TCoada comenzi) {                                       /* Functie de verificare pt elementele din coada, irelevanta pt tema */
    TListaCoada aux = comenzi->inc;
    printf("coada: ");
    while (aux != NULL) {
        printf("%s\n", aux->info);
        aux = aux->urm;
    }
    printf("\n");

}

void executeComanda(FILE *fout, TCoada comenzi, Trenulet tren)
/* Identificam + executam comanda din coada */
{
    char *command = extrageComanda(&comenzi);
    char *comm = strtok(command, " ");
    char *new_mecanic = strtok(NULL, " ");                              /* Extragem comanda din coada, o despartim in comanda + elementul care trebuie inserat/schimbat */
                                                                        /* Daca elementul nu exista nu ne folosim de new_mecanic si e si NULL */
    if (strcmp(comm, "MOVE_LEFT") == 0) {
        tren = moveLeft(tren);

    } else if (strcmp(comm, "MOVE_RIGHT") == 0) {
        tren = moveRight(tren);

    } else if (strcmp(comm, "WRITE") == 0) {
        if(new_mecanic != NULL)
            tren = newMecanic(tren, *new_mecanic);

    } else if (strcmp(comm, "CLEAR_CELL") == 0) {
        tren = clearCell(tren);

    } else if (strcmp(comm, "CLEAR_ALL") == 0) {
        tren = clearAll(tren);

    } else if (strcmp(comm, "INSERT_LEFT") == 0) {
        if(new_mecanic != NULL) 
            tren = insertLeft(fout, tren, *new_mecanic);

    } else if (strcmp(comm, "INSERT_RIGHT") == 0) {
        if(new_mecanic != NULL) 
            tren = insertRight(tren, *new_mecanic);

    } else if (strcmp(comm, "SEARCH") == 0) {
        if (new_mecanic != NULL)
            tren = SEARCH(fout, tren, new_mecanic);

    } else if (strcmp(comm, "SEARCH_LEFT") == 0) {
        if (new_mecanic != NULL)
            tren = SEARCH_LEFT(fout, tren, new_mecanic);

    } else if (strcmp(comm, "SEARCH_RIGHT") == 0) {
        if (new_mecanic != NULL)
            tren = SEARCH_RIGHT(fout, tren, new_mecanic);
    }                                                                   /* Secventa de if-else care verifica care comanda este extrasa din coada si apeleaza functia specifica */
                                                                        /* La comenzile care au newvoie de new_mecanic exista si o verificare ca acesta sa fie diferit de NULL */
    free(command);
}

void INPUT(FILE *fin, FILE *fout, TCoada comenzi, Trenulet tren)
/* Functie care se ocupa de input-ul/output-ul din fisier + executare comenzi care nu sunt adaugate in coada */
{
    int numCommands = 0;
    fscanf(fin, "%d", &numCommands);
    fgetc(fin);                                                         /* Citim din fisier numarul de comenzi + newline */

    int i = 0;
    for (i = 0; i < numCommands; i++) {
        char command[20];

        if (fgets(command, sizeof(command), fin)) {                     /* citim fiecare comanda + verificam daca citirea a reusit */
            int len = strlen(command);
            if (len > 0 && command[len - 1] == '\n') {
                command[len - 1] = '\0';
            }                                                           /* Inlocuirea ultimului caracter din newline in sfarsit de sir pt evitarea comportamentului buggy */

            if (strcmp(command, "SHOW_CURRENT") == 0) {
                showCurent(fout, tren);

            } else if (strcmp(command, "SHOW") == 0) {
                showAll(fout, tren);

            } else if (strcmp(command, "SWITCH") == 0) {
                SWITCH(&comenzi);

            } else if (strcmp(command, "EXECUTE") == 0) {
                executeComanda(fout, comenzi, tren);

            } else IntrQ(comenzi, command);                             /* Comenzile de tip QUERY sunt executate pe loc iar celelalte introduse in coada */
        }
    }
}

void DistrugeTren(Trenulet tren)
/* Eliberare memorie tren = lista dublu inlantuita */
{
    TLista2 aux = tren->s->urm;
    while (aux != tren->s) {
        TLista2 delete = aux;
        aux = aux->urm;
        free(delete);
    }
    free(tren->s);
    free(tren);
}

void DistrugeCoada(TCoada comenzi)
/* Elibeare memorie coada = lista dublu inlantuita + eliberare informatie = comanda */
{
    TListaCoada aux = comenzi->inc;
    while (aux != NULL) {
        TListaCoada delete = aux;
        aux = aux->urm;
        if(delete->info != NULL)
            free(delete->info);

        free(delete);
    }
    free(comenzi);
}

int main()
{
    Trenulet tren = InitTL2();
    TCoada comenzi = InitQ();                                               /* Initializare tren + coada comenzi */

    FILE *fin = fopen("tema1.in", "r");
    if(!fin) return 0;
    FILE *fout = fopen("tema1.out", "w");
    if(!fout) return 0;                                                     /* Deschidere fisiere din in/out + verificare */

    INPUT(fin, fout, comenzi, tren);                                        /* Input-ul din fisier este procesat */

    fclose(fin);
    fclose(fout);

    DistrugeTren(tren);
    DistrugeCoada(comenzi);                                                 /* Inchidere fisiere si distrugere tren si coada */

    return 0;
}
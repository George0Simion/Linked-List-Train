# Tren și Cozi de Comenzi

## Cuprins
1. [Implementare Tren și Vagoane](#implementare-tren-și-vagoane)
2. [Coada de Comenzi](#coada-de-comenzi)
3. [Free și Alte Operații](#free-și-alte-operații)
4. [Checker-ul Local](#checker-ul-local)

## Implementare Tren și Vagoane

Pentru implementarea trenului cu vagoane am folosit o coadă dublă înlănțuită cu santinelă circulară declarată în fișierul header `tren.h`. Lista este inițializată la începutul programului în funcția `InitTL2`. În aceeași funcție:
- pun pe mecanic caracterul `#`
- pe santinelă tot `#` (santinela nu va fi afișată niciodată)
- realizez legătura dintre santinelă și mecanic, trenul fiind în starea sa inițială.

Pentru operațiile de tip **QUERY** am creat un fișier nou cu header-ul acestuia. Pentru afișarea mecanicului, funcția `showCurrent` afișează informația de pe mecanic. Pentru afișarea întregului tren, funcția `showAll` parcurge trenul de la prima poziție după santinelă (primul vagon) până la sfârșitul trenului și afișează informația de pe fiecare vagon.

Funcția `Switch` inversează elementele din coada de comenzi, salvând prima dată în final începutul cozii, apoi schimbând legăturile de pe fiecare celulă (comandă), iar în final punând ultima comandă la început.

Operațiile de tip **UPDATE** se află în fișierele `.c` și `.h` ce îi poartă numele:
- `moveLeft` mută mecanicul la stânga dacă nu e pe prima poziție.
- `moveRight` mută mecanicul la dreapta dacă nu e pe ultima poziție. Dacă este pe ultima, creează o nouă celulă, pune informația `#` în aceasta, reface legăturile și mută mecanicul pe această poziție.
- `newMecanic` pune o nouă informație în mecanic.
- `clearCell` eliberează o celulă (distruge un vagon) și reface legăturile dacă trenul nu e în stare inițială.
- `clearAll` eliberează toate vagoanele trenului până la santinelă, după care creează un nou mecanic și reface legăturile.
- `insertLeft` inserează un nou vagon la stânga mecanicului și reface legăturile sau afișează eroare dacă mecanicul e pe prima poziție din tren.
- `insertRight` inserează un nou vagon la dreapta mecanicului și reface legăturile.

Operația de tip **SEARCH** calculează lungimea trenului și a cuvântului căutat și verifică dacă lungimea cuvântului e mai mare decât lungimea trenului. Apoi:
- parcurge trenul pe toată lungimea sa (pornind pe rând de la fiecare element) până când cuvântul este găsit.
- alocă memorie pentru un șir auxiliar în care parcurge elementele de pe fiecare vagon și le pune în șirul auxiliar, sărind peste santinelă.
- compară cuvântul găsit cu cel căutat și, dacă sunt egale, schimbă poziția mecanicului cu startul cuvântului și semaforul devine 1, ieșind din buclă.
- dacă nu găsește cuvântul, trece pe următoarea poziție de start sărind peste mecanic.

Pentru **SEARCH_RIGHT** și **SEARCH_LEFT** logica este similară, cu diferența că parcurgerea se face respectiv în sensul acelor de ceasornic și în sens invers acelor de ceasornic, fără a mai sări peste santinelă la comparare.

## Coada de Comenzi

Pentru implementarea cozii de comenzi am folosit o coadă reprezentată printr-o listă simplu înlănțuită cu doi pointeri, unul la începutul cozii și unul la finalul cozii. La începutul programului:
- initializez coada și pun `inc` și `sf` la NULL.
- în funcția `INPUT` citesc numărul de comenzi, apoi pentru fiecare comandă verific dacă e de tip QUERY (`show`, `show_current`, `switch`) sau `execute`. Dacă nu e de tip `execute`, o introduc în coadă.

Extragerea din coadă se face la întâlnirea comenzii `execute`, unde este apelată funcția `executeComanda`:
- extrage comanda din coadă, folosind un pointer auxiliar care reține începutul cozii și rețin comanda cu ajutorul funcției `strdup`.
- verifică dacă coada e goală. Dacă e goală, pun `inc` și `sf` la NULL, altfel pun `inc` pe următorul element și eliberez memoria pentru auxiliarul unde era începutul.
- comanda extrasă o despart în două cu ajutorul funcției `strtok` și apoi execut operația corespunzătoare.

## Free și Alte Operații

Pentru eliberarea memoriei am creat două funcții:
1. Una pentru eliberarea cozii, unde parcurg coada și eliberez fiecare element.
2. Una pentru eliberarea trenului, unde parcurg trenul și eliberez fiecare vagon.

În final, închid și fișierele de input și output care au fost deschise inițial cu "r" și "w". Pentru fiecare tip de operație am creat un fișier `.c` și `.h` pentru un aspect și o organizare mai bună a codului.

## Checker-ul Local

- README: 5/5
- test1.in: 2.5/2.5
  - Valgrind test.in: 1/1
- test2.in: 2.5/2.5
  - Valgrind test.in: 1/1
- test3.in: 2.5/2.5
  - Valgrind test.in: 1/1
- test4.in: 2.5/2.5
  - Valgrind test.in: 1/1
- test5.in: 5/5
  - Valgrind test.in: 1/1
- test6.in: 2/2
  - Valgrind test.in: 1/1
- test7.in: 2/2
  - Valgrind test.in: 1/1
- test8.in: 2/2
  - Valgrind test.in: 1/1
- test9.in: 3/3
  - Valgrind test.in: 1/1
- test10.in: 3/3
  - Valgrind test.in: 1/1
- test11.in: 5/5
  - Valgrind test.in: 1/1
- test12.in: 5/5
  - Valgrind test.in: 1/1
- test13.in: 5/5
  - Valgrind test.in: 1/1
- test14.in: 5/5
  - Valgrind test.in: 1/1
- test15.in: 2/2
  - Valgrind test.in: 1/1
- test16.in: 2/2
  - Valgrind test.in: 1/1
- test17.in: 2/2
  - Valgrind test.in: 1/1
- test18.in: 5/5
  - Valgrind test.in: 1/1
- test19.in: 5/5
  - Valgrind test.in: 1/1
- test20.in: 5/5
  - Valgrind test.in: 1/1
- test21.in: 5/5
  - Valgrind test.in: 1/1
- test22.in: 3/3
  - Valgrind test.in: 1/1
- test23.in: 3/3
  - Valgrind test.in: 1/1
- test24.in: 3/3
  - Valgrind test.in: 1/1
- test25.in: 3/3
  - Valgrind test.in: 1/1
- test26.in: 2/2
  - Valgrind test.in: 1/1
- test27.in: 2/2
  - Valgrind test.in: 1/1
- test28.in: 2/2
  - Valgrind test.in: 1/1
- test29.in: 2/2
  - Valgrind test.in: 1/1
- test30.in: 2/2
  - Valgrind test.in: 1/1

Total: 100.0/100

Valgrind: 20/20

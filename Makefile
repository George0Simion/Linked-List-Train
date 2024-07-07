#SIMION George Constantin - 313CB

CFLAGS=-Wall -Wextra -Werror

.PHONY: clean run

build: tren.c
	gcc -g tren.c QUERY.c SEARCH.c UPDATE.c tren.h UPDATE.h SEARCH.h QUERY.h $(CFLAGS) -o tema1

run: tema1
	./tema1

valgrind: 
	valgrind -s --leak-check=yes --track-origins=yes ./tema1

clean:
	rm -f tema1

.PHONY: clean install

default: brainf

brainf: brainf.o

.c.o:
	cc -Wall -Wextra -O3 -std=c99 -pedantic -c $< -o $@

clean:
	rm -f *.o brainf

install:
	cp brainf /usr/local/bin/.

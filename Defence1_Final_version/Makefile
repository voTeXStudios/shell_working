# Makefile

CC= gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra
LDFLAGS=
LDLIBS= -lreadline -lm -lncurses


SRC= ls.c functions.c rm.c cat.c cd.c grep.c tree.c calc.c hostname.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END

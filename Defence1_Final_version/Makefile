# Makefile

CC= gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra
LDFLAGS=
LDLIBS= -lreadline


SRC= ls.c functions.c rm.c cat.c cd.c grep.c tree.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END

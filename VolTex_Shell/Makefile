# Makefile

CC= gcc
CPPFLAGS=
CFLAGS= -w -Wall -Wextra
LDFLAGS=
LDLIBS= -lreadline -lm -lncurses


SRC= ls.c echo.c functions.c rm.c cat.c cd.c grep.c alias.c tree.c calc.c redirection.c pipe.c hostname.c main.c env.c tic_tac_toe.c invader.c history.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END

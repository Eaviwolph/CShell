# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -fsanitize=address -g
LDFLAGS =
LDLIBS = 

OBJ = Tools.o Functions.o Shell.o
NAME = MyShell.exe
DEP = ${OBJ:.o=.d}

all: main

main: compil clean

compil: ${OBJ}
		${CC} ${CFLAGS} ${CPPFLAGS} ${OBJ} -o ${NAME}

clean:
		${RM} ${OBJ} ${DEP}

-include ${DEP}

# END

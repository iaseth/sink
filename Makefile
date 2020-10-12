GCC = @gcc

RM = @rm -f

SOURCE = src/main.c
OBJ = build/main.o
BIN = build/sink

default: ${BIN}

${OBJ}: ${SOURCE}
	${GCC} -c ${SOURCE} -o ${OBJ}

${BIN}: ${OBJ}
	${GCC} ${OBJ} -o ${BIN}

redo: clean run

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${OBJ}



GCC = @gcc
INCLUDE_FLAG = -Iinclude

RM = @rm -f

MAIN_SRC = src/main.c
MAIN_OBJ = build/main.o

SINK_SRC = src/sink.c
SINK_OBJ = build/sink.o

BIN = build/sink

default: ${BIN}

${MAIN_OBJ}: ${MAIN_SRC}
	${GCC} -c ${MAIN_SRC} -o ${MAIN_OBJ} ${INCLUDE_FLAG}

${SINK_OBJ}: ${SINK_SRC}
	${GCC} -c ${SINK_SRC} -o ${SINK_OBJ} ${INCLUDE_FLAG}

${BIN}: ${MAIN_OBJ} ${SINK_OBJ}
	${GCC} ${MAIN_OBJ} ${SINK_OBJ} -o ${BIN}

redo: clean run

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${MAIN_OBJ}
	${RM} ${SINK_OBJ}



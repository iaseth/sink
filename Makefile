AMP = @

GCC = ${AMP}gcc
INCLUDE_FLAG = -Iinclude
LINK_FLAG = -lcurl

RM = ${AMP}rm -f

MAIN_SRC = src/main.c
MAIN_OBJ = build/main.o

SINK_SRC = src/sink.c
SINK_OBJ = build/sink.o

BIN = build/sink

default: ${BIN}

debug:
	${eval AMP := }

${MAIN_OBJ}: ${MAIN_SRC}
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${SINK_OBJ}: ${SINK_SRC}
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${BIN}: ${MAIN_OBJ} ${SINK_OBJ}
	${GCC} $^ -o $@ ${LINK_FLAG}

redo: clean default

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${MAIN_OBJ}
	${RM} ${SINK_OBJ}



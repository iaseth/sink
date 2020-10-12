AMP = @

GCC = ${AMP}gcc
INCLUDE_FLAG = -Iinclude
LINK_FLAG = -lcurl

RM = ${AMP}rm -f

SINK_NAMES = sink
SINK_NAMES += sink_label
SINK_NAMES += sink_object

SINK_OBJ_NAMES = ${addsuffix .o, ${SINK_NAMES}}
SINK_OBJS = ${addprefix build/, ${SINK_OBJ_NAMES}}

MAIN_SRC = src/main.c
MAIN_OBJ = build/main.o

BIN = build/sink

default: ${BIN}

debug:
	${eval AMP := }

${MAIN_OBJ}: ${MAIN_SRC}
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${SINK_OBJS}: build/%.o: src/%.c include/%.h
	${GCC} -c $< -o $@ ${INCLUDE_FLAG}

${BIN}: ${MAIN_OBJ} ${SINK_OBJS}
	${GCC} $^ -o $@ ${LINK_FLAG}

redo: clean default

run: ${BIN}
	@${BIN}

move:
	sudo cp ${BIN} /usr/bin

clean:
	${RM} ${BIN}
	${RM} ${MAIN_OBJ}
	${RM} ${SINK_OBJS}



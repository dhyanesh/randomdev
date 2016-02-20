CC = g++
CFLAGS = -O2
FLAGS = -lm -lprofiler
OUTPUT = bin

all: ${OUTPUT} ${OUTPUT}/MultiplayerReversi

${OUTPUT}:
	mkdir $@

${OUTPUT}/MultiplayerReversi: ${OUTPUT}/MultiplayerReversi.o
	${CC} ${OUTPUT}/MultiplayerReversi.o ${FLAGS} -o $@

${OUTPUT}/%.o: %.cc
	${CC} -c $< ${CFLAGS} -o $@

clean:
	rm -f ${OUTPUT}/MultiplayerReversi ${OUTPUT}/*.o

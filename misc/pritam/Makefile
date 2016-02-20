CC = g++
CFLAGS = -g

checkers: checkers1.cpp bitboard.o
	${CC} checkers1.cpp bitboard.o ${CFLAGS} -o checkers

bitboard.o: bitboard.cc bitboard.h
	${CC} -c bitboard.cc ${CFLAGS}

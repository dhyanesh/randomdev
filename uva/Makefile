CC = g++
FLAGS = -g -lm

% : %.cpp
	${CC} ${FLAGS} -o out/$@ $@.cpp
% : %.cc
	${CC} ${FLAGS} -o out/$@ $@.cc

clean:
	rm -f out/* 

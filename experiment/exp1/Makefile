VPATH = ./src ../../src ../../include
FLAGS = -I../../include 
COMPILADOR=g++

all: experimento1

experimento1: experimento1.cpp
	@mkdir -p bin
	$(COMPILADOR) $(FLAGS) ../../objects/DinamicaMotores.o ./src/experimento1.cpp  -o ./bin/experimento1

clean:
	rm -Rf bin

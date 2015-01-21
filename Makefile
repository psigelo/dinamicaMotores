VPATH = ./src ./include
FLAGS = -I./include
COMPILADOR=g++

all: DinamicaMotores.o


DinamicaMotores.o: DinamicaMotores.cpp
	@mkdir -p objects
	$(COMPILADOR) $(FLAGS) -c ./src/DinamicaMotores.cpp -o ./objects/DinamicaMotores.o

clean:
	rm -Rf objects bin

#
# Makefile 
#

CCC      = g++
FLAGS += -std=c++17 -pedantic -Wall -Wextra -Weffc++ -pthread
SFML_FLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDE_SFML += -I${SFML_ROOT}/include -L${SFML_ROOT}/lib

OBJECTS = screen.o piece.o piece1.o piece2.o piece3.o piece4.o piece5.o piece6.o piece7.o



tetris: bin ${OBJECTS} Makefile src/tetris.cc screen.o
	${CCC} ${FLAGS} src/tetris.cc ${OBJECTS} -o bin/game ${INCLUDE_SFML} ${SFML_FLAGS}	

screen.o: src/screen.h src/screen.cc piece.o piece1.o piece2.o piece3.o piece4.o piece5.o piece6.o piece7.o
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/screen.cc

piece.o: src/piece.h src/piece.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece.cc

piece1.o: src/piece1.h src/piece1.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece1.cc

piece2.o: src/piece2.h src/piece2.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece2.cc

piece3.o: src/piece3.h src/piece3.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece3.cc

piece4.o: src/piece4.h src/piece4.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece4.cc

piece5.o: src/piece5.h src/piece5.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece5.cc

piece6.o: src/piece6.h src/piece6.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece6.cc

piece7.o: src/piece7.h src/piece7.cc
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/piece7.cc

directories: 
	@ \mkdir -p bin

bin:
	@ \mkdir -p bin
clean:
	@ \rm -f *.o *.gch
	@ \rm -r -f bin
zap:
	@ \rm -f -v *.~
	@ \rm -f -v *.~*
	@ \rm -f -v src/*.~
	@ \rm -f -v src/*.~*
	@ \rm -f -v src/*#
	@ \rm -f -v src/#*

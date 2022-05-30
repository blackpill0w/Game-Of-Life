CXX = g++
CXXFLAGS = -Wall -Weffc++ -Wextra -Wsign-conversion
LDFLAGS = -l sfml-window -l sfml-system -l sfml-graphics

SRC=src
SFML-UTILS=SFML-utilities

game_of_life: constants.o cell.o sfmlColors.o button.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} $? ${SRC}/main.cpp -o $@
constants.o: ${SRC}/constants.cpp
	${CXX} ${CXXFLAGS} -c $?
cell.o: ${SRC}/cell.cpp
	${CXX} ${CXXFLAGS} -c $?
sfmlColors.o: ${SRC}/${SFML-UTILS}/sfmlColors.cpp
	${CXX} ${CXXFLAGS} -c $?
button.o: ${SRC}/${SFML-UTILS}/button.cpp
	${CXX} ${CXXFLAGS} -c $?

clean:
	rm -rf game_of_life *.o

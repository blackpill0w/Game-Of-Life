CXX = g++
CXXFLAGS = -Wall -Weffc++ -Wextra -Wsign-conversion
LDFLAGS = -l sfml-window -l sfml-system -l sfml-graphics

game_of_life: constants.o cell.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} $? main.cpp -o $@
constants.o: constants.cpp
	${CXX} ${CXXFLAGS} -c constants.cpp -o $@
cell.o: cell.cpp
	${CXX} ${CXXFLAGS} -c cell.cpp -o $@

clean:
	rm -rf game_of_life *.o
CXX = g++
CXXFLAGS = -Wall -Weffc++ -Wextra -Wsign-conversion
LDFLAGS = -l sfml-window -l sfml-system -l sfml-graphics

game_of_life: constants.o cell.o
	${CXX} ${CXXFLAGS} ${LDFLAGS} $? src/main.cpp -o $@
constants.o: src/constants.cpp
	${CXX} ${CXXFLAGS} -c $? -o $@
cell.o: src/cell.cpp
	${CXX} ${CXXFLAGS} -c $? -o $@

clean:
	rm -rf game_of_life *.o

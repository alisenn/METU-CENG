LDFLAGS=-ansi -pedantic

all: ; g++ $(LDFLAGS) Particle.cpp Wall.cpp CurvyWall.cpp Cell.cpp MicroOrganism.cpp NucleoBase.cpp Triangular.cpp Circular.cpp Squadratic.cpp Tissue.cpp Main.cpp -o hw4
wall_tests: ; g++ $(LDFLAGS) Particle.cpp Wall.cpp CurvyWall.cpp WallTests.cpp -o hw4
cell_tests: ; g++ $(LDFLAGS) Particle.cpp Wall.cpp CurvyWall.cpp Cell.cpp MicroOrganism.cpp NucleoBase.cpp Triangular.cpp Tissue.cpp CellTests.cpp -o hw4
microorganism_tests: ; g++ $(LDFLAGS) Particle.cpp Wall.cpp CurvyWall.cpp Cell.cpp MicroOrganism.cpp NucleoBase.cpp Triangular.cpp Circular.cpp Squadratic.cpp Tissue.cpp MicroorganismTests.cpp -o hw4
run: ;./hw4 input/cells.txt input/microorganisms.txt
valgrind: ; valgrind --leak-check=full ./hw4 input/cells.txt input/microorganisms.txt
clean: ; rm -rf hw4

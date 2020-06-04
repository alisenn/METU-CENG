LDFLAGS=-std=c++11

1: ; g++ $(LDFLAGS) Book.cpp HardCopy.cpp SoftCopy.cpp TestGroup1.cpp -o Test
2: ; g++ $(LDFLAGS) Book.cpp HardCopy.cpp SoftCopy.cpp TestGroup2.cpp -o Test
3: ; g++ $(LDFLAGS) Book.cpp HardCopy.cpp SoftCopy.cpp TestGroup3.cpp -o Test
4: ; g++ $(LDFLAGS) Book.cpp HardCopy.cpp SoftCopy.cpp TestGroup4.cpp -o Test
5: ; g++ $(LDFLAGS) Book.cpp HardCopy.cpp SoftCopy.cpp TestGroup5.cpp -o Test
run: ;./Test
valgrind: ; valgrind --leak-check=full ./Test
clean: ; rm -rf Test

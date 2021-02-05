all:
	g++ -O3 *.cpp -c -std=c++11 -march=native -ljpeg -lm
	g++ *.o -o raytracer -lpthread -ljpeg -lm

clean:
	rm -f *.o

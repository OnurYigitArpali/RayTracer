all:
	g++ *.cpp -o main -std=c++11 -ljpeg -lpthread -march=native -O3
clean:
	rm -f *.o

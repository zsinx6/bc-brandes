all:
	g++ graph.cpp brandes.cpp -o brandes -Wall
clean:
	rm brandes

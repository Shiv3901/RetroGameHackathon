all: hello.cpp
	g++ hello.cpp -lncurses -o hello
	./hello

colour: colour.cpp
	g++ colour.cpp -lncurses -o colour
	./colour

grid: grid.cpp
	g++ grid.cpp -lncurses -o grid
	./grid
all: 2048

2048: 2048_UI.cpp ./header/2048.cpp
	clang++ --std=c++20 2048_UI.cpp ./header/2048.cpp -o 2048 -lSDL2 -lSDL2_ttf
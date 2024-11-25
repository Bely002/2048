all: 2048UI

2048UI: main.cpp jeu.cpp dessin.cpp
	clang++ --std=c++20 -o 2048UI main.cpp jeu.cpp dessin.cpp -lSDL2 -lSDL2_ttf
	
clean:
	rm -f 2048UI

.PHONY: all clean


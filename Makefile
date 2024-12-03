.PHONY : Console Ncurses UI Tests IA help

Console: ./Console/2048_Console.cpp ./header/2048.cpp
	clang++ --std=c++20 ./Console/2048_Console.cpp ./header/2048.cpp -o 2048

Ncurses: ./Ncurses/2048_Ncurses.cpp ./header/2048.cpp
	clang++ --std=c++20 ./Ncurses/2048_Ncurses.cpp ./header/2048.cpp -o 2048 -lncurses

UI: ./UI/2048_UI.cpp ./header/2048.cpp
	clang++ --std=c++20 ./UI/2048_UI.cpp ./header/2048.cpp -o 2048 -lSDL2 -lSDL2_ttf

Tests: ./Tests/2048_Tests.cpp ./header/2048.cpp
	clang++ --std=c++20 ./Tests/2048_Tests.cpp ./header/2048.cpp -o 2048_Tests

IA: ./IA/2048_IA.cpp ./header/2048.cpp
	clang++ --std=c++20 ./IA/2048_IA.cpp ./header/2048.cpp -o 2048_IA

help:
	@echo "\nListe des commandes :"
	@echo "	make Console	- Compile 2048 en version console (./2048)"
	@echo "	make Ncurses	- Compile 2048 en version console colorée avec ncurses (./2048)"
	@echo "	make UI		- Compile 2048 avec une interface graphique avec SDL2 (./2048)"
	@echo "	make IA		- Compile l'IA de 2048 (./2048_IA)"
	@echo "	make Tests	- Compile les tests de la bibliothèque 2048 (./2048_Tests)\n"
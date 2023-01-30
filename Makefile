all:
	g++ -std=c++17 -mwindows -Wall -O3 -I include source/main.cpp source/program.cpp SDL2.dll SDL2_image.dll -o program_for_genshin.exe
	.\program_for_genshin.exe

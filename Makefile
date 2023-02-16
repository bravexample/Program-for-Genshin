all:
	gcc -std=c17 -mwindows -Wall -O3 -I include main.c SDL2.dll -o program_for_genshin.exe
	.\program_for_genshin.exe

all:
	gcc -mwindows -Wall -O3 -I include source/main.c source/program.c SDL2.dll SDL2_image.dll -o program_for_genshin.exe
	.\program_for_genshin.exe
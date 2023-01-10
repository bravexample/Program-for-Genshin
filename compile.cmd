@echo off

gcc -mwindows -Wall -O3 -I include source/main.c SDL2.dll SDL2_image.dll -o sdl_yoimiya_macro.exe
.\sdl_yoimiya_macro.exe
@echo off

cl /O2 /Fe:Program-for-Genshin /std:c17 /sdl /Wall /WX main.c User32.lib Gdi32.lib
del *.obj
Program-for-Genshin.exe
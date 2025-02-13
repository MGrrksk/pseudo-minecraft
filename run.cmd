@echo off
setlocal

set flags=-Wall
set include=-Iinclude -Idependencies/include
set libDir=-Ldependencies/lib
set src=src/*.cpp src/graphics/*.cpp dependencies/src/*.c
set target=bin/minecraft
set libs=-lglfw3dll

g++ %flags% %include% %libDir% %src% -o %target% %libs%
start /b /wait %target%
endlocal
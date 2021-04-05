INCLUDE_PATH="D:\thirdparty\mingw32\include"
LIB_PATH="D:\thirdparty\mingw32\lib"

main:
	g++ -Wall -Wextra -Werror -g *.cpp glad.c -o ..\build\main.exe -I$(INCLUDE_PATH) -L$(LIB_PATH) -lmingw32 -lSDL2main -lSDL2 -lopengl32
run:
	..\build\main.exe

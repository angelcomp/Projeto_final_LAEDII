#CPP = clang++
#C = clang
CPP = g++
C = gcc

### 32 bit Windows

#LDFLAGS = -LC:\SDL2-2.0.8\i686-w64-mingw32\lib \
-LC:\SDL2_ttf-2.0.14\i686-w64-mingw32\lib \
-LC:\SDL2_image-2.0.3\i686-w64-mingw32\lib \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
-mwindows -m32 -march=i686
#CFLAGS = -IC:\SDL2-2.0.8\i686-w64-mingw32\include \
-IC:\SDL2-2.0.8\i686-w64-mingw32\include\SDL2 \
-IC:\SDL2_ttf-2.0.14\i686-w64-mingw32\include \
-IC:\SDL2_image-2.0.3\i686-w64-mingw32\include \
-Wall -c -std=c89 -m32 -march=i686
#BIN1 = hello.exe
#BIN2 = kiss_example2.exe

### 64 bit Windows

#LDFLAGS = -LC:\SDL2-2.0.8\x86_64-w64-mingw32\lib \
-LC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\lib \
-LC:\SDL2_image-2.0.3\x86_64-w64-mingw32\lib \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
-mwindows
#CFLAGS = -IC:\SDL2-2.0.8\x86_64-w64-mingw32\include \
-IC:\SDL2-2.0.8\x86_64-w64-mingw32\include\SDL2 \
-IC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\include \
-IC:\SDL2_image-2.0.3\x86_64-w64-mingw32\include \
-Wall -c -std=c89
#BIN1 = hello.exe
#BIN2 = kiss_example2.exe

### macOS

#LDFLAGS = -framework SDL2 -framework SDL2_ttf -framework SDL2_image
#CFLAGS = -I/Library/Frameworks/SDL2.framework/Headers \
-I/Library/Frameworks/SDL2_ttf.framework/Headers \
-I/Library/Frameworks/SDL2_image.framework/Headers \
-Wall -c -std=c89
#BIN1 = hello
#BIN2 = kiss_example2

### Linux

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -Wall -c -std=c99
BIN = restaurante

KISS_SRC = src/kiss_sdl

KISS_RES = kiss_resources

all: $(BIN) cp_files clean_objs

$(BIN): main.o lista.o fila.o utils.o opcoes_menu.o kiss_widgets.o kiss_draw.o kiss_general.o \
kiss_posix.o
	$(C) $^ $(LDFLAGS) -o $@

main.o: src/main.c
	$(C) $(CFLAGS) $^ -o $@
lista.o: src/lista.c
	$(C) $(CFLAGS) $^ -o $@
fila.o: src/fila.c
	$(C) $(CFLAGS) $^ -o $@
utils.o: src/utils.c
	$(C) $(CFLAGS) $^ -o $@
opcoes_menu.o: src/opcoes_menu.c
	$(C) $(CFLAGS) $^ -o $@


kiss_example2.o: $(KISS_SRC)/kiss_example2.c
	$(C) $(CFLAGS) $^ -o $@

kiss_widgets.o: $(KISS_SRC)/kiss_widgets.c
	$(C) $(CFLAGS) $^ -o $@

kiss_draw.o: $(KISS_SRC)/kiss_draw.c
	$(C) $(CFLAGS) $^ -o $@

kiss_general.o: $(KISS_SRC)/kiss_general.c
	$(C) $(CFLAGS) $^ -o $@

kiss_posix.o: $(KISS_SRC)/kiss_posix.c
	$(C) $(CFLAGS) $^ -o $@

cp_files:
	mkdir -p $(KISS_RES)
	cp $(KISS_SRC)/*.png $(KISS_RES)
	cp $(KISS_SRC)/*.ttf $(KISS_RES)

clean_objs:
	rm *.o

clean:
	clean_objs rm $(BIN) && rm -r $(KISS_RES)
#	del *.o
#	del $(BIN1)
#	del $(BIN2)


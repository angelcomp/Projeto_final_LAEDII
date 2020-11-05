CPP = g++
C = gcc

UNAME = ${shell uname}

### 64 bit Windows
ifneq ($(UNAME),Linux)
	LDFLAGS = -LC:\SDL2-2.0.8\x86_64-w64-mingw32\lib \
	-LC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\lib \
	-LC:\SDL2_image-2.0.3\x86_64-w64-mingw32\lib \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
	-mwindows
	CFLAGS = -IC:\SDL2-2.0.8\x86_64-w64-mingw32\include \
	-IC:\SDL2-2.0.8\x86_64-w64-mingw32\include\SDL2 \
	-IC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\include \
	-IC:\SDL2_image-2.0.3\x86_64-w64-mingw32\include \
	-Wall -c -std=c99
	BIN = restaurante.exe
	KISS_SRC = src\kiss_sdl
	KISS_RES = kiss_resources
else ### Linux
	LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
	CFLAGS = -Wall -c -std=c99
	BIN = restaurante
	KISS_SRC = src/kiss_sdl
	KISS_RES = kiss_resources
endif


all: $(BIN) cp_files remove_objs
	echo $(UNAME)

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

remove_objs:
	rm -f *.o

clean: remove_objs
	rm -f $(BIN)
	rm -rf $(KISS_RES)
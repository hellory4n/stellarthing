CC = gcc
CXX = g++
WINCC = x86_64-w64-mingw32-gcc
WINCXX = x86_64-w64-mingw32-g++
CFLAGS = -Wall -O2
LDFLAGS = -lglfw -ldl -lGL
WIN_LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -lkernel32 -luser32
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%, bin/%, $(SRC:.c=.o))
WIN_OBJ = $(patsubst src/%, bin/%, $(SRC:.c=_win.o))
TARGET = bin/stellarthing
WIN_TARGET = bin/stellarthing.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

windows: $(WIN_TARGET)

$(WIN_TARGET): $(WIN_OBJ)
	$(WINCC) $(WIN_LDFLAGS) -o $@ $^

bin/%_win.o: src/%.c
	@mkdir -p bin
	$(WINCC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf bin

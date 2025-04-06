CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -fno-strict-aliasing \
         -I. -Ivendor/libtrippin -Ivendor/raylib/include
LDFLAGS =

# put the bloody files here
SRCS = main.c \
    vendor/libtrippin/libtrippin.c \
    vendor/stb_ds.c \
    vendor/rlFPCamera.c \
    vendor/FastNoiseLite.c \
    player/control/player_controller.c \
    core/graphics.c

OBJS = $(SRCS:.c=.o)

PLATFORM := $(shell uname -s)
ifeq ($(PLATFORM),Linux)
    OS := linux
else ifeq ($(PLATFORM),Windows_NT)
    OS := windows
endif

ifeq ($(OS),windows)
    TARGET := stellarthing.exe
else
    TARGET := stellarthing
endif

# i dont think mingw has clang
# or at least the toolchain raylib for windows installs
ifeq ($(OS),windows)
    CC = gcc
endif

# lmao
ifeq ($(build),debug)
    CFLAGS += -g -fsanitize=address -DDEBUG
else ifeq ($(build),noasan)
    CFLAGS += -g -DDEBUG
else
    CFLAGS += -O2 -DRELEASE
endif

ifeq ($(OS),windows)
    # -Wl,--subsystem,windows hides the console window
    LDFLAGS += -Lvendor/raylib/lib/windows -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32 -Wl,--subsystem,windows,-rpath=.
else ifeq ($(OS),linux)
    LDFLAGS += -Lvendor/raylib/lib/linux -lraylib -lGL -lm -lpthread -ldl -lrt -Wl,-rpath=.
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
    ifeq ($(OS),windows)
    cp vendor/raylib/lib/windows/raylib.dll raylib.dll
    else
    cp vendor/raylib/lib/linux/libraylib.so.5.5.0 libraylib.so.550
    endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) log.txt

run: $(TARGET)
	./$(TARGET)

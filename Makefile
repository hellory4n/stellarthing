CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -fno-strict-aliasing \
         -I. -Ivendor -Ivendor/libtrippin -Ivendor/raylib/include
LDFLAGS = -L.

# put the bloody files here
SRCS = main.c \
    vendor/libtrippin/libtrippin.c \
    vendor/stb_ds.c \
    vendor/rlFPCamera.c \
    vendor/FastNoiseLite.c \
    player/control/player_controller.c \
    core/graphics.c \
    player/debug/console.c

OBJS = $(SRCS:.c=.o)

PLATFORM := $(shell uname -s)
ifeq ($(PLATFORM),Linux)
    OS = linux
else ifeq ($(PLATFORM),Windows_NT)
    OS = windows
endif

# cross compiling lmao
ifeq ($(platform),windows)
    CROSSCOMPILE = true
    OS = windows
endif

ifeq ($(OS),windows)
    TARGET := stellarthing.exe
else
    TARGET := stellarthing
endif

# i dont think mingw has clang
# or at least the toolchain raylib for windows installs
ifeq ($(OS),windows)
    ifeq ($(CROSSCOMPILE),true)
        CC = x86_64-w64-mingw32-gcc
    else
        CC = gcc
    endif
endif

# lmao
ifeq ($(build),debugasan)
    CFLAGS += -O0 -g -DDEBUG -fsanitize=address
else ifeq ($(build),debug)
    CFLAGS += -O0 -g -DDEBUG
else
    CFLAGS += -O2 -DRELEASE
endif

ifeq ($(OS),windows)
    # -Wl,--subsystem,windows hides the console window
    LDFLAGS += -Lvendor/raylib/lib/windows -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32 -Wl,--subsystem,windows,-rpath=. -static
else ifeq ($(OS),linux)
    LDFLAGS += -Lvendor/raylib/lib/linux -lraylib -lGL -lm -lpthread -ldl -lrt -Wl,-rpath=.
endif

ifeq ($(OS),windows)
    DLLCOPYCMD := vendor/raylib/lib/windows/raylib.dll raylib.dll
else
    DLLCOPYCMD := vendor/raylib/lib/linux/libraylib.so.5.5.0 libraylib.so.550
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ && cp $(DLLCOPYCMD)

clean:
	rm -f $(OBJS) $(TARGET) log.txt libraylib.so.550 raylib.dll

run: $(TARGET)
	./$(TARGET)

CC = clang
CFLAGS = -std=c99 -Wall -Wextra -I. -Ivendor/libtrippin -Ivendor/raylib/include
LDFLAGS =

# put the bloody files here
SRCS = main.c \
    vendor/libtrippin/libtrippin.c

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
else
    CFLAGS += -O2 -DRELEASE
endif

# link raylib
ifeq ($(OS),windows)
    # -Wl,--subsystem,windows hides the console window
    LDFLAGS += -Lraylib/windows -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32 -Wl,--subsystem,windows
else ifeq ($(OS),linux)
    LDFLAGS += -Lraylib/linux -lraylib -lGL -lm -lpthread -ldl -lrt
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

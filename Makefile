

CC=gcc
SHARED=pidgin-rdchooser.so
CFLAGS=-Os -g -Wall `pkg-config --cflags purple`
LDFLAGS=-Os -shared -Wall `pkg-config --libs purple`
SOURCES=$(wildcard src/*.c)
MODULES=$(patsubst src/%.c,build/%.o,$(SOURCES))

all: $(SHARED)

$(SHARED): $(MODULES)
	@$(CC) $(LDFLAGS) $^ -o $@

build/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm $(MODULES)

mrproper: clean
	@rm $(SHARED)

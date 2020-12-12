.PHONY: all
all: build

.PHONY: build
build:
	$(CC) -Isrc $(wildcard src/*.c) -obfi

.PHONY: clean
clean:
	rm -f ./bfi

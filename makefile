all:
	gcc ./src/*.c -I./include -o elektra.out -lm

run:
	./elektra.out

clean:
	rm elektra.out

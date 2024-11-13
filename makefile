CC = gcc
CFLAGS = -I./include
LDFLAGS = -lm

# Lista de arquivos fonte
SRC = ./src/main.c ./src/screen.c ./src/keyboard.c ./src/timer.c 

# Nome do executável
TARGET = elektra.out

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

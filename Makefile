CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_mixer

SRC_DIR = src
BUILD_DIR = build
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
BIN = vibes

# Detecta o sistema
ifeq ($(OS),Windows_NT)
    BIN := $(BIN).exe
    # Ajuste do include do SDL2 no Windows/Git Bash (alterar se seu SDL2 estiver em outro lugar)
    CFLAGS += -IC:/SDL2/include
    LDFLAGS += -LC:/SDL2/lib -lmingw32
else
    # Linux/WSL
    CFLAGS += -I/usr/include/SDL2
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN)

run: $(BIN)
ifeq ($(OS),Windows_NT)
	@./$(BIN)
else
	@./$(BIN)
endif

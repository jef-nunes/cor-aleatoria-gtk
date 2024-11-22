# Makefile de um projeto GTK4

# Flags do compilador
CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags gtk4)
LDFLAGS = $(shell pkg-config --libs gtk4)

# Diretórios
SRC_DIR = src
LIB_DIR = src/lib
OBJ_DIR = obj
BIN_DIR = bin

# Arquivo executável (resultado)
TARGET = $(BIN_DIR)/app

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regras padrão
all: $(TARGET)

# Criar diretórios se não existem
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_DIR)/*.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkar o executável
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Apagar arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Apaga arquivos e recompila
rebuild: clean all

# Guia de comandos
help:
	@echo "Comandos disponíveis:"
	@echo "  make        - Compila o projeto"
	@echo "  make clean  - Remove arquivos gerados"
	@echo "  make help   - Exibe esta mensagem de ajuda"


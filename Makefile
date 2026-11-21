CC = g++
CFLAGS = -std=c++11 -Wall -fsanitize=address -g -fno-omit-frame-pointer 
# Adicione essa flag ao final de CFLAGS para adicionar a coleta de dados no código -DANALISES

SRC_DIR = ./src
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
OUT_DIR = ./bin

TARGET = $(OUT_DIR)/tp1.out

OBJ = $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/Atributo.o \
	  $(OBJ_DIR)/Aventureiro.o \

all: $(TARGET)

$(OBJ_DIR)/Atributo.o: $(INCLUDE_DIR)/Atributo.hpp $(SRC_DIR)/Atributo.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Atributo.cpp -o $(OBJ_DIR)/Atributo.o

$(OBJ_DIR)/Cliente.o: $(INCLUDE_DIR)/Cliente.hpp $(SRC_DIR)/Cliente.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Cliente.cpp -o $(OBJ_DIR)/Cliente.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/main.cpp  -o $(OBJ_DIR)/main.o

$(TARGET): $(OBJ)
	${CC} ${CFLAGS} $(OBJ) -o $(TARGET)

# Rule for cleaning files generated during compilation.
# Call 'make clean' to use it
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)

run: $(TARGET)
	$(TARGET)
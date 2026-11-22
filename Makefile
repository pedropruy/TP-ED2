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
	  $(OBJ_DIR)/Cliente.o \
	  $(OBJ_DIR)/Indice.o \
	  $(OBJ_DIR)/Heap.o \
	  $(OBJ_DIR)/DSU.o \
	  $(OBJ_DIR)/Mapa.o \
	  $(OBJ_DIR)/Consultoria.o \
	  $(OBJ_DIR)/Entrada.o \

all: $(TARGET)

$(OBJ_DIR)/Atributo.o: $(INCLUDE_DIR)/Atributo.hpp $(SRC_DIR)/Atributo.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Atributo.cpp -o $(OBJ_DIR)/Atributo.o

$(OBJ_DIR)/Cliente.o: $(INCLUDE_DIR)/Cliente.hpp $(SRC_DIR)/Cliente.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Cliente.cpp -o $(OBJ_DIR)/Cliente.o

$(OBJ_DIR)/Indice.o: $(SRC_DIR)/TabelaHash.cpp $(SRC_DIR)/ArvoreAVL.cpp $(INCLUDE_DIR)/Indice.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TabelaHash.cpp -o $(OBJ_DIR)/TabelaHash.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ArvoreAVL.cpp -o $(OBJ_DIR)/ArvoreAVL.o
	ld -r $(OBJ_DIR)/TabelaHash.o $(OBJ_DIR)/ArvoreAVL.o -o $@
	rm $(OBJ_DIR)/TabelaHash.o $(OBJ_DIR)/ArvoreAVL.o 

$(OBJ_DIR)/Heap.o: $(INCLUDE_DIR)/Heap.hpp $(SRC_DIR)/Heap.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Heap.cpp -o $(OBJ_DIR)/Heap.o

$(OBJ_DIR)/DSU.o: $(INCLUDE_DIR)/DSU.hpp $(SRC_DIR)/DSU.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/DSU.cpp -o $(OBJ_DIR)/DSU.o

$(OBJ_DIR)/Mapa.o: $(INCLUDE_DIR)/Mapa.hpp $(SRC_DIR)/Mapa.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Mapa.cpp -o $(OBJ_DIR)/Mapa.o

$(OBJ_DIR)/Consultoria.o: $(INCLUDE_DIR)/Consultoria.hpp $(SRC_DIR)/Consultoria.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Consultoria.cpp -o $(OBJ_DIR)/Consultoria.o

$(OBJ_DIR)/Entrada.o: $(INCLUDE_DIR)/Entrada.hpp $(SRC_DIR)/Entrada.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Entrada.cpp -o $(OBJ_DIR)/Entrada.o

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
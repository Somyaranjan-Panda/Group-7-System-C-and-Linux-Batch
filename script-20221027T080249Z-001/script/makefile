CC = gcc

INC = inc
OBJ = obj
SRC = src
BIN = bin
LDFLAGS = -o
CFLAGS = -c -g -Wall
IFLAGS = -I $(INC)/

all: $(BIN)/ias

$(BIN)/ias: $(OBJ)/ias_source.o $(OBJ)/ias_main.o
	$(CC) $(LDFLAGS) $(BIN)/ias $(OBJ)/ias_source.o $(OBJ)/ias_main.o

$(OBJ)/ias_main.o: $(SRC)/ias_main.c 
	$(CC) $(CFLAGS) $(SRC)/ias_main.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/ias_source.o: $(SRC)/ias_source.c
	$(CC) $(CFLAGS) $(SRC)/ias_source.c $(IFLAGS)
	mv *.o $(OBJ)/


clean:
	rm -f a.out *.o
	rm -f $(BIN)/*
	rm -f $(OBJ)/*.o
	@echo "Cleaning Done!"

.PHONY: clean dirs

BIN=bin
SRC=src
OBJ=obj
LIBS=-lglut -lGLU -lGL

all: dirs $(BIN)/myOpenGlApp

$(BIN)/myOpenGlApp: $(SRC)/main.cpp $(OBJ)/object.o $(SRC)/vertex.h $(SRC)/face.h | $(BIN)
	g++ -Wall -std=c++11 $< $(OBJ)/object.o $(LIBS) -o $@

$(OBJ)/object.o: $(SRC)/object.cpp $(SRC)/object.h | $(OBJ)
	g++ -Wall -std=c++11 -c $< -o $@ $(LIBS)

dirs:
	mkdir -p $(SRC) $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)

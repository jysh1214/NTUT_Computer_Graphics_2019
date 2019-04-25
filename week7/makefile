.PHONY: clean dirs

BIN=bin
SRC=src
OBJ=obj
LIBS=-lglut -lGLU -lGL

all: dirs $(BIN)/myOpenGlApp

$(BIN)/myOpenGlApp: $(SRC)/main.cpp $(SRC)/sqr.h $(SRC)/grid.h | $(BIN)
	g++ -Wall -std=c++11 $< $(LIBS) -o $@

dirs:
	mkdir -p $(SRC) $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)

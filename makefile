PROJECT = blocks

CXX = clang++
CFLAGS = -Wall -Wextra --std=c++17 -O2
LIBS = -lGLEW -lX11 -lGLU -lGL -lpng16 -lz -lpthread

SRC = src
OBJ = obj
INC = include

INCLUDE = -I$(INC)

$(PROJECT): GameCore Main Projector
	$(CXX) $(CFLAGS) $(LIBS) $(patsubst %,$(OBJ)/%.o,$^) -o $@

Projector: %: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(LIBS) -c $< -o $(OBJ)/$@.o $(INCLUDE)

GameCore: %: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(LIBS) -c $< -o $(OBJ)/$@.o $(INCLUDE)

Main: %: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(LIBS) -c $< -o $(OBJ)/$@.o $(INCLUDE)

clean:
	@echo Removing obj files...
	@rm -f $(OBJ)/*.o $(PROJECT)

.PHONY: clean print
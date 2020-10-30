APP=esdeel02

CXX      = clang++
LIBS     = -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL_mixer -lpthread
CXXFLAGS =  -std=c++17 -Wall -Wc++17-extensions
LDFLAGS  = $(CXXFLAGS) $(LIBS) -L./lib

# Folders
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(BIN_DIR)/$(APP): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ 

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += -DDEBUG -g
debug: $(BIN_DIR)/$(APP) 

clean:
	$(RM) build/obj/* build/bin/*

.PHONY: all clean


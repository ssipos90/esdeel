APP=esdeel02

CXX      = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS  = $(CXXFLAGS) -L./lib
LIBS     = -lmylib -lm

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

clean:
	$(RM) build/obj/* build/bin/*

.PHONY: all clean


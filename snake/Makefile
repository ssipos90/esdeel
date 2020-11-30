APP=esdeel02

CXX      = clang++
LIBS     = -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread
DBGFLAGS = CXXFLAGS += -DDEBUG -g
CXXFLAGS = -std=c++17 -Wc++17-extensions -Wall -Werror -Wextra
LDFLAGS  = $(CXXFLAGS) $(LIBS) -L./lib -MMD

# Folders
SRC_DIR = src
OBJ_DIR = build/obj

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJECTS:.o=.d)

$(APP): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ 
-include $(DEPS)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(APP)

debug: $(DBGFLAGS)
debug: $(APP)

clean:
	$(RM) build/obj/* $(APP)

.PHONY: clean all

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

EXE = $(BIN_DIR)/cstrace_analyzer
SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(subst .cc,.o, $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC)))
#$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CXX = g++
CPPFLAGS = -MMD -Iinc/
CXXFLAGS = --std=c++17 -O3 -Wall -Wextra -Wshadow -Wpedantic -Iinc/
LDFLAGS  =
LDLIBS  =

.PHONY: all clean
all:$(EXE)
	@echo Running all 

$(EXE): $(OBJ) | $(BIN_DIR)
	@echo Building binaries 
	@echo $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo Building objects 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@echo Making directory: $@
	mkdir -p $@

clean:
	@echo Cleaning... 
	$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

#-include $(OBJ:.o=.d)

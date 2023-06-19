SRC_DIR = src
INC_DIR = inc
MOD_DIR = modules
MOD_INC_DIR = modules_inc
MOD_OBJ_DIR = obj_mod
OBJ_DIR = obj
BIN_DIR = bin

EXE = $(BIN_DIR)/cstrace_analyzer
SRC = $(wildcard $(SRC_DIR)/*.cc)
MOD = $(wildcard $(MOD_DIR)/*.cc)
OBJ = $(subst .cc,.o, $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC)))
MOD_OBJ = $(subst .cc,.o, $(subst $(MOD_DIR), $(MOD_OBJ_DIR), $(MOD)))
DEPENDS := $(OBJS:.o=.d) #$(patsubst %.cpp,%.d,$(SRC))

CC = gcc
CXX = g++
CPPFLAGS = -MMD -MP -I$(INC_DIR) -I$(MOD_INC_DIR)
CXXFLAGS = -g --std=c++17 -O3 -Wall -Wextra -Wshadow -Wpedantic -I$(INC_DIR) -I$(MOD_INC_DIR)
LDFLAGS  =
LDLIBS  =

.PHONY: all clean main
all:$(EXE)
	@echo Running all 

$(EXE): $(OBJ) $(MOD_OBJ) | $(BIN_DIR)
	@echo Building binaries 
	@echo $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo Building objects 
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

$(MOD_OBJ_DIR)/%.o: $(MOD_DIR)/%.cc | $(MOD_OBJ_DIR)
	@echo Building objects 
	$(CXX) $(CXXFLAGS) -c -MMD -MP  $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(MOD_OBJ_DIR):
	@echo Making directory: $@
	mkdir -p $@

clean:
	@echo Cleaning... 
	$(RM) -rv $(BIN_DIR) $(OBJ_DIR) $(MOD_OBJ_DIR)

-include $(DEPENDS)


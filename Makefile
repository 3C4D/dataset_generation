SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/generation
SRC_SUB := $(wildcard $(SRC_DIR)/*.c)
OBJ_SUB := $(SRC_SUB:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC := $(SRC_DIR)/*
OBJ := $(OBJ_DIR)/*.o

CC := gcc
CPPFLAGS := -Iinc -MMD -MP
CFLAGS   := -Wall -pedantic -g -O3
LDFLAGS  :=
LDLIBS   := -lm

.PHONY: all clean

################################ EXECUTABLES ###################################

all: $(EXE)

$(EXE): $(OBJ_DIR) $(BIN_DIR) $(OBJ_SUB) $(SRC)
	# $(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/fct_aux_yacc.c
	# mv fct_aux* $(OBJ_DIR)
	bison -dv $(SRC_DIR)/syntactic.y
	mv syntactic.tab.* syntactic.output $(OBJ_DIR)
	flex $(SRC_DIR)/lexical.l
	mv lex.yy.c $(OBJ_DIR)
	gcc -g -o $(OBJ_DIR)/lex.yy.o -c $(OBJ_DIR)/lex.yy.c
	gcc -g -o $(OBJ_DIR)/syntactic.tab.o -c $(OBJ_DIR)/syntactic.tab.c
	gcc $(LDFLAGS) -g $(LDLIBS) -o $(EXE) $(OBJ)

############################# AUXILIARY COMPILE ################################
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

############################# DIRECTORY CREATION ###############################
$(OBJ_DIR) $(BIN_DIR) :
	mkdir -p $@

################################## CLEANING ####################################
clean:
	@$(RM) -rv $(OBJ_DIR)

############################# COMPLETE CLEANING ################################
clean_all:
	@$(RM) -rv $(OBJ_DIR) $(BIN_DIR)

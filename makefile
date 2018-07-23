CC=gcc
RM=rm -f

SRC_DIR := src
OBJ_DIR := obj

INC_FILES := $(wildcard $(SRC_DIR)/*.h)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

BIN_FILE := calc-rpn

$_LDFLAGS := -g -Wall -lreadline
$_CFLAGS := -g -Wall

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

calc: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -g -o $(BIN_FILE) $(OBJ_FILES)

# learning is hard!
test: $(OBJ_FILES)
	@echo $@
	@echo $^
	@echo $(SRC_DIR)
	@echo $(SRC_FILES)
	@echo $(wildcard $(SRC_DIR)/*.c)
	@echo $(OBJ_DIR)
	@echo $(OBJ_FILES)
	@echo $(CFLAGS)
	@echo $(LDFLAGS)

clean: 
	$(RM) $(OBJ_FILES)

cleanall: clean
	$(RM) $(BIN_FILE)

CC := gcc
RM := rm -f
DEBUGGER := gdb

SRC_DIR := src
TEST_DIR := test
OBJ_DIR := obj

MAIN_FILE := $(SRC_DIR)/main.c

INC_FILES := $(wildcard $(SRC_DIR)/*.h)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o ,$(SRC_FILES))

# TEST_SRC_FILES := $(patsubst ".c", , $(patsubst $(MAIN_FILE), , $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(TEST_DIR)/*.c))
TEST_SRC_FILES := $(patsubst $(MAIN_FILE), , $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o ,$(TEST_SRC_FILES))

TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_FILES))
TEST_MAIN := $(concat $(TEST_DIR) "/test_main.c")

BIN_FILE := calc-rpn
TEST_BIN := run-tests

CFLAGS := -g -Wall
TEST_CFLAGS := -Wall -Wunused-function
LDFLAGS := -g -Wall -lreadline
TEST_LDFLAGS := -lcheck

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(BIN_FILE) $^

debug: $(BIN_FILE)
	$(DEBUGGER) $<

$(TEST_BIN): $(TEST_SRC_FILES) $(TEST_FILES) $(TEST_MAIN)
	$(CC) $(LDFLAGS) $(TEST_LDFLAGS) $^ -o $(TEST_BIN)

check: $(TEST_BIN)
	@echo
	./$<
	@echo

# learning is hard!
help: $(OBJ_FILES)
	@echo $(SRC_FILES)
	@echo $(OBJ_FILES)
	@echo $(TEST_SRC_FILES)
	@echo $(TEST_OBJ_FILES)
	@echo $(TEST_FILES)
	@echo $(TEST_OBJS)

clean: 
	$(RM) $(OBJ_FILES)
	$(RM) $(TEST_BIN)

cleanall: clean
	$(RM) $(BIN_FILE)

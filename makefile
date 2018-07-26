CC := gcc
RM := rm -f
DEBUGGER := gdb

SRC_DIR := src
TEST_DIR := test
OBJ_DIR := obj

INC_FILES := $(wildcard $(SRC_DIR)/*.h)
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
# TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_FILES))
TEST_MAIN := $(concat $(TEST_DIR) "/test_main.c")

BIN_FILE := calc-rpn
TEST_BIN := run_tests

CFLAGS := -g -c -Wall
LDFLAGS := -g -Wall -lreadline
TEST_LDFLAGS := -lcheck

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(BIN_FILE) $(OBJ_FILES)

debug: $(BIN_FILE)
	$(DEBUGGER) $<

$(TEST_BIN): $(TEST_FILES)
	$(CC) $(LDFLAGS) $(TEST_LDFLAGS) $(TEST_MAIN) "./test/test_main.c" -o $(TEST_BIN)

check: $(TEST_BIN)
	./$<

# learning is hard!
help: $(OBJ_FILES)
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

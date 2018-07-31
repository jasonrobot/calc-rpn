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

# All the main src files, except for main.c
TEST_SRC_FILES := $(patsubst $(MAIN_FILE), , $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(TEST_DIR)/*.c)
# this includes test_main.c
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

BIN_FILE := calc-rpn
TEST_BIN := run-tests

CFLAGS := -c -g -Wall

LDFLAGS := -g -Wall -lreadline -lm
TEST_LDFLAGS := -lcheck -lm

# build the main set of object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# build the main binary
$(BIN_FILE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(BIN_FILE) $^

# build main binary and run in gdb
debug: $(BIN_FILE)
	$(DEBUGGER) $<

# Build test binary directly from sources
$(TEST_BIN): $(TEST_SRC_FILES) $(TEST_FILES)
	$(CC) $(LDFLAGS) $(TEST_LDFLAGS) $^ -o $(TEST_BIN)

# Build and run tests
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

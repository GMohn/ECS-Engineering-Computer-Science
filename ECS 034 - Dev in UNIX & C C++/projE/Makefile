CC=gcc
CXX=g++

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
TESTBIN_DIR = ./testbin

INCLUDE         += -I $(INC_DIR)
CFLAGS          +=  -Wall
LDFLAGS         += 
TESTLDFLAGS     += -lgtest_main -lgtest -lpthread
CPPFLAGS        += -std=c++14 
TESTSTR_NAME    = teststr

TESTSTR_OBJ     = $(OBJ_DIR)/teststr.o
SS_OBJ          = $(OBJ_DIR)/SafeString.o
            
all: directories test leaktest

test: $(TESTBIN_DIR)/$(TESTSTR_NAME)
	$(TESTBIN_DIR)/$(TESTSTR_NAME)
	
leaktest: $(TESTBIN_DIR)/$(TESTSTR_NAME)
	valgrind --undef-value-errors=no --leak-check=full $(TESTBIN_DIR)/$(TESTSTR_NAME)
	
$(TESTBIN_DIR)/$(TESTSTR_NAME): $(TESTSTR_OBJ) $(SS_OBJ)
	$(CXX) $(SS_OBJ) $(TESTSTR_OBJ) -o $(TESTBIN_DIR)/$(TESTSTR_NAME) $(CFLAGS) $(CPPFLAGS) $(DEFINES) $(TESTLDFLAGS) 
	
$(TESTSTR_OBJ): $(SRC_DIR)/teststr.cpp $(INC_DIR)/SafeString.h
	$(CXX) $(SRC_DIR)/teststr.cpp -o $(TESTSTR_OBJ) -c $(CFLAGS) $(CPPFLAGS) $(DEFINES) $(INCLUDE)
	
$(SS_OBJ): $(SRC_DIR)/SafeString.c $(INC_DIR)/SafeString.h
	$(CC) $(SRC_DIR)/SafeString.c -o $(SS_OBJ) -c $(CFLAGS) $(DEFINES) $(INCLUDE)
	
.PHONY: directories
directories: $(OBJ_DIR) $(TESTBIN_DIR)
    
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(TESTBIN_DIR):
	mkdir -p $(TESTBIN_DIR)
	
clean:
	rm -rf $(TESTBIN_DIR)/
	rm -rf $(OBJ_DIR)/
	
.PHONY: clean
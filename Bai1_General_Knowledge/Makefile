.PHONY:all clean mk_objs mk_shared install

LIB_NAME := hi

#File thư mục hiện tại CUR_DIR
CUR_DIR := .
BIN_DIR :=$(CUR_DIR)/bin
INC_DIR :=$(CUR_DIR)/inc
OBJ_DIR :=$(CUR_DIR)/objs
SRC_DIR :=$(CUR_DIR)/src


LIB_DIR :=$(CUR_DIR)/libs
LIB_STATIC:=$(LIB_DIR)/static
LIB_SHARED:=$(LIB_DIR)/shared

CC := gcc

INC_FLAGS:= -I $(INC_DIR)

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c  -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello_manh.c  -o $(OBJ_DIR)/hello_manh.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello_world.c -o $(OBJ_DIR)/hello_world.o $(INC_FLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/hello_manh.o $(OBJ_DIR)/hello_world.o
install:
	cp -f $(LIB_STATIC)/lib$(LIB_NAME).a /usr/lib
all: 
	$(CC)   $(OBJ_DIR)/main.o  -L$(LIB_DIR)/static -l$(LIB_NAME) -o $(BIN_DIR)/statically-linked
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_STATIC)/lib$(LIB_NAME).a
	rm -rf $(BIN_DIR)/statically-linked
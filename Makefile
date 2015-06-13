TARGET = runner

#Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
LIB_DIR =

#Options
CC = clang++
SRC_EXT = .cpp
RM = rm -rf

#List classes here
CLASS = main\
		Node\
		Trie\
		FileScanner\

#List interfaces here
INTERFACE = \

#Auto var
SRC = $(addsuffix $(SRC_EXT), $(addprefix $(SRC_DIR)/, $(CLASS)))
OBJ = $(addsuffix .o, $(addprefix $(BUILD_DIR)/, $(CLASS)))
DEP = $(addsuffix .d, $(addprefix $(BUILD_DIR)/, $(CLASS)))
LIBS = $(addprefix -L,$(LIB_DIR))

#Flags
CFLAGS =-MMD -Wall -Wextra -Werror -O3 -std=c++98
LFLAGS =

#Libs
LIB_LOCAL = \

LIB_GLOBAL = \

LIB_OTHER = \

LIBS += $(LIB_OTHER)
LIBS += $(addprefix -L, $(LIB_LOCAL))
LIBS += $(addprefix -l, $(LIB_GLOBAL))

#Includes
INC += $(addprefix -I,$(INC_DIR))
INC += $(addsuffix /include, $(addprefix -I, $(LIB_LOCAL)))

#RULES
all : dirbin $(BIN_DIR)/$(TARGET)

clean :
	$(RM) $(BUILD_DIR)

fclean :
	$(RM) $(BUILD_DIR) $(TARGET)

re : fclean all

dirbin:
	mkdir -p $(BIN_DIR)

.PHONY: all clean fclean re

.SILENT: dirbuild dirbin

#Build rule
$(BIN_DIR)/$(TARGET) : $(OBJ)
	@echo "\n\033[1;4;34mLINK:\033[0m\n"$^"\n\033[36mLinking objects ...\033[0m\n"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#Compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(SRC_EXT)
	@mkdir -p $(dir $@)
	@echo "\n\033[1;4;34mCOMPIL:\033[0m\n"$<"\n\033[36mCompiling src ...\033[0m"
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

-include $(DEP)

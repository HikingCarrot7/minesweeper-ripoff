TARGET = $(BIN_DIR)/app
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = inc
SRC_DIR = src
SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
CPPFLAGS = -Wall -fsanitize=address -I$(INC_DIR)/

$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	g++ $(CPPFLAGS) $(OBJS) -o $(TARGET) -lncurses

$(OBJ_DIR)/%.cpp.o : %.cpp
	mkdir -p $(dir $@)
	g++ -c -DM $(CPPFLAGS) $< -o $@

-include $(DEPS)

.PHONY: clean
clean : 
	@rm -r $(OBJ_DIR)/ $(BIN_DIR)/

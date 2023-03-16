LIB_NAME	:= s21_matrix_oop.a

CXX			:= g++ -fdiagnostics-color=always
CPPFLAGS	:= -MMD -MP
CXXFLAGS	:= --std=c++17 -pedantic -O2 -Wall -Wextra -Werror

BUILD_DIR	:= build

SRC			:= src/s21_matrix_oop.cpp
OBJ			:= $(SRC:.cpp=.o)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	@ar rcs $@ $^
	@echo "Created $(LIB_NAME)"

clean:
	@rm -vf $(OBJ)
	@rm -vf $(OBJ:.o=.d)

fclean: clean
	@rm -vf $(NAME)
	@rm -vf $(LIB_NAME)
	@rm -rvf $(BUILD_DIR)

test: | $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)
	@cd build && ctest

$(BUILD_DIR):
	@cmake -S . -B build

style:
	@clang-format -n $(shell find src -type f -name "*.cpp") \
                     $(shell find src -type f -name "*.hpp")

.PHONY: all clean fclean test style

-include $(OBJ:.o=.d)

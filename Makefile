NAME		:= s21matrix+_test
LIB_NAME	:= s21_matrix_oop.a

# TODO set correct flags
CXX			:= g++ -fdiagnostics-color=always
CPPFLAGS	:= -MMD -MP
CXXFLAGS	:= --std=c++17 -pedantic -g -Wall -Wextra#-Werror

BUILD_DIR	:= build

# TODO remove main.cpp
SRC			:= src/s21_matrix_oop.cpp src/main.cpp
OBJ			:= $(SRC:.cpp=.o)

# TODO correct all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

# TODO use $(OBJ) when main.cpp is removed
$(LIB_NAME): src/s21_matrix_oop.o
	@ar rcs $@ $^

clean:
	@rm -vf $(OBJ)

fclean: clean
	@rm -vf $(NAME)
	@rm -vf $(LIB_NAME)
	@rm -vf $(OBJ:.o=.d)
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

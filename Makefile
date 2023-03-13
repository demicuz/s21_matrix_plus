NAME		:= s21matrix+_test

# TODO set correct flags
CXX			:= g++ -fdiagnostics-color=always
CPPFLAGS	:= -MMD -MP
CXXFLAGS	:= --std=c++17 -pedantic -g -Wall -Wextra#-Werror

SRC			:= src/s21_matrix_oop.cpp src/test.cpp
OBJ			:= $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

clean:
	@rm -vf $(OBJ)

fclean: clean
	@rm -vf $(NAME)
	@rm -vf $(OBJ:.o=.d)

style:
	@clang-format -n $(shell find src -type f -name "*.cpp") \
                     $(shell find src -type f -name "*.hpp")

.PHONY: clean fclean style

-include $(OBJ:.o=.d)

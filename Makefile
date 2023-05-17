NAME = ft_containers

CC = c++

FLAGS = -Wall -Wextra -Werror

STD = -std=c++98

SRC =   srcs/main_abb.cpp

OBJ = $(SRC:.cpp=.o)

HEADERS = ./srcs/vector/vector.hpp ./srcs/stack/stack.hpp ./srcs/map/map.hpp ./srcs/map/avl.hpp ./srcs/headers/enable_if.hpp ./srcs/headers/equal.hpp ./srcs/headers/is_integral.hpp ./srcs/headers/pair.hpp

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
		$(CC) $(FLAGS) $(STD) $(SRC) -o $(NAME)

$(OBJ): $(SRC) $(HEADERS)
		$(CC) $(FLAGS) $(STD) -c $(SRC) -o $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

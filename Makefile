# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 15:11:16 by fvoicu            #+#    #+#              #
#    Updated: 2023/11/02 01:04:52 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LIB := ./Lib

INCLUDES := -I ./include -I ${LIB}/libft

SRC := exec.c here_doc.c main.c path_finder.c utils.c
OBJ := $(addprefix src/, $(SRC:.c=.o))

all: $(NAME) LIB

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME)
	
LIB:
	@if [ -d ${LIB} ]; then \
		echo "Libft already exists"; \
	else \
		git clone https://github.com/dendeaisd/Lib.git ${LIB}; \
	fi
	make --directory=${LIB}

clean:
	@rm -rf $(OBJ)
	
fclean:
	make fclean --directory=${LIB}
	@rm -rf ${LIB}

all: fclean all

.PHONY: all clean fclean re
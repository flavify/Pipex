# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 15:11:16 by fvoicu            #+#    #+#              #
#    Updated: 2023/11/02 06:46:19 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LIB := ./Lib

INCLUDES := -I ./include -I ${LIB}/libft

SRC := exec.c here_doc.c main.c path_finder.c utils.c
OBJ := $(addprefix src/, $(SRC:.c=.o))

all: LIB $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): LIB $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB)/lib.a $(INCLUDES) -o $(NAME)
	
LIB:
	@if [ ! -d ${LIB} ]; then \
		git clone https://github.com/dendeaisd/Lib.git ${LIB}; \
	fi
	make --directory=Lib/

clean:
	@rm -rf $(OBJ)
	
fclean: clean
	make fclean --directory=${LIB}
	@rm -rf $(NAME)

bonus: all

re: fclean all

.PHONY: all LIB clean fclean bonus re

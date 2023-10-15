# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 10:01:49 by fvoicu            #+#    #+#              #
#    Updated: 2023/10/15 15:29:23 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libftprintf.a

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -I./include -g

HEADER		:=	$(wildcard include/*.h)
SRC 		:=	$(wildcard ./src/*.c)
OBJ_DIR 	:=	obj
OBJ_FILES	:= $(notdir $(SRC:.c=.o))
OBJ			:= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: src/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

bonus: all

re: fclean all

.PHONY: all bonus clean fclean re
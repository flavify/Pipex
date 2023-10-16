# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 10:01:49 by fvoicu            #+#    #+#              #
#    Updated: 2023/10/16 02:01:02 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libftprintf.a
SHELL		:=	bash

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -I./include -g

HEADER		:=	$(wildcard include/*.h)
SRC 		:=	$(wildcard ./src/*.c)
OBJ_DIR 	:=	obj
OBJ_FILES	:= $(notdir $(SRC:.c=.o))
OBJ			:= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

TURQUISE = \033[0;32m
RED = \033[0;31m
GREEN = \033[0;32m

RESET = \033[0m
UP := "\033[A"
CUT := "\033[K"

all: $(NAME) 

$(NAME): $(OBJ_DIR) $(OBJ)
	@./progressbar.sh
	@./spin.sh
	@ar rcs $(NAME) $(OBJ)
	@echo -e -n "\r\033[K\c"
	@echo -e "    $(GREEN)Rrready!✅$(RESET)"
	@./progressbar.sh

	
$(OBJ_DIR): 
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

bonus: all

re: fclean all



.PHONY: all bonus clean fclean re
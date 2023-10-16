# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 13:57:02 by fvoicu            #+#    #+#              #
#    Updated: 2023/10/15 17:57:17 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
FLAGS := -Wall -Wextra -Werror
RM := rm
SRC := \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c 	ft_striteri.c fv_strjoin_and_free.c	fv_strtok.c \
	get_next_line.c
BSRC := \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
PRINTF_DIR := ft_printf
PRINTF_LIB := $(PRINTF_DIR)/libftprintf.a


all:	$(NAME)
$(NAME): $(PRINTF_LIB)
	cc -c $(FLAGS) $(SRC)
	ar rcs $@ *.o
	make -C $(PRINTF_DIR) extract
	ar rs $@ $(PRINTF_DIR)/*.o
	
$(PRINTF_LIB) :
	make -C $(PRINTF_DIR)

clean:
		@$(RM) -rdf *.o
		make clean -C $(PRINTF_DIR)

fclean:	clean
		@$(RM) -f $(NAME)
		make fclean -C $(PRINTF_DIR)

bonus: $(NAME)
	cc -c $(FLAGS) $(BSRC)
	ar rcs $(NAME) *.o

re:	fclean all

.PHONY: all clean fclean re
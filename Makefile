# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 15:11:16 by fvoicu            #+#    #+#              #
#    Updated: 2023/09/21 15:32:09 by fvoicu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
LIBFT := ./libft/libft.a
INCLUDES := -I./include -I ${LIBFT}/include


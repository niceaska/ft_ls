# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 15:11:29 by lgigi             #+#    #+#              #
#    Updated: 2019/05/24 17:03:56 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = ft_ls
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ./libft/
INC = includes/
SRC_DIR = ./srcs/
FILES =  print.c mergesort.c core.c utils.c error.c print_helpers.c free.c compare.c long_tools.c main.c list_helpers.c parse.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft
	$(CC) $(CFLAGS) -c $(SRCS) -I $(INC) -I $(LIBFT_DIR)$(INC)
	$(CC) $(CFLAGS) $(OBJS) -o  $(NAME) -L libft/ -lft

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
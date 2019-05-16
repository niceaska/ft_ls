# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 15:11:29 by lgigi             #+#    #+#              #
#    Updated: 2019/05/16 16:35:26 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft
	gcc -Wall -Werror -Wextra print.c mergesort.c  compare.c test_main.c list_helpers.c parse.c libft/*.o -I libft/includes/ -L lft
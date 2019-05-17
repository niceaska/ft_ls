# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 15:11:29 by lgigi             #+#    #+#              #
#    Updated: 2019/05/17 17:49:33 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft
	gcc -Wall -Werror -Wextra print.c mergesort.c core.c utils.c  free.c compare.c test_main.c list_helpers.c parse.c libft/*.o -I libft/includes/ -L lft
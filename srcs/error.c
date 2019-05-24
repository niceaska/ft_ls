/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:56:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/22 17:57:30 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(t_lst *list, char *pathname, char **tab, t_env *e)
{
	write(2, "ls: ", 4);
	perror(pathname);
	free_all(pathname, tab, list, e);
}

void	illegal_option(t_env *e, char c)
{
	write(2, "ls: illegal option -- ", 22);
	write(2 , &c, 1);
	write(2 , "\n", 1);
	write(2, "usage: ls [-lrRaftuUgdi1nx] [file ...]\n", 39);
	if (e)
	{
		free(e->maxs);
		free(e);
	}
	exit(EXIT_FAILURE);
}

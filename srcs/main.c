/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:16:39 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/22 16:08:12 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_termwidth(t_env **e)
{
	struct winsize w;

	if (isatty(STDOUT_FILENO))
	{
		if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) == -1)
			return (-1);
		(*e)->w_width = w.ws_col;
	}
	else
	{
		(*e)->flags |= FL_ONE;
		return (0);
	}
	return (1);
}

void			init_maxs(t_maxs **maxs)
{
	(*maxs)->groups = 0;
	(*maxs)->n_links = 0;
	(*maxs)->names = 0;
	(*maxs)->size = 0;
	(*maxs)->total = 0;
	(*maxs)->users = 0;
	(*maxs)->major = 0;
	(*maxs)->minor = 0;
	(*maxs)->inode = 0;
}

t_env			*init_env(void)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (!(e->maxs = (t_maxs *)malloc(sizeof(t_maxs))))
	{
		free(e);
		return (0);
	}
	init_maxs(&(e->maxs));
	e->ag_cnt = 0;
	e->flags = 0;
	if ((get_termwidth(&e)) == -1)
	{
		print_error(NULL, ft_strdup("ioctl"), NULL, e);
		exit(EXIT_FAILURE);
	}
	e->max_wl = 0;
	e->max_ino = 0;
	e->dirs = 0;
	e->out = 0;
	return (e);
}

int				main(int ac, char **ag)
{
	t_env *e;

	if (!(e = init_env()))
		exit(EXIT_FAILURE);
	ag = ft_parser(&e, ag, ac);
	process_args(&e, ag, ac - e->ag_cnt);
	exit(EXIT_SUCCESS);
}

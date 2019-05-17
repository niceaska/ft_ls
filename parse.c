/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 17:46:23 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		parse_flags(t_env **e, char *s)
{
	while (*s)
	{
		if (*s == 'l')
			(*e)->flags |= FL_LONG;
		else if (*s == 'r')
			(*e)->flags |= FL_REV;
		else if (*s == 'R')
			(*e)->flags |= FL_REC;
		else if (*s == 'a')
			(*e)->flags |= FL_DOT;
		else if (*s =='t')
			(*e)->flags |= FL_TIME;
		s++;
	}
}

static int		get_termwidth(void)
{
	struct winsize w;
    
	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) == -1)
	{
		perror("ioctl()");
		exit(EXIT_FAILURE);
	}
	return (w.ws_col);
}

t_env			*init_env(void)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	e->ag_cnt = 0;
	e->w_width = get_termwidth();
	e->flags = 0;
	e->max_wl = 0;
	e->dirs = 0;
	e->out = 0;
	return (e);
}

char	**ft_parser(t_env **e, char **ag, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ag[i][0] == '-' && ag[i][1])
			parse_flags(e, ag[i]);
		else
			break ;
		i++;
	}
	(*e)->ag_cnt = i;
	return (ag + i);
}

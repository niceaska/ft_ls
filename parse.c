/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/18 19:27:57 by lgigi            ###   ########.fr       */
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
    
	if (isatty(STDOUT_FILENO))
	{
		if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) == -1)
		{
			perror("ioctl()");
			exit(EXIT_FAILURE);
		}
	}
	else
		return (80);
	return (w.ws_col);
}

void			init_maxs(t_maxs **maxs)
{
	(*maxs)->groups = 0;
	(*maxs)->n_links = 0;
	(*maxs)->names = 0;
	(*maxs)->size = 0;
	(*maxs)->time = 0;
	(*maxs)->total = 0;
	(*maxs)->users = 0;
	(*maxs)->major = 0;
	(*maxs)->minor = 0;
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
unsigned int	int_size(int num)
{
	unsigned int s;

	s = 0;
	while (num)
	{
		s++;
		num /= 10;
	}
	return (s);
}

void	parse_maxs(t_maxs **maxs, t_lst **arr, unsigned int size, unsigned int i)
{
	unsigned int s;

	while (i < size)
	{
		(*maxs)->total += arr[i]->stats->st_blocks;
		(*maxs)->n_links = MAX((*maxs)->n_links, int_size(arr[i]->stats->st_nlink));
		(*maxs)->names = MAX((*maxs)->names, ft_strlen(arr[i]->name));
		(*maxs)->groups = MAX((*maxs)->groups, \
							ft_strlen(getgrgid(arr[i]->stats->st_gid)->gr_name));
		(*maxs)->users = MAX((*maxs)->users, \
							ft_strlen(getpwuid(arr[i]->stats->st_uid)->pw_name));
		if (S_ISCHR(arr[i]->stats->st_mode))
		{
			(*maxs)->major = MAX((*maxs)->major, 
							int_size(major(arr[i]->stats->st_rdev)));
			(*maxs)->minor = MAX((*maxs)->minor, 
							int_size(minor(arr[i]->stats->st_rdev)));
			s = (*maxs)->major + (*maxs)->minor + 1;
		}
		else
			s = int_size(arr[i]->stats->st_size);
		(*maxs)->size = MAX((*maxs)->size, s);
		i++;
	}
	(*maxs)->time = 4;
}
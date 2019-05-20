/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/20 16:21:13 by lgigi            ###   ########.fr       */
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

static void parse_maxs_helper(t_maxs **maxs, t_lst *el)
{
	struct group	*gr;
	struct passwd	*uid;

	(*maxs)->total += el->stats->st_blocks;
	(*maxs)->n_links = MAX((*maxs)->n_links, int_size(el->stats->st_nlink));
	(*maxs)->names = MAX((*maxs)->names, ft_strlen(el->name));
	if ((gr = getgrgid(el->stats->st_gid)) == NULL)
		(*maxs)->groups = MAX((*maxs)->groups, int_size(el->stats->st_gid));
	else
		(*maxs)->groups = MAX((*maxs)->groups, ft_strlen(gr->gr_name));
	if ((uid = getpwuid(el->stats->st_uid)) == NULL)
		(*maxs)->users = MAX((*maxs)->users, int_size(el->stats->st_uid));
	else
		(*maxs)->users = MAX((*maxs)->users, ft_strlen(uid->pw_name));
}

void	parse_maxs(t_maxs **maxs, t_lst **arr, unsigned int size, unsigned int i)
{
	unsigned int s;

	while (i < size)
	{
		parse_maxs_helper(maxs, arr[i]);
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
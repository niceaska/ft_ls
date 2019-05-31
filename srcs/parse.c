/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/24 12:07:42 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		process_flags(t_env **e, char c)
{
	(*e)->flags |= (c == 'l') ? FL_LONG : 0;
	(*e)->flags |= (c == 'r') ? FL_REV : 0;
	(*e)->flags |= (c == 'R') ? FL_REC : 0;
	(*e)->flags |= (c == 'a' || c == 'f') ? FL_DOT : 0;
	(*e)->flags |= (c == 't') ? FL_TIME : 0;
	(*e)->flags |= (c == 'u') ? FL_UTIME : 0;
	(*e)->flags |= (c == 'c') ? FL_CTIME : 0;
	(*e)->flags |= (c == 'g') ? FL_GLONG : 0;
	(*e)->flags |= (c == 'd') ? FL_DIRS : 0;
	(*e)->flags |= (c == '1') ? FL_ONE : 0;
	(*e)->flags |= (c == 'U' || c == 'f') ? FL_NOSORT : 0;
	(*e)->flags |= (c == 'i') ? FL_INODE : 0;
	(*e)->flags |= (c == 'n') ? FL_NGUID : 0;
	(*e)->flags |= (c == 'x') ? FL_XPRINT : 0;
	(*e)->flags |= (c == 'G') ? FL_COLOR : 0;
	(*e)->flags |= (c == 'S') ? FL_BYSIZE : 0;
}

static void		parse_flags(t_env **e, char *s)
{
	while (*s)
	{
		if (!ft_strchr("lrRaftucUgdi1nxGS", *s))
			illegal_option(*e, *s);
		process_flags(e, *s);
		s++;
	}
}

char			**ft_parser(t_env **e, char **ag, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ag[i][0] == '-' && ag[i][1])
			parse_flags(e, ag[i] + 1);
		else
			break ;
		i++;
	}
	(*e)->ag_cnt = i;
	return (ag + i);
}

static void		parse_maxs_helper(t_maxs **maxs, t_lst *el, short flags)
{
	struct group	*gr;
	struct passwd	*uid;

	(*maxs)->total += el->stats->st_blocks;
	(*maxs)->n_links = MAX((*maxs)->n_links, int_size(el->stats->st_nlink));
	(*maxs)->names = MAX((*maxs)->names, ft_strlen(el->name));
	if (((gr = getgrgid(el->stats->st_gid)) == NULL) || (flags & FL_NGUID))
		(*maxs)->groups = MAX((*maxs)->groups, int_size(el->stats->st_gid));
	else
		(*maxs)->groups = MAX((*maxs)->groups, ft_strlen(gr->gr_name));
	if (((uid = getpwuid(el->stats->st_uid)) == NULL) || (flags & FL_NGUID))
		(*maxs)->users = MAX((*maxs)->users, int_size(el->stats->st_uid));
	else
		(*maxs)->users = MAX((*maxs)->users, ft_strlen(uid->pw_name));
}

void			parse_maxs(t_maxs **maxs, t_lst **arr,
							unsigned int size, short flags)
{
	unsigned int s;
	unsigned int i;

	i = 0;
	while (i < size)
	{
		parse_maxs_helper(maxs, arr[i], flags);
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
}

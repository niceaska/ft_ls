/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/24 21:45:37 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_byalfa(t_lst *l1, t_lst *l2, t_env *e)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = l1->name;
	name2 = l2->name;
	res = (e->flags & FL_REV) ?\
		ft_strcmp(name2, name1) : ft_strcmp(name1, name2);
	return (res);
}

static int		ft_bysize(t_lst *l1, t_lst *l2, t_env *e)
{
	if (l1->stats->st_size < l2->stats->st_size)
		return ((e->flags & FL_REV) ? -1 : 1);
	else if (l1->stats->st_size > l2->stats->st_size)
		return ((e->flags & FL_REV) ? 1 : -1);
	return (ft_byalfa(l1, l2, e));
}

static int		ft_bytime(t_lst *l1, t_lst *l2, t_env *e)
{
	if (e->flags & FL_UTIME)
	{
		if (l1->stats->st_atime < l2->stats->st_atime)
			return ((e->flags & FL_REV) ? -1 : 1);
		else if (l1->stats->st_atime > l2->stats->st_atime)
			return ((e->flags & FL_REV) ? 1 : -1);
	}
	else if (e->flags & FL_CTIME)
	{
		if (l1->stats->st_ctime < l2->stats->st_ctime)
			return ((e->flags & FL_REV) ? -1 : 1);
		else if (l1->stats->st_ctime > l2->stats->st_ctime)
			return ((e->flags & FL_REV) ? 1 : -1);
	}
	else
	{
		if (l1->stats->st_mtime < l2->stats->st_mtime)
			return ((e->flags & FL_REV) ? -1 : 1);
		else if (l1->stats->st_mtime > l2->stats->st_mtime)
			return ((e->flags & FL_REV) ? 1 : -1);
	}
	return (ft_byalfa(l1, l2, e));
}

t_cmp_func		choose_cmp(t_env *e)
{
	t_cmp_func cmp;

	if (e->flags & FL_TIME)
		cmp = ft_bytime;
	else if (e->flags & FL_BYSIZE)
		cmp = ft_bysize;
	else
		cmp = ft_byalfa;
	return (cmp);
}

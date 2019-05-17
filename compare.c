/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 21:05:03 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_byalfa(t_lst *l1, t_lst *l2)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = (l1->name[0] == '.') ? ft_strdup(l1->name + 1) : ft_strdup(l1->name);
	name2 = (l2->name[0] == '.') ? ft_strdup(l2->name + 1) : ft_strdup(l2->name);
	res = ft_strcmp(name1, name2);
	free(name1);
	free(name2);
	return (res);
}

static int		ft_revbyalfa(t_lst *l1, t_lst *l2)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = (l1->name[0] == '.') ? \
			ft_strdup(l1->name + 1) : ft_strdup(l1->name);
	name2 = (l2->name[0] == '.') ? \
			ft_strdup(l2->name + 1) : ft_strdup(l2->name);
	res = ft_strcmp(name2, name1);
	free(name1);
	free(name2);
	return (res);
}

static int		ft_bytime(t_lst *l1, t_lst *l2)
{
	if (l1->stats->st_mtime < l2->stats->st_mtime)
		return (1);
	else if (l1->stats->st_mtime > l2->stats->st_mtime)
		return (-1);
	return (0);
}

static int		ft_revbytime(t_lst *l1, t_lst *l2)
{
	if (l1->stats->st_mtime > l2->stats->st_mtime)
		return (1);
	else if (l1->stats->st_mtime < l2->stats->st_mtime)
		return (-1);
	return (0);
}

cmp_func choose_cmp(t_env *e)
{
	cmp_func cmp;

	if (e->flags & FL_TIME)
	{
		if (e->flags & FL_REV)
			cmp = ft_revbytime;
		else
			cmp = ft_bytime;
		return (cmp);
	}
	if (e->flags & FL_REV)
		cmp = ft_revbyalfa;
	else
		cmp = ft_byalfa;
	return (cmp);
}
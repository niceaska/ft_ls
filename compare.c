/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:44:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/16 17:27:59 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_byalfa(t_lst *l1, t_lst *l2)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = (l1->name[0] == '.') ? ft_strdup(l1->name + 1) : ft_strdup(l1->name);
	name2 = (l2->name[0] == '.') ? ft_strdup(l2->name + 1) : ft_strdup(l2->name);
	res = ft_strcmp(ft_strlowcase(name1), ft_strlowcase(name2));
	free(name1);
	free(name2);
	return (res);
}

int		ft_revbyalfa(t_lst *l1, t_lst *l2)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = (l1->name[0] == '.') ? \
			ft_strdup(l1->name + 1) : ft_strdup(l1->name);
	name2 = (l2->name[0] == '.') ? \
			ft_strdup(l2->name + 1) : ft_strdup(l2->name);
	res = ft_strcmp(ft_strlowcase(name2), ft_strlowcase(name1));
	free(name1);
	free(name2);
	return (res);
}

cmp_func choose_cmp(t_env *e)
{
	cmp_func cmp;

	if (e->flags & FL_REV)
		cmp = ft_revbyalfa;
	else if (!(e->flags & FL_REV) && !(e->flags & FL_TIME))
		cmp = ft_byalfa;
	return (cmp);
}
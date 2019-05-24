/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:29:05 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/20 19:03:57 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_tab(char **tab)
{
	unsigned int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			if (tab[i])
				free(tab[i++]);
		free(tab);
	}
}

void	free_list(t_lst **list)
{
	t_lst *tmp;

	while (list && *list)
	{
		tmp = *list;
		free(tmp->name);
		if (tmp->stats != NULL)
			free(tmp->stats);
		*list = (*list)->next;
		free(tmp); 
	}
}

void	free_all(char *str, char **tab, t_lst *list, t_env *e)
{
	if (str)
		free(str);
	if (tab)
		free_tab(tab);
	if (list)
		free_list(&list);
	if (e)
	{
		free(e->maxs);
		free(e);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:22:50 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 20:21:50 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	list_size(t_lst *list)
{
	unsigned int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_lst			*init_list(char *pathname, char *name)
{
	t_lst *new;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	new->name = ft_strdup(name);
	new->next = NULL;
	if (!(new->stats = (struct stat *)malloc(sizeof(struct stat))))
	{
		free(new);
		return (NULL);
	}
	if ((lstat(pathname, new->stats)) == -1)
	{
		free(new);
		perror("stat()");
		return (NULL);
	}
	new->print = 1;
	new->isdir = (new->stats->st_mode & __S_IFDIR) ? 1 : 0;
	return (new);
}

void			find_maxstrl(t_env **e, t_lst *list)
{
	while (list)
	{
		if (ft_strlen(list->name) > (*e)->max_wl)
			(*e)->max_wl = ft_strlen(list->name);
		list = list->next;
	}
	(*e)->max_wl += 1;
}

void			count_dirs(t_env **e, t_lst *list, int fl)
{
	while (list)
	{
		if (!fl)
		{
			if (list->isdir)
				(*e)->dirs++;
		}
		else
		{
			if (list->isdir && ft_strcmp(".", list->name) != 0 \
				&& ft_strcmp("..", list->name) != 0)
				(*e)->dirs += (!((*e)->flags & FL_DOT) \
								&& list->name[0] == '.') ? 0 : 1;
		}
		list = list->next;
	}
}
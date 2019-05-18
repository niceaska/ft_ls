/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:22:50 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/18 20:32:44 by lgigi            ###   ########.fr       */
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
	t_lst *n;

	if (!(n = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	n->name = ft_strdup(name);
	n->next = NULL;
	if (!(n->stats = (struct stat *)malloc(sizeof(struct stat))))
	{
		free(n);
		return (NULL);
	}
	if ((lstat(pathname, n->stats)) == -1)
	{
		free(n);
		perror("stat()");
		return (NULL);
	}
	(S_ISLNK(n->stats->st_mode)) ? ft_bzero(n->c, PATH_MAX + 1) : 0;
	(S_ISLNK(n->stats->st_mode)) ?\
					readlink(pathname, n->c, n->stats->st_size) : 0;
	get_chmod(n->chmod, pathname, n->stats->st_mode);
	n->print = 1;
	n->isdir = (S_ISDIR(n->stats->st_mode)) ? 1 : 0;
	return (n);
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
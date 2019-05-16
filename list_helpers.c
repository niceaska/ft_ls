/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:22:50 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/16 21:28:55 by lgigi            ###   ########.fr       */
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
		//exit(EXIT_FAILURE);
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
	(*e)->max_wl += 4;
}

void			count_dirs(t_env **e, t_lst *list)
{
	while (list)
	{
		if (list->isdir)
			(*e)->dirs++;
		list = list->next;
	}
}
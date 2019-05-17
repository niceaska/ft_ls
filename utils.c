/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:41:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 20:16:12 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**get_dirs(t_lst *list, t_env *e, unsigned int	i, int fl)
{
	char			**dirs;

	if (!(dirs = (char **)malloc(sizeof(char *) * (e->dirs + 1))))
	{
		perror("malloc");
		free_all(NULL, NULL, list, e);
		exit(EXIT_FAILURE);
	}
	while (i < e->dirs)
	{
		while (list && ((!list->isdir && !fl) || (fl && (!list->isdir || \
			(!ft_strcmp(".", list->name) || !ft_strcmp("..", list->name) \
			|| (!(e->flags & FL_DOT) && list->name[0] == '.'))))))
			list = list->next;
		if (!(dirs[i] = ft_strdup(list->name)))
		{
			free_all(NULL, dirs, list, e);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		list = (list) ? list->next : list;
		i++;
	}
	dirs[i] = NULL;
	return (dirs);
}

char	*get_path(char *path, char *new_dir)
{
	char	*swap;
	char	*new_path;

	new_path = ft_strnew(ft_strlen(path) + 1);
	new_path = ft_strcpy(new_path, path);
	if (*path)
		new_path[ft_strlen(path)] = '/';
	swap = new_path;
	new_path = ft_strjoin(new_path, new_dir);
	free(swap);
	return (new_path);
}

void	split(t_lst *src, t_lst **left, t_lst **right)
{
	t_lst *fst;
	t_lst *nxt;

    if (!src || !src->next)
    {
        *left = src;
        *right = NULL;
		return ;
    }
	fst = src;
	nxt = src->next;
	while (nxt)
	{
		nxt = nxt->next;
		if (nxt)
		{
			fst = fst->next;
			nxt = nxt->next;
		}
    }
    *left = src;
	*right = fst->next;
	fst->next = NULL;
}
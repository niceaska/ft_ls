/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:42:41 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/18 17:15:58 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lst 	*fill_args(char **ag, int ac, int i, t_lst *res)
{
	if (ac <= 0 || !ag || !*ag) 
		return (NULL);
	if (!(res  = init_list(*ag, *ag)))
	{
		if (*(ag + 1) && --ac)
			res = fill_args(++ag, ac, i, res);
		else
			return (NULL);
	}
	if (res->isdir)
		res->print = 0;
	res->next = fill_args(ag + 1, ac - 1, i + 1, res->next);
	return (res);
}



static t_lst 	*fill_list(struct dirent *d, DIR *dir, t_lst *res, char *path)
{
	char *pathname;

	if (d == NULL) 
		return (NULL);
	pathname = get_path(path, d->d_name);
	if (!(res  = init_list(pathname, d->d_name)))
	{
		if ((d = readdir(dir)) != NULL)
			res = fill_list(d, dir, res, path);
		else
			return (NULL);
	}
	d = readdir(dir);
	free(pathname);
	res->next = fill_list(d, dir, res->next, path);
	return (res);
}

static void	process_dirs(t_env *e, char **dirs,char *path, int i)
{
	char	**recdir;
	char	*pathname;
	t_lst	*list;
	DIR 	*dir;

	while (dirs[++i])
	{
		pathname = get_path(path, dirs[i]);
		(e->out) ? ft_printf("\n%s:\n", pathname) : 0;
		dir = opendir(pathname);
		list = fill_list(readdir(dir), dir, list, pathname);
		merge_sort(&list, choose_cmp(e));
		printer(list, e, 0);
		closedir(dir);
		if (e->flags & FL_REC)
		{
			e->dirs = 0;
			count_dirs(&e, list, 1);
			recdir = get_dirs(list, e, 0, 1);
			process_dirs(e, recdir, pathname, -1);
			free_tab(recdir);
		}
		free_all(pathname, NULL, list, NULL);
	}
}

void	process_args(t_env **e, char **ag, int ac)
{
	t_lst	*list;
	char	*path;
	char	**dirs;

	list = NULL;
	if (ac <= 0)
	{
		list = init_list(".", ".");
		list->print = 0;
	}
	else
		list = fill_args(ag, ac, 0, list);
	merge_sort(&list, choose_cmp(*e));
	count_dirs(e, list, 0);
	simple_print(list, *e);
	dirs = get_dirs(list, *e, 0, 0);
	path = ft_strnew(1);
	process_dirs(*e, dirs, path, -1);
	free_all(path, dirs, list, *e);
}
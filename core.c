/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:42:41 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/23 14:47:01 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lst 	*fill_args(char **ag, int ac, short flags, t_lst *res)
{
	struct stat		st;
	char			*path;

	if (ac <= 0 || !ag || !*ag) 
		return (NULL);
	if (!(res = init_list(*ag, *ag)))
	{
		if (*(ag + 1) && --ac)
			return (fill_args(++ag, ac, flags, res));
		else
			return (NULL);
	}
	if (res && S_ISLNK(res->stats->st_mode) && !(flags & FL_DIRS)\
	&& !((flags & FL_LONG) || (flags & FL_NGUID) || (flags & FL_GLONG)))
	{
		path = (res->c[0] == '.' && res->c[1] == '.' && res->c[2] == '/') ? \
								get_path(res->name, res->c) : ft_strdup(res->c);
		stat(path, &st);
		res->isdir = (S_ISDIR(st.st_mode)) ? 1 : 0;
		free(path);
	}
	if (res->isdir && res)
		res->print = (flags & FL_DIRS) ? 1 : 0;
	res->next = fill_args(ag + 1, ac - 1, flags, res->next);
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

static t_lst *proceass_list(t_env *e, DIR *dir, char *pathname)
{
	t_lst *list;

	list = 0;
	(e->out) ? ft_printf("\n%s:\n", pathname) : 0;
	list = fill_list(readdir(dir), dir, list, pathname);
	(e->flags & FL_NOSORT) ? 0 : merge_sort(&list, choose_cmp(e), e);
	printer(list, e, 0, 1);
	return (list);	
}

static void	process_dirs(t_env *e, char **dirs, char *path, long i)
{
	char	**recdir;
	char	*pathname;
	t_lst	*list;
	DIR 	*dir;

	while (dirs[++i])
	{
		pathname = get_path(path, dirs[i]);
		if (!(dir = opendir(pathname)))
		{
			print_error(NULL, pathname, NULL, NULL);
			continue ;
		}
		list = proceass_list(e, dir, pathname);
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
		list->print = ((*e)->flags & FL_DIRS) ? 1 : 0;
	}
	else
		list = fill_args(ag, ac, (*e)->flags, list);
	((*e)->flags & FL_NOSORT) ? 0 : merge_sort(&list, choose_cmp(*e), *e);
	printer(list, *e, 0, 0);
	((*e)->flags & FL_DIRS) ? 0 : count_dirs(e, list, 0);
	dirs = ((*e)->flags & FL_DIRS) ? 0 : get_dirs(list, *e, 0, 0);
	path = ((*e)->flags & FL_DIRS) ? 0 : ft_strnew(1);
	((*e)->flags & FL_DIRS) ? 0 : process_dirs(*e, dirs, path, -1);
	free_all(path, dirs, list, *e);
}

/*
void	push(t_lst **list, char *pathname, char *name)
{
	t_lst *new;

	new = init_list(pathname, name);
	if (!list && !*list)
	{
		*list = new;
		return ;
	}
	else
	{
		new->next = *list;
		*list = new;
	}
	
}
static t_lst 	*fill_list(DIR *dir, char *path)
{
	char			*pathname;
	t_lst			*list;
	struct dirent	*d;

	list = NULL;
	while ((d = readdir(dir)) != NULL)
	{
		pathname = get_path(path, d->d_name);
		push(&list, pathname, d->d_name);
		free(pathname);
	}
	return (list);
}
*/
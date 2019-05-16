/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/16 21:35:45 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		parse_flags(t_env **e, char *s)
{
	while (*s)
	{
		if (*s == 'l')
			(*e)->flags |= FL_LONG;
		else if (*s == 'r')
			(*e)->flags |= FL_REV;
		else if (*s == 'R')
			(*e)->flags |= FL_REC;
		else if (*s == 'a')
			(*e)->flags |= FL_DOT;
		else if (*s =='t')
			(*e)->flags |= FL_TIME;
		s++;
	}
}

static int		get_termwidth(void)
{
	struct winsize w;
    
	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) == -1)
	{
		perror("ioctl()");
		exit(EXIT_FAILURE);
	}
	return (w.ws_col);
}

t_env			*init_env(void)
{
	t_env *e;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	e->ag_cnt = 0;
	e->w_width = get_termwidth();
	e->flags = 0;
	e->max_wl = 0;
	e->dirs = 0;
	return (e);
}

char	**ft_parser(t_env **e, char **ag, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ag[i][0] == '-' && ag[i][1])
			parse_flags(e, ag[i]);
		else
			break ;
		i++;
	}
	(*e)->ag_cnt = i;
	return (ag + i);
}

t_lst 	*fill_args(char **ag, int ac, int i, t_lst *res)
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

t_lst 	*fill_list(struct dirent *d, DIR *dir, t_lst *res, char *path)
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
	res->next = fill_list(d, dir, res->next, path);
	return (res);
}

char	**get_dirs(t_lst *list, t_env *e, unsigned int	i)
{
	char			**dirs;

	if (!(dirs = (char **)malloc(sizeof(char *) * e->dirs)))
	{
		perror("malloc");
		//free everything
		exit(EXIT_FAILURE);
	}
	while (i < e->dirs)
	{
		while (list && !list->isdir)
			list = list->next;
		if (!(dirs[i] = ft_strdup(list->name)))
		{
			//free everything
			perror("malloc");
			//exit(EXIT_FAILURE);
		}
		if (list)
			list = list->next;
		i++;
	}
	dirs[i] = NULL;
	return (dirs);
}


void	process_dirs(t_env *e, char **dirs, char *path)
{
	unsigned int	i;
	char			*pathname;
	t_lst			*list;
	DIR 			*dir;

	i = 0;
	while (dirs[i])
	{
		dir = opendir(dirs[i]);
		pathname = get_path(path, dirs[i]);
		list = fill_list(readdir(dir), dir, list, pathname);
		merge_sort(&list, ft_byalfa);
		simple_print(list, e);
		closedir(dir);
		free(pathname);
		i++;
	}
}

t_lst	*process_args(t_env **e, char **ag, int ac)
{
	t_lst	*list;
	char	**dirs;

	list = NULL;
	if (ac <= 0)
		list = init_list(".", ".");
	else
		list = fill_args(ag, ac, 0, list);
	merge_sort(&list, ft_revbyalfa);
	count_dirs(e, list);
	simple_print(list, *e);
	dirs = get_dirs(list, *e, 0);
	process_dirs(*e, dirs, ft_strnew(1));
	return (list);
}


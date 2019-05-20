/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:27:14 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/20 16:09:19 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_cols(t_lst **arr, t_env *e,
							unsigned int size, unsigned int i)
{
	unsigned int	cols;
	unsigned int 	rows;
	unsigned int	base;
	unsigned int	j;
	
	cols = e->w_width / e->max_wl;
	cols = (cols == 0) ? 1 : cols;
	rows = size / cols;
	if (size % cols)
		++rows;
	while (i < rows)
	{
		base = i;
		j = 0;
		while (j < cols)
		{
			ft_printf("%-*s", e->max_wl, arr[base]->name);
			if ((base += rows) >= size)
				break ;
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static void		print_time(t_lst *el)
{
	time_t	now;
	char	*s;

	time(&now);
	s = ctime(&(el->stats->st_mtime)) + 4;
	if ((el->stats->st_mtime + HALF_YEAR < now) \
		|| (el->stats->st_mtime > now + HALF_YEAR))
	{
		ft_printf(" %.6s ", s);
		s += 15;
		ft_printf("%.5s ", s);
		return ;
	}
	ft_printf(" %.12s ", s);
}

static void		long_helper(t_lst *el, t_maxs *maxs)
{
	struct group	*gr;
	struct passwd	*uid;

	ft_printf("%s %*hu", el->chmod, maxs->n_links, el->stats->st_nlink);
	if ((uid = getpwuid(el->stats->st_uid)) == NULL)
		ft_printf(" %-*ld", maxs->users, el->stats->st_uid);
	else
		ft_printf(" %-*s", maxs->users, uid->pw_name);
	if ((gr = getgrgid(el->stats->st_gid)) == NULL)
		ft_printf(" %-*ld", maxs->users, el->stats->st_gid);
	else
		ft_printf("  %-*s", maxs->groups, gr->gr_name);
	if (S_ISBLK(el->stats->st_mode) || S_ISCHR(el->stats->st_mode))
		ft_printf("%*d,%*d", maxs->major + 1, major(el->stats->st_rdev), 
						maxs->minor + 1, minor(el->stats->st_rdev));
	else
		ft_printf("  %*lld", maxs->size, el->stats->st_size);
	print_time(el);
	ft_printf("%s", el->name);
	if (S_ISLNK(el->stats->st_mode))
		ft_printf(" -> %s", el->c);
}

static void		print_long(t_lst **arr, t_maxs *maxs,
							unsigned int size, unsigned int i)
{
	ft_printf("total: %ld\n", maxs->total);
	while (i < size)
	{
		long_helper(arr[i], maxs);
		ft_printf("\n");
		i++;
	}
}

void	printer(t_lst *list, t_env *e, unsigned int i, int fl_dir)
{
	t_lst			**arr;

	e->max_wl = 1;
	find_maxstrl(&e, list);
	if (!(arr = (t_lst **)malloc(sizeof(t_lst *) * (list_size(list) + 1))))
		return ;
	while (list)
	{
		if (((e->flags & FL_DOT)\
			|| list->name[0] != '.') && fl_dir)
			arr[i++] = list;
		else if (list->print && !fl_dir)
			arr[i++] = list;
		list = list->next;
	}
	(e->flags & FL_LONG) ? init_maxs(&(e->maxs)) : 0;
	(e->flags & FL_LONG) ? parse_maxs(&(e->maxs), arr, i, 0) : 0;
	((e->flags & FL_LONG) && i > 0) ? print_long(arr, e->maxs, i, 0) : print_cols(arr, e, i, 0);
	if (i)
		e->out++;
	free(arr);
}

void	print_error(t_lst *list, char *pathname, char **tab, t_env *e)
{
	write(2, "ls: ", 4);
	perror(pathname);
	free_all(pathname, tab, list, e);
}
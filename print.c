/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:27:14 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/18 21:20:02 by lgigi            ###   ########.fr       */
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

static void		print_long(t_lst **arr, t_maxs *maxs,
							unsigned int size, unsigned int i)
{
	ft_printf("total: %ld\n", maxs->total);
	while (i < size)
	{
		ft_printf("%s", arr[i]->chmod);
		ft_printf(" %*hu", maxs->n_links, arr[i]->stats->st_nlink);
		ft_printf(" %-*s", maxs->users, getpwuid(arr[i]->stats->st_uid)->pw_name);
		ft_printf("  %-*s", maxs->groups, getgrgid(arr[i]->stats->st_gid)->gr_name);
		if (S_ISBLK(arr[i]->stats->st_mode) || S_ISCHR(arr[i]->stats->st_mode))
		{
			ft_printf("%*d,", maxs->major + 1, major(arr[i]->stats->st_rdev));
			ft_printf("%*d", maxs->minor + 1, minor(arr[i]->stats->st_rdev));
		}
		else
			ft_printf("  %*lld", maxs->size, arr[i]->stats->st_size);
		print_time(arr[i]);
		ft_printf("%s", arr[i]->name);
		if (S_ISLNK(arr[i]->stats->st_mode))
			ft_printf(" -> %s", arr[i]->c);
		ft_printf("\n");
		i++;
	}
}

void	simple_print(t_lst *list, t_env *e)
{
	t_lst			**arr;
	unsigned int	i;

	i = 0;
	find_maxstrl(&e, list);
	if (!(arr = (t_lst **)malloc(sizeof(t_lst *) * (list_size(list) + 1))))
		return ;
	while (list)
	{
		if (list->print)
			arr[i++] = list;
		list = list->next;
	}
	if (i)
		print_cols(arr, e, i, 0);
	if (i)
		e->out++;
	free(arr);
}

void	printer(t_lst *list, t_env *e, unsigned int i)
{
	t_lst			**arr;

	e->max_wl = 1;
	find_maxstrl(&e, list);
	if (!(arr = (t_lst **)malloc(sizeof(t_lst *) * (list_size(list) + 1))))
		return ;
	while (list)
	{
		if ((e->flags & FL_DOT) || list->name[0] != '.')
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
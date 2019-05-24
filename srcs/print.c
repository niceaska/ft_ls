/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:27:14 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/23 16:30:11 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_scol(t_lst **arr, t_env *e, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		print_name(arr[i], e);
		ft_printf("\n");
		i++;
	}
}

static void		print_cols(t_lst **arr, t_env *e,
							unsigned int size, long i)
{
	unsigned int	cols;
	unsigned int 	rows;
	unsigned int	base;
	long			j;

	if (!size)
		return ;
	if (e->flags & FL_ONE)
		return (print_scol(arr, e, size));
	get_rcols(e, &rows, size, &cols);
	while (++i < rows)
	{
		base = ((e->flags & FL_XPRINT) && i > 0) ? base : i;
		j = -1;
		while (++j < cols)
		{
			print_name(arr[base], e);
			if ((base += (e->flags & FL_XPRINT) ? 1 : rows) >= size)
				break ;
		}
		ft_printf("\n");
	}
}

static void		print_long(t_lst **arr, t_env *e, unsigned int size)
{
	unsigned int i;

	i = 0;
	(!e->out && !e->dirs) ? 0 : ft_printf("total %ld\n", e->maxs->total);
	while (i < size)
	{
		long_helper(arr[i], e->maxs, e);
		ft_printf("\n");
		i++;
	}
}

void	printer(t_lst *list, t_env *e, unsigned int i, int fl_dir)
{
	t_lst			**arr;

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
	if ((e->flags & FL_LONG) || (e->flags & FL_NGUID) || (e->flags & FL_GLONG))
	{
		init_maxs(&(e->maxs));
		e->maxs->inode = e->max_ino;
		parse_maxs(&(e->maxs), arr, i, e->flags);
		print_long(arr, e, i);
	}
	else
		print_cols(arr, e, i, -1);
	e->out += (i) ? 1 : 0;
	free(arr);
}

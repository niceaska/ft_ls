/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:27:14 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 18:04:56 by lgigi            ###   ########.fr       */
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
	rows = size / cols;
	if (size % cols)
		++rows;
	while (i < rows)
	{
		base = i;
		j = 0;
		while (j < cols)
		{
			ft_printf("%-*s", (e->w_width / cols), arr[base]->name);
			if ((base += rows) >= size)
				break ;
			j++;
		}
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
	if (!(arr = (t_lst **)malloc(sizeof(t_lst *) * list_size(list))))
		return ;
	while (list)
	{
		if (list->print)
			arr[i++] = list;
		list = list->next;
	}
	print_cols(arr, e, i, 0);
	if (i)
		e->out++;
	free(arr);
}

void	printer(t_lst *list, t_env *e, unsigned int i)
{
	t_lst			**arr;

	e->max_wl = 0;
	find_maxstrl(&e, list);
	if (!(arr = (t_lst **)malloc(sizeof(t_lst *) * list_size(list))))
		return ;
	while (list)
	{
		if ((e->flags & FL_DOT) || list->name[0] != '.')
			arr[i++] = list;
		list = list->next;
	}
	print_cols(arr, e, i, 0);
	e->out++;
	free(arr);
}
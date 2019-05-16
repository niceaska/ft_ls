/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:27:14 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/16 14:15:56 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	simple_print(t_lst *list, t_env *e)
{
	find_maxstrl(&e, list);
	while (list)
	{
		if (list->print)
			ft_printf("%-*s", e->max_wl, list->name);
		list = list->next;
	}
}
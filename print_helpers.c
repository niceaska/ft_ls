/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:58:06 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/22 18:00:27 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_name(t_lst *el, t_env *e)
{
	if (e->flags & FL_INODE)
		ft_printf("%*ju ", e->max_ino, (uintmax_t)el->stats->st_ino);
	if ((e->flags & FL_ONE) || (e->flags & FL_MPRINT))
		ft_printf("%s", el->name);
	else
		ft_printf("%-*s", e->max_wl, el->name);
}

void		get_rcols(t_env *e, unsigned int *rows,
							unsigned int size, unsigned int *cols)
{
	if (e->flags & FL_INODE)
		*cols = e->w_width / (e->max_wl + e->max_ino + 1);
	else
		*cols = e->w_width / e->max_wl;
	*cols = (*cols == 0) ? 1 : *cols;
	*rows = size / *cols;
	*rows += (size % *cols) ? 1 : 0;
}

static void		print_time(t_lst *el, short flags)
{
	time_t	now;
	time_t	el_time;
	char	*s;

	time(&now);
	el_time = (flags & FL_UTIME) ? \
			el->stats->st_atime : el->stats->st_mtime;
	s = ctime(&el_time) + 4;
	if ((el_time + HALF_YEAR < now) \
		|| (el_time > now + HALF_YEAR))
	{
		ft_printf(" %.6s ", s);
		s += 15;
		ft_printf("%.5s ", s);
		return ;
	}
	ft_printf(" %.12s ", s);
}

void		long_helper(t_lst *el, t_maxs *maxs, short flags)
{
	struct group	*gr;
	struct passwd	*uid;

	(flags & FL_INODE) ? ft_printf("%*ju ", maxs->inode, (uintmax_t)el->stats->st_ino) : 0;
	ft_printf("%s %*hu", el->chmod, maxs->n_links, el->stats->st_nlink);
	if (((uid = getpwuid(el->stats->st_uid)) == NULL) || (flags & FL_NGUID))
		(flags & FL_GLONG) ? 0 : ft_printf(" %-*ld", maxs->users, el->stats->st_uid);
	else
		(flags & FL_GLONG) ? 0 : ft_printf(" %-*s", maxs->users, uid->pw_name);
	if (((gr = getgrgid(el->stats->st_gid)) == NULL) || (flags & FL_NGUID))
		ft_printf(" %-*ld", maxs->users, el->stats->st_gid);
	else
		ft_printf("  %-*s", maxs->groups, gr->gr_name);
	if (S_ISBLK(el->stats->st_mode) || S_ISCHR(el->stats->st_mode))
		ft_printf("%*d,%*d", maxs->major + 1, major(el->stats->st_rdev), 
						maxs->minor + 1, minor(el->stats->st_rdev));
	else
		ft_printf("  %*lld", maxs->size, el->stats->st_size);
	print_time(el, flags);
	ft_printf("%s", el->name);
	if (S_ISLNK(el->stats->st_mode))
		ft_printf(" -> %s", el->c);
}

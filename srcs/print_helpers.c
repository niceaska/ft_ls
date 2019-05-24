/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:58:06 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/24 12:38:22 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*choose_color(mode_t mode, char *chmod, char *link_buf)
{
	if (S_ISDIR(mode) && chmod[9] != 't')
		return (DIR_COL);
	else if (S_ISDIR(mode) && chmod[9] == 't')
		return (STICKY_COL);
	else if (S_ISCHR(mode) || S_ISBLK(mode))
		return (BLKCHR_COL);
	else if	(S_ISLNK(mode) && *link_buf)
		return (LINK_COL);
	else if (S_ISLNK(mode) && !*link_buf)
		return (ORPAN_COL);
	else if (S_ISSOCK(mode))
		return (SOCK_COL);
	else if (S_ISFIFO(mode))
		return (FIFO_COL);
	else if ((mode & S_IXUSR) && chmod[3] == 's' \
			&& (mode & S_IXGRP)  && (mode & S_IXOTH))
		return (SETUID_COL);
	else if ((mode & S_IXUSR) && chmod[6] == 's' \
			&& (mode & S_IXGRP)  && (mode & S_IXOTH))
		return (SETGID_COL);
	else if ((mode & S_IXUSR) \
			&& (mode & S_IXGRP)  && (mode & S_IXOTH))
		return (EXEC_COL);
	return (FILE_COL);
}

void		print_name(t_lst *el, t_env *e)
{
	long ret;

	if ((e->flags & FL_INODE) && !((e->flags & FL_LONG) || \
		(e->flags & FL_NGUID) || (e->flags & FL_GLONG)))
		ft_printf("%*ju ", e->max_ino, (uintmax_t)el->stats->st_ino);
	if (e-> flags & FL_COLOR)
		ft_putstr(choose_color(el->stats->st_mode, el->chmod, el->c));
	ret = write(1, el->name, ft_strlen(el->name));
	if (e->flags & FL_COLOR)
		ft_putstr(COL);
	if (!(e->flags & FL_ONE) && !((e->flags & FL_LONG) || \
		(e->flags & FL_NGUID) || (e->flags & FL_GLONG)))
		while (ret < e->max_wl)
			ret += write(1, " ", 1);
}

static void		print_str(char *str, long max, short fl)
{
	long ret;

	if (fl)
		write(1, " ", 1);
	else
		write(1, "  ", 2);
	ret = write(1, str, ft_strlen(str));
	while (ret < max)
		ret += write(1, " ", 1);
}

static void		print_time(t_lst *el, short flags)
{
	time_t	now;
	time_t	el_time;
	char	*s;

	time(&now);
	if (flags & FL_UTIME)
		el_time = el->stats->st_atime;
	else if (flags & FL_CTIME)
		el_time = el->stats->st_ctime;
	else
		el_time = el->stats->st_mtime;
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

void		long_helper(t_lst *el, t_maxs *maxs, t_env *e)
{
	struct group	*gr;
	struct passwd	*uid;

	(e->flags & FL_INODE) ? ft_printf("%*ju ", maxs->inode, (uintmax_t)el->stats->st_ino) : 0;
	ft_printf("%s %*hu", el->chmod, maxs->n_links, el->stats->st_nlink);
	if (((uid = getpwuid(el->stats->st_uid)) == NULL) || (e->flags & FL_NGUID))
		(e->flags & FL_GLONG) ? 0 : ft_printf(" %-*ld", maxs->users, el->stats->st_uid);
	else
		(e->flags & FL_GLONG) ? 0 : print_str(uid->pw_name, (long)maxs->users, 1);
	if (((gr = getgrgid(el->stats->st_gid)) == NULL) || (e->flags & FL_NGUID))
		ft_printf("  %-*ld", maxs->groups, el->stats->st_gid);
	else
		print_str(gr->gr_name, (long)maxs->groups, 0);
	if (S_ISBLK(el->stats->st_mode) || S_ISCHR(el->stats->st_mode))
		ft_printf("%*d,%*d", maxs->major + 1, major(el->stats->st_rdev), 
						maxs->minor + 1, minor(el->stats->st_rdev));
	else
		ft_printf("  %*lld", maxs->size, el->stats->st_size);
	print_time(el, e->flags);
	print_name(el, e);
	if (S_ISLNK(el->stats->st_mode))
		ft_printf(" -> %s", el->c);
}

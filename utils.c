/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:41:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/18 19:28:20 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**get_dirs(t_lst *list, t_env *e, unsigned int	i, int fl)
{
	char			**dirs;

	if (!(dirs = (char **)malloc(sizeof(char *) * (e->dirs + 1))))
	{
		perror("malloc");
		free_all(NULL, NULL, list, e);
		exit(EXIT_FAILURE);
	}
	while (i < e->dirs)
	{
		while (list && ((!list->isdir && !fl) || (fl && (!list->isdir || \
			(!ft_strcmp(".", list->name) || !ft_strcmp("..", list->name) \
			|| (!(e->flags & FL_DOT) && list->name[0] == '.'))))))
			list = list->next;
		if (!(dirs[i] = ft_strdup(list->name)))
		{
			free_all(NULL, dirs, list, e);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		list = (list) ? list->next : list;
		i++;
	}
	dirs[i] = NULL;
	return (dirs);
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

void	split(t_lst *src, t_lst **left, t_lst **right)
{
	t_lst *fst;
	t_lst *nxt;

    if (!src || !src->next)
    {
        *left = src;
        *right = NULL;
		return ;
    }
	fst = src;
	nxt = src->next;
	while (nxt)
	{
		nxt = nxt->next;
		if (nxt)
		{
			fst = fst->next;
			nxt = nxt->next;
		}
    }
    *left = src;
	*right = fst->next;
	fst->next = NULL;
}
char	ft_ftype(int mode)
{
	char	c;

	if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISREG(mode))
		c = '-';
	else if	(S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else if (S_ISFIFO(mode))
		c = 'p';
	else
		c = '?';
	return (c);
}

/*
char	get_acl(char *pathname)
{
	acl_t acl;
    acl_entry_t dummy;
    ssize_t xattr;
    char ch;

	xattr = 0;
	acl = acl_get_link_np(pathname, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_TYPE_DEFAULT, &dummy) == -1)
	{
        acl_free(acl);
        acl = NULL;
    }
  	if ((xattr = listxattr(pathname, NULL, 0, XATTR_NOFOLLOW)) > 0)
		ch = '@';
	else
    	ch = (acl != NULL) ? '+' : ' ';
	return (ch);
}
*/
void	get_chmod(char chmod[12], char *pathname, int mode)
{
	chmod[0] = ft_ftype(mode);
	chmod[1] = CHMOD_UREAD(mode);
	chmod[2] = CHMOD_UWRITE(mode);
	chmod[3] = CHMOD_UEXEC(mode);
	chmod[4] = CHMOD_GREAD(mode);
	chmod[5] = CHMOD_GWRITE(mode);
	chmod[6] = CHMOD_GEXEC(mode);
	chmod[7] = CHMOD_OREAD(mode);
	chmod[8] = CHMOD_OWRITE(mode);
	chmod[9] = CHMOD_OEXEC(mode);
	//chmod[10] = get_acl(pathname);
	chmod[11] = '\0';
	if (mode & S_ISUID)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:11:09 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/23 13:24:49 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else if (S_ISFIFO(mode))
		c = 'p';
	else
		c = '?';
	return (c);
}

char	get_acl(char *pathname)
{
	acl_t			acl;
	acl_entry_t		dummy;
	ssize_t			xattr;
	char			ch;

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

void	get_chmod(char chmod[12], char *pathname, mode_t mode)
{
	int i;

	i = 0;
	chmod[i++] = ft_ftype(mode);
	chmod[i++] = CHMOD_UREAD(mode);
	chmod[i++] = CHMOD_UWRITE(mode);
	if ((chmod[i] = CHMOD_UEXEC(mode)) == '-')
		chmod[i++] = (mode & S_ISUID) ? 'S' : '-';
	else
		chmod[i++] = (mode & S_ISUID) ? 's' : 'x';
	chmod[i++] = CHMOD_GREAD(mode);
	chmod[i++] = CHMOD_GWRITE(mode);
	if ((chmod[i] = CHMOD_GEXEC(mode)) == '-')
		chmod[i++] = (mode & S_ISGID) ? 'S' : '-';
	else
		chmod[i++] = (mode & S_ISGID) ? 's' : 'x';
	chmod[i++] = CHMOD_OREAD(mode);
	chmod[i++] = CHMOD_OWRITE(mode);
	if ((chmod[i] = CHMOD_OEXEC(mode)) == '-')
		chmod[i++] = (mode & S_ISVTX) ? 'T' : '-';
	else
		chmod[i++] = (mode & S_ISVTX) ? 't' : 'x';
	chmod[i++] = get_acl(pathname);
	chmod[i] = '\0';
}

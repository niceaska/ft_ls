/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:11:09 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/22 18:09:16 by lgigi            ###   ########.fr       */
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
	int i;

	i = 0;
	ft_strlen(pathname);
	chmod[i++] = ft_ftype(mode);
	chmod[i++] = CHMOD_UREAD(mode);
	chmod[i++] = CHMOD_UWRITE(mode);
	chmod[i++] = CHMOD_UEXEC(mode);
	chmod[i++] = CHMOD_GREAD(mode);
	chmod[i++] = CHMOD_GWRITE(mode);
	chmod[i++] = CHMOD_GEXEC(mode);
	chmod[i++] = CHMOD_OREAD(mode);
	chmod[i++] = CHMOD_OWRITE(mode);
	chmod[i++] = CHMOD_OEXEC(mode);
	//chmod[i++] = get_acl(pathname);
	chmod[i] = '\0';
	if (mode & S_ISUID)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:16:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/23 13:32:51 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/sysmacros.h> 
# include <grp.h>
# include <pwd.h>
# include <errno.h>
# include <time.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <limits.h>
# include <linux/limits.h>

# define FILE_COL "\033[00m"
# define LINK_COL "\033[01;36m"
# define DIR_COL "\033[01;34m"
# define FIFO_COL "\033[01;33m"
# define SOCK_COL "\033[01;35m"
# define EXEC_COL "\033[01;32m"
# define BLKCHR_COL "\033[01;33;01m"
# define COL "\033[0m"

# define CHMOD_UREAD(m)((m) & S_IRUSR) ? 'r' : '-'
# define CHMOD_UWRITE(m)((m) & S_IWUSR) ? 'w' : '-'
# define CHMOD_UEXEC(m)((m) & S_IXUSR) ? 'x' : '-'
# define CHMOD_GREAD(m)((m) & S_IRGRP) ? 'r' : '-'
# define CHMOD_GWRITE(m)((m) & S_IWGRP) ? 'w' : '-'
# define CHMOD_GEXEC(m)((m) & S_IXGRP) ? 'x' : '-'
# define CHMOD_OWRITE(m)((m) & S_IWOTH) ? 'w' : '-'
# define CHMOD_OREAD(m)((m) & S_IROTH) ? 'r' : '-'
# define CHMOD_OEXEC(m)((m) & S_IXOTH) ? 'x' : '-'

# define FL_LONG (1 << 0)
# define FL_REV (1 << 1)
# define FL_REC (1 << 2)
# define FL_DOT (1 << 3)
# define FL_TIME (1 << 4)
# define FL_UTIME (1 << 5)
# define FL_GLONG (1 << 6)
# define FL_DIRS (1 << 7)
# define FL_ONE (1 << 8)
# define FL_NOSORT (1 << 9)
# define FL_INODE (1 << 10)
# define FL_NGUID (1 << 11)
# define FL_XPRINT (1 << 12)
# define FL_COLOR (1 << 13)

# define HALF_YEAR 15778463

typedef struct		s_maxs
{
	long			total;
	unsigned int	n_links;
	unsigned int	names;
	unsigned int	users;
	unsigned int	groups;
	unsigned int	size;
	unsigned int	major;
	unsigned int	minor;
	unsigned int	inode;
}					t_maxs;

typedef struct		s_env
{

	int				w_width;
	short			flags;
	unsigned int	max_wl;
	unsigned int	max_ino;
	unsigned int	ag_cnt;
	unsigned int	dirs;
	unsigned int	out;
	struct s_maxs	*maxs;
}					t_env;

typedef struct		s_lst
{
	char			*name;
	char			c[PATH_MAX + 1];
	char			chmod[12];
	short			isdir;
	short			print;
	struct stat		*stats;
	struct s_lst	*next;
}					t_lst;

typedef int (*t_cmp_func)(t_lst *, t_lst *);

unsigned int		list_size(t_lst *list);
t_lst				*init_list(char *pathname, char *name);
char				**ft_parser(t_env **e, char **ag, int ac);
void				parse_maxs(t_maxs **maxs, t_lst **arr,
								unsigned int size, short flags);

t_env				*init_env(void);
void				init_maxs(t_maxs **maxs);
void				reset_env(t_env **e);

void				process_args(t_env **e, char **ag, int ac);
void				find_maxstrl(t_env **e, t_lst *list);
void				count_dirs(t_env **e, t_lst *list, int fl);
char				*get_path(char *path, char *new_dir);
char				**get_dirs(t_lst *list, t_env *e, unsigned int	i, int fl);
unsigned int		int_size(long num);
void				get_chmod(char chmod[12], char *pathname, mode_t mode);
void				get_rcols(t_env *e, unsigned int *rows,
										unsigned int size, unsigned int *cols);
void				printer(t_lst *list, t_env *e, unsigned int i, int fl_dir);
void				print_name(t_lst *el, t_env *e);
void				long_helper(t_lst *el, t_maxs *maxs, short flags);

void				print_error(t_lst *list, char *pathname, char **tab, t_env *e);
void				illegal_option(t_env *e, char c);

void				merge_sort(t_lst **list, t_cmp_func cmp);
void				split(t_lst *src, t_lst **left, t_lst **right);
t_cmp_func 			choose_cmp(t_env *e);

void				free_tab(char **tab);
void				free_list(t_lst **list);
void				free_all(char *str, char **tab, t_lst *list, t_env *e);


#endif
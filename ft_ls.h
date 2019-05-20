/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:16:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/20 16:22:04 by lgigi            ###   ########.fr       */
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

# define HALF_YEAR 15778463

typedef struct		s_maxs
{
	long			total;
	unsigned int	n_links;
	unsigned int	names;
	unsigned int	users;
	unsigned int	groups;
	unsigned int	time;
	unsigned int	size;
	unsigned int	major;
	unsigned int	minor;
}					t_maxs;

typedef struct		s_env
{

	int				w_width;
	short			flags;
	unsigned int	max_wl;
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

typedef int (*cmp_func)(t_lst *, t_lst *);

unsigned int		list_size(t_lst *list);
t_lst				*init_list(char *pathname, char *name);
char				**ft_parser(t_env **e, char **ag, int ac);
void				parse_maxs(t_maxs **maxs, t_lst **arr,
								unsigned int size, unsigned int i);

t_env				*init_env(void);
void				init_maxs(t_maxs **maxs);

void				process_args(t_env **e, char **ag, int ac);
void				find_maxstrl(t_env **e, t_lst *list);
void				count_dirs(t_env **e, t_lst *list, int fl);
char				*get_path(char *path, char *new_dir);
char				**get_dirs(t_lst *list, t_env *e, unsigned int	i, int fl);
unsigned int		int_size(int num);
void				get_chmod(char chmod[12], char *pathname, int mode);

void				printer(t_lst *list, t_env *e, unsigned int i, int fl_dir);
void				print_error(t_lst *list, char *pathname, char **tab, t_env *e);

void				merge_sort(t_lst **list, cmp_func cmp);
void				split(t_lst *src, t_lst **left, t_lst **right);
cmp_func 			choose_cmp(t_env *e);

void				free_tab(char **tab);
void				free_list(t_lst **list);
void				free_all(char *str, char **tab, t_lst *list, t_env *e);


#endif
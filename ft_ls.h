/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:16:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/17 21:06:30 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>
# include <stdio.h>

# define FL_LONG (1 << 0)
# define FL_REV (1 << 1)
# define FL_REC (1 << 2)
# define FL_DOT (1 << 3)
# define FL_TIME (1 << 4)


typedef struct		s_env
{

	int				w_width;
	short			flags;
	unsigned int	max_wl;
	unsigned int	ag_cnt;
	unsigned int	dirs;
	unsigned int	out;
}					t_env;

typedef struct		s_lst
{
	char			*name;
	short			isdir;
	short			print;
	struct stat		*stats;
	struct s_lst	*next;
}					t_lst;

typedef int (*cmp_func)(t_lst *, t_lst *);

unsigned int		list_size(t_lst *list);
t_lst				*init_list(char *pathname, char *name);
char				**ft_parser(t_env **e, char **ag, int ac);
t_env				*init_env(void);
void				process_args(t_env **e, char **ag, int ac);
void				find_maxstrl(t_env **e, t_lst *list);
void				count_dirs(t_env **e, t_lst *list, int fl);
char				*get_path(char *path, char *new_dir);
char				**get_dirs(t_lst *list, t_env *e, unsigned int	i, int fl);

void				simple_print(t_lst *list, t_env *e);
void				printer(t_lst *list, t_env *e, unsigned int i);

void				merge_sort(t_lst **list, cmp_func cmp);
void				split(t_lst *src, t_lst **left, t_lst **right);
cmp_func 			choose_cmp(t_env *e);

void				free_tab(char **tab);
void				free_list(t_lst **list);
void				free_all(char *str, char **tab, t_lst *list, t_env *e);


#endif
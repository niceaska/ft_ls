/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:16:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/05/16 17:53:35 by lgigi            ###   ########.fr       */
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
t_lst				*process_args(t_env **e, char **ag, int ac);
void				simple_print(t_lst *list, t_env *e);
void				find_maxstrl(t_env **e, t_lst *list);
void				count_dirs(t_env **e, t_lst *list);

void				merge_sort(t_lst **list, cmp_func cmp);
int					ft_byalfa(t_lst *l1, t_lst *l2);
int					ft_revbyalfa(t_lst *l1, t_lst *l2);


#endif
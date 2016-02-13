/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 17:03:22 by avacher           #+#    #+#             */
/*   Updated: 2016/02/13 17:03:22 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>

typedef struct		s_arg
{
	int				recu;
	int				a;
	int				g;
	int				l;
	int				o;
	int				p;
	int				r;
	int				t;
	int				colors;
	int				arg_nb;
	int				own_len;
	int				gr_len;
	int				lk_len;
	int				maj_len;
	int				min_len;
	int				size_len;
	blkcnt_t		tot_blocks;
}					t_arg;

typedef struct		s_flist
{
	char			*name;
	char			*path;
	char			type;
	char			*date;
	char			*year;
	int				epoc;
	char			*owner;
	char			*group;
	char			rights[13];
	char			*size;
	char			*major;
	char			*minor;
	char			*link_nb;
	char			*link;
	int				fsize_len;
	blkcnt_t		block;
	struct s_flist	*next;
}					t_flist;

int					ft_error(int error, char *cur_pb);
int					free_s_flist(t_flist **lst);

char				*format_path(char *b_path, char *filename, int namelen);
int					get_time(t_flist **lst, struct stat buff_stat);
int					get_name(t_arg *option, t_flist **lst, int ac_c, char **av);

int					get_options(t_arg *option, int *ac_c, char **av);
int					init_options(t_arg *option);
int					getpwgr(struct passwd **pwd, struct group **grp,
						struct stat bs);
t_flist				*lst_new(char *name, char *fpath, t_arg **option);
int					lst_time_insert(t_arg *option, t_flist **lst, t_flist *new);
int					lst_insert(t_arg *option, t_flist **lst, t_flist *new);

int					recu_dir(t_arg *opt, char *dpath, char *name);

int					file_rights(t_flist **lst, struct stat buff_stat);
char				file_type(struct stat buff_stat);

int					file_info(char *path, char *name, t_arg *option,
								t_flist **lst);
int					display_total(t_arg **option);
int					display_colors(t_flist **lst);
int					long_display(t_flist **lst, t_arg *option);

int					first_display(t_flist **lst, t_arg *options);
int					display_dirname(t_arg *option, char *str);
int					put_space(char *str, int len);
int					ls_display(t_arg *opt, t_flist **lst);

#endif

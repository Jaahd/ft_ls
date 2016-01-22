/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 14:16:52 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
/*
	tmp = *lst;
	while(tmp)
	{
		printf("lst2 : name : %s,\npath :%s,\ntype : %d,\ndate : %s,\nowner : %s,\ngroup : %s,\nrights : %s,\n", tmp->name, tmp->path, tmp->type, tmp->date, tmp->owner, tmp->group, tmp->rights);
		tmp = tmp->next;	
	}

 NE PAS OUBLIER DE GERER LA "NON - TAILLE" POUR LES FICHIERS b OU c!!!!!!!!!!!!
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

typedef struct		s_arg
{
	int				recu;
	int				a;
	int				l;
	int				r;
	int				t;
	int				arg_nb;
	int				own_len;
	int				gr_len;
	int				lk_len;
	int				size_len;
}					t_arg;	

typedef struct		s_flist
{
	char			*name;
	char			*path;
	char			type;
	char			*date;
	char			*owner;
	char			*group;
	char			rights[13];
	char			*size; // -> cf si besoin de le changer en int //
	int				fsize_len;
	char			*link_nb;
	char			*link;
	struct s_flist	*next;	
}					t_flist;

int					ft_error(int error, char *cur_pb);
int					free_options(t_arg *option);

// getinfo
//int					get_mtime(t_arg *argmt);
char				*format_path(char *b_path, char *filename, int namelen);
int					lst_insert(t_arg *option, t_flist **lst, t_flist *new);
t_flist				*lst_new(char *name, char *fpath, t_arg *option);
int					get_name(t_arg *option, t_flist **lst, int ac_c, char **av);
int					get_options(t_arg *option, int *ac_c, char **av);

// permissions
int					file_size(t_flist *lst, t_arg *option, struct stat b_stat);
int					file_rights(t_flist *lst, struct stat buff_stat);
char				file_type(struct stat buff_stat);
int					option_l(struct stat buff_stat, char *cheat[],
								t_flist *lst, t_arg *option);
int					file_info(char *path, t_arg *option, t_flist *lst);

// display
int					first_display(t_flist **lst, t_arg *options);
int					long_display(t_flist *lst, t_arg *option);
int					ls_display(t_arg *opt, t_flist *lst);

// managedir 
int					fill_dirlist(DIR *p_dir, t_flist **lst, t_arg *argmt);
int					lst_pushback(t_flist **lst, char *dname);
int					open_dir(t_arg *opt, char *dpath, char *dname);

#endif

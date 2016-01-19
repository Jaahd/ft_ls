/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/19 20:01:38 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
/*
 NE PAS OUBLIER DE GERER LA "NON - TAILLE" POUR LES FICHIERS b OU c!!!!!!!!!!!!
 */
#include <stdio.h>
#include <dirent.h>

typedef struct		s_arg
{
	int				recu;
	int				a;
	int				l;
	int				r;
	int				t;
}					t_arg;	

typedef struct		s_flist
{
	char			*name;
	char			*path;
	char			type;
	char			*date;
	char			*owner;
	char			*group;
	char			*rights;
	char			*size; // -> cf si besoin de le changer en int //
	char			*link_nb;
	char			*link;
	int				arg_nb;
	struct s_flist	*prev;
	struct s_flist	*next;	
}					t_flist;

int					ft_error(int error, char *cur_pb);

// getinfo
//int					get_mtime(t_arg *argmt);
char				*format_path(char *b_path, char *filename, int namelen);
int					bubble_sort(t_arg *opt, t_flist *lst);
int					get_options(t_arg *opt, int *ac_c, char **av);
int					get_name(t_flist *lst, int ac, int *ac_c, char **av);

// permissions
int					isadir(char *path);

// display
int					first_display(t_flist *lst);
int					ls_display(struct dirent *p_dirent, t_arg *argmt);

// managedir 
int					fill_dirlist(DIR *p_dir, t_flist **dir_lst, t_arg *argmt);
int					dirlst_pushb(t_flist **dirlist, char *dname);
int					open_dir(t_arg argmt, char *dpath, char *dname);

#endif

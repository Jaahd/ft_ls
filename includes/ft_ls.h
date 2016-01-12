/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/12 21:01:05 by avacher          ###   ########.fr       */
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
	char			**n_arg;
	char			**fpath;
	int				arg_nb;
	int				rec;
	int				a;
	int				l;
	int				r;
	int				t;
}					t_arg;	

typedef struct		s_dlist
{
	char			*dname;
	struct s_dlist	*next;	
}					t_dlist;

int					ft_error(int error, char *cur_pb);

// getinfo
char				*format_path(char *b_path, char *filename, int namelen);
int					bubble_sort(t_arg *argmt);
int					get_options(t_arg *argmt, int *ac_c, char **av);
int					get_name(t_arg *argmt, int ac, int *ac_c, char **av);

// permissions
int					isadir(char *path);

// display
int					first_display(t_arg argmt);

// managelist ----> a renommer "managedir" 
int					fill_dirlist(DIR *pDir, t_dlist **dir_lst);
int					dirlst_pushb(t_dlist **dirlist, char *dname);
int					open_dir(t_arg argmt, char *dpath, char *dname);

#endif

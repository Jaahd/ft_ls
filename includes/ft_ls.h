/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 18:56:45 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
/*
 NE PAS OUBLIER DE GERER LA "NON - TAILLE" POUR LES FICHIERS b OU c!!!!!!!!!!!!
 */
#include <stdio.h>
typedef struct		s_arg
{
	char			**n_arg;
	char			**fpath;
	int				arg_nb;
	int				R;
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

void				ft_error(int error, char *cur_pb);
int					get_options(t_arg *argmt, int *ac_c, char **av);
int					get_name(t_arg *argmt, int ac, int *ac_c, char **av);
int					bubble_sort(t_arg *argmt);
int					isadir(char *path);

#endif

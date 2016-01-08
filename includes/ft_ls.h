/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/08 13:24:06 by avacher          ###   ########.fr       */
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

void				ft_error(int error, char *cur_pb);
int					get_options(t_arg *argmt, int *ac_c, char **av);
int					get_name(t_arg *argmt, int ac, int *ac_c, char **av);

#endif

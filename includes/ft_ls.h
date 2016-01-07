/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:16:44 by avacher           #+#    #+#             */
/*   Updated: 2016/01/07 17:40:12 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
/*
 NE PAS OUBLIER DE GERER LA "NON - TAILLE" POUR LES FICHIERS b OU c!!!!!!!!!!!!
 */

typedef struct		s_arg
{
	char			**arg_name;
	char			**format_path;
	int				arg_nb;
	char			*options;	
}					t_arg;	

#endif

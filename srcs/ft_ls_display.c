/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/13 20:11:34 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		first_display(t_arg argmt)
{
	int			i;

	i = -1;
	while (++i < argmt.arg_nb)
	{
		if (!(isadir(argmt.fpath[i])))	
			ft_putendl(argmt.n_arg[i]);/* fonction d'affichage */
	}
	i = -1;
	while (++i < argmt.arg_nb)
	{
		if (isadir(argmt.fpath[i]) && ft_strcmp(argmt.n_arg[i], ".") 
				&& ft_strcmp(argmt.n_arg[i], ".."))
		{
			ft_putchar('\n');
			ft_putstr(argmt.n_arg[i]);
			ft_putendl(":");
			open_dir(argmt, argmt.fpath[i], argmt.n_arg[i]);
		}
	}
	return (0);
}
/*
int		long_display()
*/
int		ls_display(struct dirent *p_dirent, t_arg *argmt)
{

	if (ft_strcmp(p_dirent->d_name, ".") && ft_strcmp(p_dirent->d_name, "..")
			&& argmt)
	{
		if (argmt->l == 1)
		{
			printf("l is good\n");
//			long_display(p_dirent->d_name);
		}
		else
			ft_putendl(p_dirent->d_name);
	}
	//	printf("\ndirent : %s\nargmt : %s\npath : %s\n", p_dirent->d_name, name, path);
	return (0);
}

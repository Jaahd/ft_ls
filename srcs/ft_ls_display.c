/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/12 21:09:08 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ft_putendl(argmt.n_arg[i]);
			open_dir(argmt, argmt.fpath[i], argmt.n_arg[i]);
		}
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/20 13:35:02 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		first_display(t_flist **lst, t_arg option)
{
	printf("fct : first_display\n");
	t_flist		*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (!(isadir(tmp->path)))	
		{
			printf("nom des fichiers :\n");
			ft_putendl(tmp->name);/* fonction d'affichage */
		}
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp != NULL)
	{
		printf("nom des dossiers :\n");
		if (isadir(tmp->path) && ft_strcmp(tmp->name, ".") 
				&& ft_strcmp(tmp->name, ".."))
		{
			ft_putendl(tmp->name);/* fonction d'affichage */
			ft_putchar('\n');
			ft_putstr(tmp->name);
			ft_putendl(":");
			ft_putendl("nom du dossier");
			open_dir(option, tmp->path, tmp->name);
		}
		tmp = tmp->next;
	}
	return (0);
}
/*
int		long_display()
*/
int		ls_display(struct dirent *p_dirent, t_arg *option, t_flist **lst)
{
//	printf("fct : ls_display\n");

	if (ft_strcmp(p_dirent->d_name, ".") && ft_strcmp(p_dirent->d_name, "..")
			&& *lst)
	{
		if (option->l == 1)
		{
			printf("l is good\n");
//			long_display(p_dirent->d_name);
		}
		else
			ft_putendl(p_dirent->d_name);
	}
	//	printf("\ndirent : %s\n*lst : %s\npath : %s\n", p_dirent->d_name, name, path);
	return (0);
}

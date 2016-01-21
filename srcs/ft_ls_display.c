/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/21 16:12:00 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		first_display(t_flist **lst, t_arg *option)
{
//	printf("fct : first_display\n");
	t_flist		*tmp;
	int			is_dir;

	tmp = *lst;
	while (tmp != NULL)
	{
//		printf("nom du chose : %s\n", tmp->name);
		is_dir = file_info(tmp->path, option, tmp);
		if (tmp->type != 'd')	
			printf("noms des fichiers");/* fonction d'affichage */
		tmp = tmp->next;
	}
		tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".") 
				&& ft_strcmp(tmp->name, ".."))
		{
			if(option->arg_nb >  1)
			{
				ft_putstr(tmp->name); /* fonction d'affichage */
				ft_putendl(":");
			}
			if ((open_dir(option, tmp->path, tmp->name)))
				printf("nom des fichiers du dossier\n");
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
		//	long_display(p_dirent->d_name);
		}
		else
			ft_putendl(p_dirent->d_name);
	}
	//	printf("\ndirent : %s\n*lst : %s\npath : %s\n", p_dirent->d_name, name, path);
	return (0);
}

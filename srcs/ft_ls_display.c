/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/21 19:04:40 by avacher          ###   ########.fr       */
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
		is_dir = file_info(tmp->path, option, tmp);
		if (tmp->type != 'd')	
			ft_putendl(tmp->name);/* fonction d'affichage */
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->type == 'd' /* && ft_strcmp(tmp->name, ".")*/ 
				&& ft_strcmp(tmp->name, ".."))
		{

			if(option->arg_nb >  1)
			{
				ft_putchar('\n');
				ft_putstr(tmp->name); /* fonction d'affichage */
				ft_putendl(":");
			}
			open_dir(option, tmp->path, tmp->name);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		long_display(t_flist *lst/*, t_arg *option*/)
{
	ft_putstr(lst->rights);
	//	display_link_nb(lst, option);
	ft_putchar(' ');
	ft_putstr(lst->owner);
	ft_putstr("  ");
	ft_putstr(lst->group);
	ft_putstr("  ");
	ft_putstr(lst->size);
	ft_putchar(' ');
	ft_putstr(lst->date);
	ft_putchar(' ');
	return (0);
}

int		ls_display(struct dirent *p_dirent, t_arg *option, t_flist **lst)
{
	//	printf("fct : ls_display\n");
	t_flist		*tmp;
	int			is_dir;

	tmp = *lst;
	if (ft_strcmp(p_dirent->d_name, ".") && ft_strcmp(p_dirent->d_name, "..")
			&& tmp)
	{
		is_dir = file_info(tmp->path, option, tmp);
		if (option->l == 1)
		{
			long_display(tmp);
		}
		ft_putendl(p_dirent->d_name);
		if (option->l == 1 && (*lst)->type == 'l')
		{
			ft_putstr(" -> ");
			ft_putstr((*lst)->link);
		}
	}
	//	printf("\ndirent : %s\ntmp : %s\npath : %s\n", p_dirent->d_name, name, path);
	return (0);
}

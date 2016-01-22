/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 14:31:48 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
	if(tmp->next != NULL)
	{
		t2 = (option->t ? tmp->next->date : tmp->next->name);
		while (i = (option->r ? ft_strcmp(t2, new1) : ft_strcmp(new1, t2)) > 0))
		tmp = tmp->next;
	}
	*/
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		first_display(t_flist **lst, t_arg *option)
{
	//	printf("fct : first_display\n");
	t_flist		*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		file_info(tmp->path, option, tmp);
		if (tmp->type != 'd')	
			ls_display(option, tmp);/* fonction d'affichage */
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

int		put_space(char *str, int len)
{
//		printf("fct : put_space\n");
	int			i;

	i = ft_strlen(str);
	while(i < len)
	{
		ft_putchar(' ');
		i++;
	}
	return (0);
}

int		long_display(t_flist *lst, t_arg *option)
{
//		printf("fct : long_display\nlst->owner : %s\toption->l : %d\n");
	ft_putstr(lst->rights);
	ft_putstr(lst->link_nb);
	put_space(lst->link_nb, (option->lk_len + 1));
	ft_putstr(lst->owner);
	put_space(lst->owner, (option->own_len + 2));
	ft_putstr(lst->group);
	put_space(lst->group, (option->gr_len + 2));
	put_space(lst->size, option->size_len);
	ft_putstr(lst->size);
	ft_putchar(' ');
	ft_putstr(lst->date);
	ft_putchar(' ');
	return (0);
}

int		ls_display(t_arg *option, t_flist *lst)
{
//		printf("fct : ls_display\n");
	t_flist		*tmp;

	tmp = lst;
/*	while(tmp)
	{
		printf("lst2 : name : %s,\npath :%s,\ntype : %d,\ndate : %s,\nowner : %s,\ngroup : %s,\nrights : %s,\nsize :%s\n\n", tmp->name, tmp->path, tmp->type, tmp->date, tmp->owner, tmp->group, tmp->rights, tmp->size);
		tmp = tmp->next;	
	}
	tmp = *lst;
*/	printf("nom du fichier : %s\n", tmp->name);
	if (ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0)
	{
//		is_dir = file_info(tmp->path, option, tmp);
		if (option->l == 1)
		{
			long_display(tmp, option);
		}
		ft_putendl(tmp->name);
		if (option->l == 1 && lst->type == 'l')
		{
			ft_putstr(" -> ");
			ft_putstr(lst->link);
		}
	}
//		printf("\ndirent : %s\ntmp : %s\npath : %s\n", p_dirent->d_name, tmp->name, tmp->path);
	return (0);
}

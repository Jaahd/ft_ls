/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 13:06:42 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		first_display(t_flist **lst, t_arg *option)
{
		printf("fct : first_display\n");
	t_flist		*tmp;
	int			is_dir;

	tmp = *lst;
	printf("toto fait dodo\n");
	while (tmp != NULL)
	{
		is_dir = file_info(tmp->path, option, tmp);
		if (tmp->type != 'd')	
			ft_putendl(tmp->name);/* fonction d'affichage */
		tmp = tmp->next;
	}
	printf("j'aime le chocolat\n");
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
	printf("turlututu chapeau pointu\n");
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
//	printf("i : %d\tlen :%d\n", i, len);
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

int		ls_display(struct dirent *p_dirent, t_arg *option, t_flist **lst)
{
//		printf("fct : ls_display\n");
	t_flist		*tmp;
	int			is_dir;

	tmp = *lst;
	while(tmp)
	{
		printf("lst2 : name : %s,\npath :%s,\ntype : %d,\ndate : %s,\nowner : %s,\ngroup : %s,\nrights : %s,\n", tmp->name, tmp->path, tmp->type, tmp->date, tmp->owner, tmp->group, tmp->rights);
		tmp = tmp->next;	
	}
	tmp = *lst;
	if (ft_strcmp(p_dirent->d_name, ".") && ft_strcmp(p_dirent->d_name, "..")
			&& tmp)
	{
		is_dir = file_info(tmp->path, option, tmp);
		if (option->l == 1)
		{
			printf("pouet\n");
//			long_display(tmp, option);
		}
		ft_putendl(p_dirent->d_name);
		if (option->l == 1 && (*lst)->type == 'l')
		{
			ft_putstr(" -> ");
			ft_putstr((*lst)->link);
		}
	}
//		printf("\ndirent : %s\ntmp : %s\npath : %s\n", p_dirent->d_name, tmp->name, tmp->path);
	return (0);
}

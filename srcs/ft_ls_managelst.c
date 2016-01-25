/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managelst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:25:02 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:25:14 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

t_flist		*lst_new(char *name, char *fpath, t_arg *option)
{
//	printf("fct : lst_new\n");
	t_flist			*new;
	
	if ((new = (t_flist *)malloc(sizeof(t_flist))) == NULL)
		ft_error (1, "list creation"); // nom a reprendre
	if ((new->name = ft_strdup(name)) == NULL)
		ft_error(1, name);
	new->path = fpath;
	new->type = 0;
	new->date = NULL;
	new->owner = NULL;
	new->group = NULL;
	new->size = NULL;
	new->link_nb = NULL;
	new->link = NULL;
	new->next = NULL;
	new->fsize_len = 0;
	new->block = 0;
	file_info(new->path, option, new);
	return (new);
}

int		lst_2nd_insert(char *new1, t_arg *option, t_flist *tmp, t_flist *new)
{
	char			*tmp1;
	int				cmp;

	tmp1 = (option->t ? tmp->next->date : tmp->next->name);
	while (tmp->next != NULL && (cmp = (option->r ? ft_strcmp(tmp1, new1)
					: ft_strcmp(new1, tmp1))) > 0)
	{
		tmp = tmp->next;
		if (tmp->next)
			tmp1 = (option->t ? tmp->next->date : tmp->next->name);
	}
	new->next = tmp->next;
	tmp->next = new;
	return (0);
}

int		lst_insert(t_arg *option, t_flist **lst, t_flist *new)
{
//	printf("fct : lst_insert\n");	
	t_flist			*tmp;
	char			*tmp1;
	char			*new1;
	int				cmp;

	tmp = *lst;
	tmp1 = (option->t ? tmp->date : tmp->name);
	new1 = (option->t ? new->date : new->name);
	cmp = (option->r ? ft_strcmp(tmp1, new1) : ft_strcmp(new1, tmp1));
	if (cmp < 0)
	{
		new->next = tmp;
		*lst = new;
		return (0);
	}
	else if (tmp->next == NULL)
	{
		tmp->next = new;
		return (0);
	}
	lst_2nd_insert(new1, option, tmp, new);
	return (0);
}

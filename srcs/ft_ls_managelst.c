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
	new->fsize_len = 0;
	new->link_nb = NULL;
	new->link = NULL;
	new->next = NULL;
	file_info(new->path, option, new);
	return (new);
}

int		lst_insert(t_arg *option, t_flist **lst, t_flist *new)
{
//	printf("fct : lst_insert\n");	
	t_flist			*tmp;
	char			*tmp1;
	char			*tmp2;
	char			*new1;
	int				cmp;
	int				cmp1;
	int				cmp2;

	/*tmp = *lst;
	while(tmp)
	{
		printf("ds tmp, name = %s\n", tmp->name);
		tmp = tmp->next;
	}*/
	ft_putchar('\n');
	cmp1 = 0;
	cmp2 = 0;
	tmp = *lst;
	tmp1 = (option->t ? tmp->date : tmp->name);
	new1 = (option->t ? new->date : new->name);
	cmp = (option->r ? ft_strcmp(tmp1, new1) : ft_strcmp(new1, tmp1));
		//printf("->%d xxx %s xxx %s<-\n", cmp, new->name, tmp->name);
	if (cmp < 0)
	{
//		printf("->%s|\t|%s<-\n", new->name, tmp->name);
		new->next = tmp;
		*lst = new;
		return (0);
	}
	else if (tmp->next == NULL)
	{
		tmp->next = new;
		return (0);
	}
	tmp2 = (option->t ? tmp->next->date : tmp->next->name);
	while (tmp->next != NULL && (cmp = (option->r ? ft_strcmp(tmp2, new1)
					: ft_strcmp(new1, tmp2))) > 0)
	{
		tmp2 = (option->t ? tmp->next->date : tmp->next->name);
		printf("cmp = %d\n", cmp);
		tmp = tmp->next;
	}
	new->next = tmp->next;
	tmp->next = new;
	return (0);
}

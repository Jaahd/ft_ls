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

t_flist		*lst_new(char *name, char *fpath, t_arg **option)
{
//	printf("fct : lst_new\n");
	t_flist			*new;

	if ((new = (t_flist *)malloc(sizeof(t_flist))) == NULL)
		ft_error (1, "list creation"); // nom a reprendre
/*	if (ft_strcmp(name, ""))
	{
		if ((new->name = ft_strdup(fpath)) == NULL)
			ft_error(1, name);
	}
	else
*/		if ((new->name = ft_strdup(name)) == NULL)
			ft_error(1, name);
	new->path = ft_strdup(fpath);
	new->type = 0;
	new->date = NULL;
	new->year = NULL;
	new->epoc = 0;
	new->owner = NULL;
	new->group = NULL;
	new->size = NULL;
	new->link_nb = NULL;
	new->link = NULL;
	new->next = NULL;
	new->fsize_len = 0;
	new->block = 0;
	file_info(new->path, *option, &new);
//printf("\nlongeur des lien : %d\n", (*option)->lk_len);
	return (new);
}

int		lst_2nd_t_insert(t_arg *option, t_flist **lst, t_flist *new)
{
//	printf("fct : lst_2_t_insert\n");
	int				cmp;
	t_flist			*tmp;

	tmp = *lst;
	while (tmp->next != NULL && (cmp = (option->r ?
					intcmp(tmp->next->epoc, new->epoc) :
					intcmp(new->epoc, tmp->next->epoc))) <= 0)
	{
		if (cmp == 0)
		{
			while (tmp->next && (option->r ?
						ft_strcmp(tmp->next->name, new->name) :
						ft_strcmp(new->name, tmp->next->name)) > 0
						&& intcmp(tmp->next->epoc, new->epoc) == 0)
				tmp = tmp->next;
			new->next = tmp->next;
			tmp->next = new;		
			return (0);
		}
		tmp = tmp->next;
	}
	new->next = tmp->next;
	tmp->next = new;
	return (0);
}

int		lst_time_insert(t_arg *option, t_flist **lst, t_flist *new)
{
//	printf("fct : lst_time_insert\n");
	t_flist			*tmp;
	int				cmp;

	tmp = *lst;
	cmp = (option->r ? intcmp(tmp->epoc, new->epoc) :
			intcmp(new->epoc, tmp->epoc));
	//printf("%s\tnew : %d\t tmp : %d\t cmp : %d\n", new->name, new->epoc, tmp->epoc, cmp);
	if (cmp > 0 || (cmp == 0 && (option->r ? ft_strcmp(tmp->name, new->name) :
										ft_strcmp(new->name, tmp->name)) < 0))
	{
//		printf("if : cmp>0\n");
		new->next = tmp;	
		*lst = new;
		return (0);
	}
	else if (tmp->next == NULL)
	{
//		printf("if cmp<0 et tmp->next == NULL\n");
		tmp->next = new;
		return (0);
	}
	lst_2nd_t_insert(option, lst, new);
	tmp = *lst;
	printf("*NEW* [%s]\t", new->name);
	while (tmp)
	{
		printf("[%s]->", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
	return (0);
}

int		lst_insert(t_arg *option, t_flist **lst, t_flist *new)
{
//	printf("fct : lst_insert\n");	
	t_flist			*tmp;
	int				cmp;

	tmp = *lst;
	if ((cmp = (option->r ? ft_strcmp(tmp->name, new->name) :
					ft_strcmp(new->name, tmp->name))) < 0)
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
	while (tmp->next != NULL && (cmp = (option->r ?
					ft_strcmp(tmp->next->name, new->name) :
					ft_strcmp(new->name, tmp->next->name))) > 0)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
	return (0);
}

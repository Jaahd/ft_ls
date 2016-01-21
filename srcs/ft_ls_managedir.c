/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managedir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:40:26 by avacher           #+#    #+#             */
/*   Updated: 2016/01/21 19:04:47 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

int		lst2_pushback(t_flist **list, char *name)
{
//	printf("fct : lst2_pushback\n");
	t_flist		*tmp;
	t_flist		*new;

	tmp = *list;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if ((new = (t_flist *)malloc(sizeof(t_flist))) == NULL)
		ft_error(1, name);
	new->next = NULL;
	if ((new->name = ft_strdup(name)) == NULL)
		ft_error(1, name);
	if (tmp)
		tmp->next = new;
	else
		*list = new;
	return (0);
}

int		fill_list(DIR *p_dir, t_flist **lst2, t_arg *option, char *dpath)
{
//	printf("fct : fill_list\n");
	struct dirent		*p_dirent;
	t_flist				*new;

	while ((p_dirent = readdir(p_dir)) != NULL) 
	{
		if (ft_strcmp(p_dirent->d_name, ".") != 0 && ft_strcmp(p_dirent->d_name, "..") != 0)
		{
			new = lst_new(p_dirent->d_name, format_path(dpath,
						p_dirent->d_name, ft_strlen(p_dirent->d_name)));
			if (*lst2 == NULL)
				*lst2 = new;
			else
				lst_insert(option, lst2, new);
		}
		if (p_dirent->d_name[0] != '.')
			ls_display(p_dirent, option, lst2);	
	}
	return (0);
}

int		open_dir(t_arg *option, char *dpath, char *dname)
{
//	printf("fct : open_dir\n");
	DIR					*p_dir;
	t_flist				*lst2;
	t_flist				*tmp;
	
	lst2 = NULL;
	p_dir = opendir(dpath);
	if (p_dir == NULL)
		return (ft_error(3, dname));
	fill_list(p_dir, &lst2, option, dpath);
	closedir(p_dir);
	tmp = lst2;
	while(tmp)
	{
//		printf("\n-------- lst2 -------\n name : %s,\npath :%s,\nowner : %s,\n-----option -R :%d\n", tmp->name, tmp->path, tmp->owner, option->recu);
		tmp = tmp->next;	
	}
	while (option->recu == 1 && lst2)
	{
		if (ft_strcmp(lst2->name, ".") != 0 && ft_strcmp(lst2->name, "..") != 0)
			open_dir(option, format_path(dpath, lst2->name, 
						ft_strlen(lst2->name)), lst2->name);
		lst2 = lst2->next;
	}
	return (1);
}

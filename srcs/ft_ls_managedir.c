/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managedir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:40:26 by avacher           #+#    #+#             */
/*   Updated: 2016/01/21 14:19:11 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

int		lst_pushback(t_flist **list, char *name)
{
//	printf("fct : lst_pushback\n");
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

int		fill_list(DIR *p_dir, t_flist **lst, t_arg *option)
{
//	printf("fct : fill_list\n");
	struct dirent		*p_dirent;
	int					i;

	i = 0;
	while ((p_dirent = readdir(p_dir)) != NULL) 
	{
		ls_display(p_dirent, option, lst);	
	//	printf("dir content :%s\n", p_dirent->d_name);
		if (p_dirent->d_type == DT_DIR)
			lst_pushback(lst, p_dirent->d_name);
		i++;
	}
	return (0);
}

int		open_dir(t_arg *option, char *dpath, char *dname)
{
//	printf("fct : open_dir\n");
	int					i;
	DIR					*p_dir;
	t_flist				*lst;
	
	i = 0;
	lst = NULL;
	p_dir = opendir(dpath);
	if (p_dir == NULL)
		return (ft_error(3, dname));
	fill_list(p_dir, &lst, option);
	closedir(p_dir);
	while (option->recu == 1 && lst)
	{
		if (ft_strcmp(lst->name, ".") != 0 && ft_strcmp(lst->name, "..") != 0)
			open_dir(option, format_path(dpath, lst->name, 
						ft_strlen(lst->name)), lst->name);
		lst = lst->next;
	}
	return (0);
}

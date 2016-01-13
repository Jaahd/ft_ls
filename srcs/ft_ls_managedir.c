/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:27:11 by avacher           #+#    #+#             */
/*   Updated: 2016/01/13 16:15:38 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

int		dirlst_pushb(t_dlist **dirlist, char *dname)
{
	t_dlist		*tmp;
	t_dlist		*new;

	tmp = *dirlist;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if ((new = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		ft_error(1, dname);
	new->next = NULL;
	if ((new->dname = ft_strdup(dname)) == NULL)
		ft_error(1, dname);
	if (tmp)
		tmp->next = new;
	else
		*dirlist = new;
	return (0);
}

int		fill_dirlist(DIR *p_dir, t_dlist **dir_lst, t_arg *argmt)
{
	struct dirent		*p_dirent;
	int					i;

	i = 0;
	while ((p_dirent = readdir(p_dir)) != NULL) 
	{
		ls_display(p_dirent, argmt, argmt->n_arg[i], argmt->fpath[i]);	
	//	printf("dir content :%s\n", p_dirent->d_name);
		if (p_dirent->d_type == DT_DIR)
			dirlst_pushb(dir_lst, p_dirent->d_name);
		i++;
	}
	return (0);
}

int		open_dir(t_arg argmt, char *dpath, char *dname)
{
	int					i;
	DIR					*p_dir;
	t_dlist				*dir_lst;
	
	i = 0;
	dir_lst = NULL;
	p_dir = opendir(dpath);
	if (p_dir == NULL)
		return (ft_error(3, dname));
	fill_dirlist(p_dir, &dir_lst, &argmt);
	closedir(p_dir);
	while (argmt.rec == 1 && dir_lst)
	{
		if (ft_strcmp(dir_lst->dname, ".") != 0 && 
				ft_strcmp(dir_lst->dname, "..") != 0)
			open_dir(argmt, format_path(dpath, dir_lst->dname,
					ft_strlen(dir_lst->dname)),
			 	dir_lst->dname);
		dir_lst = dir_lst->next;
	}
	return (0);
}


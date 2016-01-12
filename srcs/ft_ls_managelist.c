/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:27:11 by avacher           #+#    #+#             */
/*   Updated: 2016/01/12 21:00:05 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

int		open_dir(t_arg argmt, char *dpath, char *dname)
{
	int					i;
	DIR					*pDir;
	t_dlist				*dir_lst;
	
	i = 0;
	dir_lst = NULL;
	pDir = opendir(dpath);
	if (pDir == NULL)
		return (ft_error(3, dname));
	fill_dirlist(pDir, &dir_lst);
	closedir(pDir);
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

int		fill_dirlist(DIR *pDir, t_dlist **dir_lst)
{
	struct dirent		*pDirent;

	while ((pDirent = readdir(pDir)) != NULL) 
	{
		printf("dir content :%s\n", pDirent->d_name);
		if (pDirent->d_type == DT_DIR)
			dirlst_pushb(dir_lst, pDirent->d_name);
	}
	return (0);
}

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

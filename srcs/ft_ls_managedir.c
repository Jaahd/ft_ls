/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managedir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:40:26 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:25:51 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

int		fill_list(DIR *p_dir, t_flist **lst2, t_arg *option, char *dpath)
{
	struct dirent		*p_dirent;
	t_flist				*new;
	t_flist				*tmp;
	char				*str;

	while ((p_dirent = readdir(p_dir)) != NULL) 
	{
		new = lst_new(p_dirent->d_name, (str = format_path(dpath,
			p_dirent->d_name, ft_strlen(p_dirent->d_name))), &option);
		free(str);
		if (*lst2 == NULL)
			*lst2 = new;
		else if (option->t == 1)
			lst_time_insert(option, lst2, new);
		else
			lst_insert(option, lst2, new);
	}
	tmp = *lst2;
	display_total(&option);
	while(tmp)
	{
		if (option->a == 1 || (option->a == 0 && tmp->name[0] != '.'))
			ls_display(option, &tmp);	
		tmp = tmp->next;	
	}
	return (0);
}

int		open_dir(t_arg *option, char *dpath)
{
	//		printf("fct : open_dir\n");
	DIR					*p_dir;
	t_flist				*lst2;
	t_flist				*tmp;
	char				*str;

	lst2 = NULL;
	p_dir = opendir(dpath);
	if (p_dir == NULL)
		return (0);
	fill_list(p_dir, &lst2, option, dpath);
	closedir(p_dir);
	tmp = lst2;
	while (option->recu == 1 && tmp)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
		&& ft_strcmp(tmp->name, ".."))
		{
			display_dirname(option, tmp->path);
			open_dir(option, (str = format_path(dpath, tmp->name, 
						ft_strlen(tmp->name))));
			free(str);
		}
		option->size_len = 0;
		tmp = tmp->next;
	}
	free_s_flist(&lst2);
	return (1);
}

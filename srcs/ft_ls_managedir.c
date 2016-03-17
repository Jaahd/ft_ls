/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managedir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 17:03:22 by avacher           #+#    #+#             */
/*   Updated: 2016/02/13 17:03:22 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

static int		first_display_dir(t_flist **lst2, t_arg *option, int i)
{
	t_flist				*tmp;

	tmp = *lst2;
	display_total(&option, i);
	while (tmp)
	{
		if (option->a == 1 || (option->a == 0 && tmp->name[0] != '.'))
			ls_display(option, &tmp);
		tmp = tmp->next;
	}
	return (0);
}

static int		fill_list(DIR *p_dir, t_flist **lst2, t_arg *option, char *path)
{
	struct dirent		*p_dirent;
	t_flist				*new;
	char				*str;
	int					i;

	i = 0;
	while ((p_dirent = readdir(p_dir)) != NULL)
	{
		str = format_path(path, p_dirent->d_name, ft_strlen(p_dirent->d_name));
		if ((new = lst_new(p_dirent->d_name, str, &option)) == NULL)
			continue ;
		if (*lst2 == NULL)
			*lst2 = new;
		else if (option->t == 1)
			lst_time_insert(option, lst2, new);
		else
			lst_insert(option, lst2, new);
		if (option->a == 1 || (option->a == 0 && new->name[0] != '.'))
			i++;
	}
	first_display_dir(lst2, option, i);
	return (0);
}

static int		open_dir(t_flist **lst2, t_arg *option, char *dpath, char *name)
{
	DIR					*p_dir;

	if ((p_dir = opendir(dpath)) == NULL)
		return (ft_error(3, name));
	fill_list(p_dir, lst2, option, dpath);
	closedir(p_dir);
	return (0);
}

int				recu_dir(t_arg *option, char *dpath, char *name)
{
	t_flist				*lst2;
	t_flist				*tmp;
	char				*str;

	lst2 = NULL;
	if ((open_dir(&lst2, option, dpath, name)) == -1)
		return (-1);
	tmp = lst2;
	while (option->recu == 1 && tmp)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
				&& ft_strcmp(tmp->name, "..") && (option->a == 1
					|| (option->a != 1 && tmp->name[0] != '.')))
		{
			display_dirname(option, tmp->path);
			option->lk_len = 0;
			option->size_len = 0;
			recu_dir(option, (str = format_path(dpath, tmp->name,
							ft_strlen(tmp->name))), tmp->name);
		}
		option->size_len = 0;
		tmp = tmp->next;
	}
	return (1);
}

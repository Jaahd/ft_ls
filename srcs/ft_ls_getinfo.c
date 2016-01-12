/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:48:37 by avacher           #+#    #+#             */
/*   Updated: 2016/01/12 17:01:24 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include "ft_ls.h"

char	*format_path(char *b_path, char *filename, int namelen)
{
	char			*tmp;
	char			*f_path;

	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (b_path[ft_strlen(b_path) - 1] != '/')
	{
		if((tmp = ft_strjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if(((f_path = ft_strjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	ft_strdel(&tmp);
	return (f_path);
}

int		bubble_sort(t_arg *argmt)
{
	int		i;
	int		j;

	i = 0;
	while (i < argmt->arg_nb)
	{
		j = i + 1;
		while (j < argmt->arg_nb)
		{
			if (ft_strcmp(argmt->n_arg[i], argmt->n_arg[j]) > 0)
			{
				ft_swap(&(argmt->n_arg[i]), &(argmt->n_arg[j]));
				ft_swap(&(argmt->fpath[i]), &(argmt->fpath[j]));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		get_options(t_arg *argmt, int *ac_c, char **av)
{
	int				i;
	int				cpt;

	cpt = 1;
	while (cpt < *ac_c)
	{
		i = 1;
		while (av[cpt][0] == '-' && av[cpt][i])
		{
			if (av[cpt][i] != 'R' && av[cpt][i] != 'a' && av[cpt][i] != 'l' &&
					av[cpt][i] != 'r' && av[cpt][i] != 't')
				ft_error(2, &av[cpt][i]);
			argmt->R = (av[cpt][i] == 'R') ? 1 : argmt->R;
			argmt->a = (av[cpt][i] == 'a') ? 1 : argmt->a;
			argmt->l = (av[cpt][i] == 'l') ? 1 : argmt->l;
			argmt->r = (av[cpt][i] == 'r') ? 1 : argmt->r;
			argmt->t = (av[cpt][i] == 't') ? 1 : argmt->t;
			i++;
		}
		if (av[cpt][0] != '-')
			break ;
		cpt++;
	}
	*ac_c -= cpt;
	return (0);
}

int		get_name(t_arg *argmt, int ac, int *ac_c, char **av)
{
	int				i;

	i = 0;
	if (*ac_c == 0)
	{
		if ((argmt->n_arg[0] = ft_strdup(".")) == NULL)
			ft_error(1, ".");
		if ((argmt->fpath[0] = ft_strdup("./")) == NULL)
			ft_error(1, "./");
	}
	while (i < *ac_c)
	{
		if((argmt->n_arg[i] = ft_strdup(av[ac - *ac_c + i])) == NULL)
			ft_error(1, argmt->n_arg[i]);
		argmt->fpath[i] = format_path("./", argmt->n_arg[i], ft_strlen(argmt->n_arg[i]));
		i++;
	}
	argmt->n_arg[i] = NULL;
	argmt->fpath[i] = NULL;
	return (0);
}

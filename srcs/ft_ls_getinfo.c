/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:48:37 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:25:39 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		fonction(t_flist **new, char *av, char *tmp, t_arg *option)
{
	*new = lst_new(av, tmp, &option);
	ft_strdel(&tmp);
	return (0);
}

int		get_name(t_arg *option, t_flist **lst, int ac_c, char **av)
{
	t_flist			*new;
	char			*tmp;
	int				cpt;

	cpt = 1;
	if (ac_c == 0)
		open_dir(option, "./");
	while (av[cpt] && av[cpt][0] == '-')
		cpt++;
	while (av[cpt])
	{
		tmp = format_path("./", av[cpt], ft_strlen(av[cpt]));
		if (av[cpt][0] == '/')
			new = lst_new("", av[cpt], &option);
		else
			fonction(&new, av[cpt], tmp, option);
		if (*lst == NULL)
			*lst = new;
		else if(option->t == 1)
			lst_time_insert(option, lst, new);
		else
			lst_insert(option, lst, new);
		cpt++;
	}
	return (0);
}

char	*format_path(char *b_path, char *filename, int namelen)
{
	char			*tmp;
	char			*f_path;
	int				p_len;

	tmp = NULL;
	p_len = ft_strlen(b_path);
	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (p_len > 0 && b_path[p_len - 1] != '/')
	{
		if ((tmp = ft_properjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else if (p_len > 0)
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if (((f_path = ft_properjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	free(tmp);
	return (f_path);
}

int		get_options(t_arg *opt, int *ac_c, char **av)
{
	int				i;
	int				cpt;

	cpt = 0;
	while (++cpt < *ac_c)
	{
		i = 1;
		while (av[cpt][0] == '-' && av[cpt][i])
		{
			if (av[cpt][i] != 'R' && av[cpt][i] != 'a' && av[cpt][i] != 'l' &&
					av[cpt][i] != 'r' && av[cpt][i] != 't' && av[cpt][i] != 'G')
				ft_error(2, &av[cpt][i]);
			opt->recu = (av[cpt][i] == 'R') ? 1 : opt->recu;
			opt->a = (av[cpt][i] == 'a') ? 1 : opt->a;
			opt->l = (av[cpt][i] == 'l') ? 1 : opt->l;
			opt->r = (av[cpt][i] == 'r') ? 1 : opt->r;
			opt->t = (av[cpt][i] == 't') ? 1 : opt->t;
			opt->colors = (av[cpt][i] == 'G') ? 1 : opt->colors;
			i++;
		}
		if (av[cpt][0] != '-')
			break ;
	}
	*ac_c -= cpt;
	return (0);
}

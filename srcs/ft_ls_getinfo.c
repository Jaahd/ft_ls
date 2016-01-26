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


int		get_name(t_arg *option, t_flist **lst, int ac_c, char **av)
{
//	printf("fct : get_name\n");
	t_flist			*new;
	int				cpt;

	cpt = 1;
	if (ac_c == 0)
	{
		open_dir(option, "./");
//		new = lst_new(".", "./", option);
//		*lst = new;
//		return (0);
	}
	while (av[cpt] && av[cpt][0] == '-')
		cpt++;
	while (av[cpt])
	{
		new = lst_new(av[cpt], format_path("./", av[cpt], ft_strlen(av[cpt])),
				option);
		if (*lst == NULL)
			*lst = new;
		else
			lst_insert(option, lst, new);
		cpt++;
	}
	return (0);
}

char	*format_path(char *b_path, char *filename, int namelen)
{
//	printf("fct : format_path\n");
	char			*tmp;
	char			*f_path;
	int				p_len;

	tmp = NULL;
	p_len = ft_strlen(b_path);
	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (p_len > 0 && b_path[p_len - 1] != '/')
	{
		if ((tmp = ft_strjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else if (p_len > 0)
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if (((f_path = ft_properjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	ft_strdel(&tmp);
	return (f_path);
}

int		get_options(t_arg *opt, int *ac_c, char **av)
{
//	printf("fct : get_options\n");
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
			opt->recu = (av[cpt][i] == 'R') ? 1 : opt->recu;
			opt->a = (av[cpt][i] == 'a') ? 1 : opt->a;
			opt->l = (av[cpt][i] == 'l') ? 1 : opt->l;
			opt->r = (av[cpt][i] == 'r') ? 1 : opt->r;
			opt->t = (av[cpt][i] == 't') ? 1 : opt->t;
			i++;
		}
		if (av[cpt][0] != '-')
			break ;
		cpt++;
	}
	*ac_c -= cpt;
	return (0);
}

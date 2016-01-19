/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:48:37 by avacher           #+#    #+#             */
/*   Updated: 2016/01/19 22:37:00 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

t_flist		*lst_new(char *name, char *fpath)
{
	t_flist			*new;
	
	if ((new = (t_flist *)malloc(sizeof(t_flist))) == NULL)
		ft_error (1, "list creation"); // nom a reprendre
	if ((new->name = ft_strdup(name)) == NULL)
		ft_error(1, name);
	new->path = fpath;
	new->type = 0;
	new->date = NULL;
	new->owner = NULL;
	new->group = NULL;
	new->rights = NULL;
	new->size = NULL;
	new->link_nb = NULL;
	new->link = NULL;
	new->next = NULL;
	return (new);
}

int		lst_insert(t_arg *opt, t_flist **lst, t_flist *new)
{
	t_flist			*tmp;
	int				cmp;

	tmp = *lst;
	while (tmp->next != NULL && (cmp = (opt->r ?
					ft_strcmp(new->name, tmp->next->name) :
					ft_strcmp(tmp->next->name, new->name)) < 0))
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
	return (0);
}

int		get_name(t_arg *opt, t_flist **lst, int ac_c, char **av)
{
	t_flist			*new;
	int				cpt;

	cpt = 1;
	if (ac_c == 0)
	{
		new = lst_new(".", "./");
		*lst = new;
	}
	while (av[cpt] && av[cpt][0] == '-')
		cpt++;
	while (av[cpt])
	{
		new = lst_new(av[cpt], format_path("", av[cpt], ft_strlen(av[cpt])));
		if (*lst == NULL)
			*lst = new;
		else
			lst_insert(opt, lst, new);
	}
	return (0);
}

char	*format_path(char *b_path, char *filename, int namelen)
{
	char			*tmp;
	char			*f_path;

	tmp = NULL;
	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (b_path && b_path[ft_strlen(b_path) - 1] != '/')
	{
		if ((tmp = ft_strjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else if (b_path)
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

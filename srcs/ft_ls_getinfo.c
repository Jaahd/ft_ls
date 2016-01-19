/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:48:37 by avacher           #+#    #+#             */
/*   Updated: 2016/01/19 19:46:07 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
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
		if ((tmp = ft_strjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if (((f_path = ft_strjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	ft_strdel(&tmp);
	return (f_path);
}
/*
int		get_mtime(t_arg *opt)
{
	struct stat		buff;
	int				i;

	i = 0;
	if ((opt->t_arg = (int *)malloc(sizeof(int) * (opt->arg_nb))) == NULL)
		ft_error(1, "opt.n_arg");
	while (lst->name[i])
	{
		stat(lst->path[i], &buff);	
		opt->t_arg[i] = buff.st_mtime;
		i++;
	}
	return (0);
}
*//*
int		bubble_sort(t_arg *opt)
{
	int		cmp;
	int		i;
	int		j;

	i = -1;
	while (++i < opt->arg_nb)
	{
		j = i + 1;
		while (j < opt->arg_nb)
		{
			if (opt->t == 1)
				cmp = opt->r ? (opt->t_arg[i] - opt->t_arg[j]) : 
					(opt->t_arg[j] - opt->t_arg[i]);
			else
				cmp = opt->r ? ft_strcmp(lst->name[j], lst->name[i]) : 
					ft_strcmp(lst->name[i], lst->name[j]);
			if (cmp > 0)
			{
				ft_swap(&(lst->name[i]), &(lst->name[j]));
				ft_swap(&(lst->path[i]), &(lst->path[j]));
				int_swap(&(opt->t_arg[i]), &(opt->t_arg[j]));
			}
			j++;
		}
	}
	return (0);
}
*/
void	lst_swap(t_flist **lst, char *s1, t_arg *opt)
{
	t_flist		*tmp;
	t_flist		*tmp2;
	char		*str;

	tmp = *lst;
	str = (opt->t == 1 ? tmp->date : tmp->name);
	while (tmp && tmp->next && str != s1)
	{
		tmp2 = tmp->next->next;
		tmp->next->prev = tmp->prev;
		tmp->next->next = tmp;
		tmp->prev = tmp->next;
		tmp->next = tmp2;
	}
}

int		bubble_sort(t_arg *opt, t_flist *lst)
{
	int			cmp;
	t_flist		*tmp;
	t_flist		*tmp2;

	tmp = lst;
	tmp2 = lst->next;

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

int		get_name(t_flist *lst, int ac, int *ac_c, char **av)
{
	int				i;

	i = 0;
	if (*ac_c == 0)
	{
		if ((lst->name = ft_strdup(".")) == NULL)
			ft_error(1, ".");
		if ((lst->path = ft_strdup("./")) == NULL)
			ft_error(1, "./");
	}
	while (i < *ac_c)
	{
		if ((lst->name = ft_strdup(av[ac - *ac_c + i])) == NULL)
			ft_error(1, lst->name);
		if (lst->name[0] != '/')
			lst->path = format_path("./", lst->name, ft_strlen(lst->name));
		else
			lst->path = ft_strdup(lst->name);
		lst->prev = lst;
		lst = lst->next;
		i++;
	}
	return (0);
}

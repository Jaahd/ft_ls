/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:48:37 by avacher           #+#    #+#             */
/*   Updated: 2016/01/08 13:34:26 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include "ft_ls.h"

int		get_options(t_arg *argmt, int *ac_c, char **av)
{	
	int				i;
	int				cpt;

	cpt = 1;
	while(cpt < *ac_c)
	{
		i = 1;
		while(av[cpt][0] == '-' && av[cpt][i])
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
	if ((argmt->n_arg = (char **)malloc(sizeof(char *) * (1 + *ac_c))) == NULL) 
		ft_error(1, *argmt->n_arg);
	if ((argmt->fpath = (char **)malloc(sizeof(char *) * (1 + *ac_c))) == NULL)
		ft_error(1, *argmt->fpath);
	if (*ac_c == 0)
	{
		argmt->n_arg[0] = ft_strdup(".");
		argmt->fpath[0] = ft_strdup("./");
	}
	while(i < *ac_c)
	{
		argmt->n_arg[i] = ft_strdup(av[ac - *ac_c + i]);
		argmt->fpath[i] = ft_strjoin("./", av[ac - *ac_c + i]);
		i++;
	}
	argmt->n_arg[i] = NULL;
	argmt->fpath[i] = NULL;
	return (0);
}


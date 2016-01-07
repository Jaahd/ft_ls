/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/07 21:50:10 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*##### readdir met qqch dans errno!!!!!!!!!!!!#############*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"

void	ft_error(int error)
{
	if (error == 1)
		perror("memory allocation failure");
	exit(EXIT_FAILURE);
}

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
	if (((argmt->n_arg = (char **)malloc(sizeof(char *) * (2 + *ac_c))) == NULL) 
	|| ((argmt->fpath = (char **)malloc(sizeof(char *) * (2 + *ac_c))) == NULL))
		ft_error(1);
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
	argmt->n_arg[i + 1] = NULL;
	argmt->fpath[i + 1] = NULL;
	return (0);
}

int		main(int ac, char **av)
{
	t_arg			argmt;
	int				ac_c;

	ac_c = ac;
	get_options(&argmt, &ac_c, av);
	get_name(&argmt, ac, &ac_c, av);
	printf("n_arg :'%s'\n", argmt.n_arg[0]);
	printf("fpath :'%s'\n", argmt.fpath[0]);
	printf("R :%d\ta :%d\tl :%d\tr :%d\tt :%d\n", argmt.R, argmt.a, argmt.l, argmt.r, argmt.t);
	return (0);
}

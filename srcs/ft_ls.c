/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/07 19:01:12 by avacher          ###   ########.fr       */
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

int		get_options(t_arg *argmt, int ac, char **av)
{
	int				cpt;
	char			*tmp;

	cpt = 1;
	if ((argmt->options = ft_strnew(1)) == NULL)
		ft_error(1);
	while (cpt <= ac && av[cpt][0] == '-')
	{
		tmp = argmt->options;
		argmt->options = ft_properjoin(argmt->options, av[cpt] + 1);
		ft_strdel(&tmp);
		cpt++;
	}
	return (0);
}

int		get_name(t_arg *argmt, int ac, char **av)
{
	if (ac == 1)
	{
		if ((argmt->arg_name = (char **)malloc(sizeof(char *) * 2)) == NULL 
		|| (argmt->format_path = (char **)malloc(sizeof(char *) * 2)) == NULL)
			ft_error(1);
		argmt->arg_name[0] = ".";
		argmt->format_path[0] = "./";
	}
	argmt->format_path[ac] = NULL;
	argmt->arg_name[ac] = NULL;
	return (0);
}

int		main(int ac, char **av)
{
	t_arg			argmt;

	get_name(&argmt, ac, av);
	return (0);
}

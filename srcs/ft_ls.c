/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 17:03:22 by avacher           #+#    #+#             */
/*   Updated: 2016/02/13 17:03:22 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"

int		ft_error(int error, char *cur_pb)
{
	if (error == 1)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(cur_pb);
		exit(EXIT_FAILURE);
	}
	if (error == 2)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(*cur_pb, 2);
		ft_putendl_fd("\nusage: ft_ls [GRagloprt] [file ...]", 2);
		exit(EXIT_FAILURE);
	}
	if (error == 3)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(cur_pb);
	}
	return (0);
}

int		free_s_flist(t_flist **lst)
{
	t_flist		*tmp;

	while (*lst)
	{
		free(&(*lst)->name);
		free(&(*lst)->path);
		free(&(*lst)->date);
		free(&(*lst)->year);
		free(&(*lst)->owner);
		free(&(*lst)->group);
		free(&(*lst)->size);
		free(&(*lst)->major);
		free(&(*lst)->minor);
		free(&(*lst)->link_nb);
		free(&(*lst)->link);
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_flist		*lst;
	t_arg		option;
	int			ac_c;

	ac_c = ac;
	lst = NULL;
	init_options(&option);
	get_options(&option, &ac_c, av);
	option.arg_nb = ac_c;
	get_name(&option, &lst, ac_c, av);
	first_display(&lst, &option);
	return (0);
}

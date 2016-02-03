/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:26:19 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h> /* -> getpwduid */
#include <pwd.h> /* -> getpwduid */
#include <grp.h> /* -> get grgid */
#include <sys/errno.h>
#include <sys/stat.h>
#include <time.h> /* for ctime -> pour modif format de time */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"

int		ft_error(int error, char *cur_pb)
{
	ft_putstr("ft_ls: ");
	if (error == 1)
	{
		perror(cur_pb);
		exit(EXIT_FAILURE);
	}
	if (error == 2)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(*cur_pb, 2);
		ft_putendl_fd("\nusage: ft_ls [Ralrt] [file ...]", 2);
		exit(EXIT_FAILURE);
	}
	if (error == 3)
		perror(cur_pb);
	return (0);
}

int		init_options(t_arg *option)
{
	option->recu = 0;
	option->a = 0;
	option->l = 0;
	option->r = 0;
	option->t = 0;
	option->colors = 0;
	option->arg_nb = 0;
	option->own_len = 0;
	option->gr_len = 0;
	option->lk_len = 0;
	option->maj_len = 0;
	option->min_len = 0;
	option->size_len = 0;
	option->tot_blocks = 0;
	return (0);
}

int		free_s_flist(t_flist **lst)
{
	t_flist		*tmp;

	while (*lst)
	{
		free(&(*lst)->name); // pb mem
		free(&(*lst)->path); //pb mem
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
	printf("fct : main\n");
	t_flist			*lst;
	t_arg			option;
	int				ac_c;
	int	i;

	i = -1;
	ac_c = ac;
	lst = NULL;
	init_options(&option);
	get_options(&option, &ac_c, av);
	option.arg_nb = ac_c;
	get_name(&option, &lst, ac_c, av);
	first_display(&lst, &option);
//	free_s_flist(&lst);
//	while (1);
	return (0);
}

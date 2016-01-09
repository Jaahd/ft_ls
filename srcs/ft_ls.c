/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/08 13:32:44 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h> /* -> getpwduid */
#include <pwd.h> /* -> getpwduid */
#include <grp.h> /* -> get grgid */
#include <uuid/uuid.h> /* -> getpwduid & getgrgid */
#include <sys/errno.h>
#include <sys/stat.h>
#include "libft.h"
#include <time.h> /* for ctime -> pour modif format de time */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"
/*##### readdir met qqch dans errno!!!!!!!!!!!!#############*/

void	ft_error(int error, char *cur_pb)
{	
	ft_putstr("ft_ls: ");
	if (error == 1)
		perror(cur_pb);
	if (error == 2)
	{
		ft_putstr_fd("illegal option -- ", 2);
		ft_putchar_fd(*cur_pb, 2);
		ft_putendl_fd("\nusage: ft_ls [Ralrt] [file ...]", 2);
	}
	exit(EXIT_FAILURE);
}

int		bubble_sort(t_arg *argmt)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while(argmt->n_arg[j] != NULL)
	{
		if(ft_strcmp(argmt->n_arg[i], argmt->n_arg[j]) > 0)
		{
			ft_swap(argmt->n_arg[i], argmt->n_arg[j]);
			i = 0;
			j = 1;
		}
		i++;
		j++;
	}
}

int		read_file(t_arg *argmt)
{
	int		i;

	i = 0;
	while(argmt->n_arg[i] != NULL)
	{
		printf("%s\n",argmt->n_arg[i]);
		i++;
	}
	return 0;
}

int		main(int ac, char **av)
{
	t_arg			argmt;
	int				ac_c;

	ac_c = ac;
	get_options(&argmt, &ac_c, av);
	get_name(&argmt, ac, &ac_c, av);
	read_file(&argmt);	
	/* printf a virer */
//	printf("n_arg :'%s'\n", argmt.n_arg[0]);
//	printf("n_arg2 :'%s'\n", argmt.n_arg[1]);
//	printf("fpath :'%s'\n", argmt.fpath[0]);
//	printf("fpath2 :'%s'\n", argmt.fpath[1]);
//	printf("R :%d\ta :%d\tl :%d\tr :%d\tt :%d\n", argmt.R, argmt.a, argmt.l, argmt.r, argmt.t);
	/* printf a virer */
	return (0);
}

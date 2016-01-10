/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 13:24:50 by avacher          ###   ########.fr       */
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

/*##### readdir met qqch dans errno!!!!!!!!!!!!#############*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"

void	ft_error(int error, char *cur_pb)
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
}

int		read_file(t_arg *argmt)
{
	int					i;
	DIR					*pDir;

	i = 0;
	while (i < argmt->arg_nb)
	{
		if (isadir(argmt->fpath[i]))
		{
			pDir = opendir(argmt->n_arg[i]);
			if (pDir != NULL)
			{
				printf("pDir : %s\n", argmt->n_arg[i]);
				closedir(pDir);
			}
			else
				ft_error(3, argmt->n_arg[i]);
		}
		else
			printf("file :%s\n", argmt->n_arg[i]);
			/* afficher juste le fichier */
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_arg			argmt;
	int				ac_c;
	int	i;
	i = 0;
	ac_c = ac;
	get_options(&argmt, &ac_c, av);
	get_name(&argmt, ac, &ac_c, av);
	argmt.arg_nb = ac_c;
	bubble_sort(&argmt);
	read_file(&argmt);
/*	while (argmt.n_arg[i] != NULL)
	{
		printf("arg : %s\n", argmt.n_arg[i]);
		i++;
	}
	printf("---END---\n\n");
*/	/* printf a virer */
	//	printf("n_arg :'%s'\n", argmt.n_arg[0]);
	//	printf("n_arg2 :'%s'\n", argmt.n_arg[1]);
	//	printf("fpath :'%s'\n", argmt.fpath[0]);
	//	printf("fpath2 :'%s'\n", argmt.fpath[1]);
	//	printf("R :%d\ta :%d\tl :%d\tr :%d\tt :%d\n", argmt.R, argmt.a, argmt.l, argmt.r, argmt.t);
	/* printf a virer */
	return (0);
}

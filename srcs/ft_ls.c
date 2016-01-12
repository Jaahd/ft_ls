/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/12 17:42:18 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h> /* -> getpwduid */
#include <pwd.h> /* -> getpwduid */
#include <grp.h> /* -> get grgid */
// #include <uuid/uuid.h> /* -> deja inclu ds getpwduid & getgrgid */
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
	return (EXIT_FAILURE);
}

int		fill_dirlist(DIR *pDir, t_dlist **dir_lst)
{
	struct dirent		*pDirent;

	while ((pDirent = readdir(pDir)) != NULL) 
	{
		if (pDirent->d_type == DT_DIR)
			dirlst_pushb(dir_lst, pDirent->d_name);
	}
	return (0);
}

int		open_dir(char *dpath, char *dname)
{
	int					i;
	DIR					*pDir;
	t_dlist				*dir_lst;
	
	i = 0;
	dir_lst = NULL;
	pDir = opendir(dpath);
	if (pDir == NULL)
		return (ft_error(3, dname));
	fill_dirlist(pDir, &dir_lst);
	closedir(pDir);
	printf("pouet\n");
	while (dir_lst)
	{
		printf("trololo\n");
		printf("path:%s\tdir name:%s\n", format_path(dpath, dir_lst->dname, ft_strlen(dir_lst->dname)), dir_lst->dname);
		if (ft_strcmp(dir_lst->dname, ".") != 0 && 
				ft_strcmp(dir_lst->dname, "..") != 0)
			open_dir(format_path(dpath, dir_lst->dname, ft_strlen(dir_lst->dname)),
			 	dir_lst->dname);
		dir_lst = dir_lst->next;
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
	argmt.arg_nb = ac_c;
	if ((argmt.n_arg = (char **)malloc(sizeof(char *) * (argmt.arg_nb + 1))) == NULL)
		ft_error(1, "argmt.n_arg");
	if ((argmt.fpath = (char **)malloc(sizeof(char *) * (argmt.arg_nb + 1))) == NULL)
		ft_error(1, "argmt.fpath");
	get_name(&argmt, ac, &ac_c, av);
	bubble_sort(&argmt);
	while (i < argmt.arg_nb)
	{
		open_dir(argmt.fpath[i], argmt.n_arg[i]);
		printf("n_arg :%s\tfpath :%s\n", argmt.n_arg[i], argmt.fpath[i]);
		i++;
	}
	//	read_dir(&argmt);
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
}//

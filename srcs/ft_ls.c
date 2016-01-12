/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:10:43 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 18:59:30 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h> /* -> getpwduid */
#include <pwd.h> /* -> getpwduid */
#include <grp.h> /* -> get grgid */
// #include <uuid/uuid.h> /* -> getpwduid & getgrgid */
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

char	*format_path(char *b_path, char *filename, int namelen)
{
	char			*tmp;
	char			*f_path;

	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (b_path[ft_strlen(b_path) - 1] != '/')
	{
		if((tmp = ft_strjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if(((f_path = ft_strjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	ft_strdel(&tmp);
	return (f_path);
}

int		fill_dirlist(DIR *pDir, t_dlist **dir_list)
{
	struct dirent		*pDirent;
	
	while ((pDirent = readdir(pDir)) != NULL) 
	{
		printf("dir content :%s\n", pDirent->d_name);
		if (pDirent->d_type == DT_DIR)
			dirlst_pushb(dir_list, pDirent->d_name);
	}
	return (0);
}
/*
int		open_dir(char *dpath, char *dname)
{
	int					i;
	DIR					*pDir;
	t_dlist				*dir_list;
	
	i = 0;
	pDir = opendir(dpath);
	if (pDir == NULL)
		ft_error(3, dname);
	fill_dirlist(pDir, &dir_list);
	while (dir_list != NULL)
	{
		open_dir(format_path(dpath, dir_list->dname), dir_list->dname);
		dir_list = dir_list->next;
	}
	return (0);
}
*/
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
		printf("n_arg :%s\tfpath :%s\n", argmt.n_arg[i], argmt.fpath[i]);
/*		open_dir(argmt.fpath[i], argmt.n_arg[i]);
*/		i++;
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

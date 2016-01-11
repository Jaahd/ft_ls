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

int		read_dir(DIR *pDir)
{
/*	struct dirent		*pDirent;
	int					type;
	char				*name;

	while ((pDirent = readdir(pDir)) != NULL)
	{
		type = pDirent->d_type;
		name = pDirent->d_name;
	}
*/	pDir = (DIR *)pDir;	
	return (0);
}

char	*format_path(char *b_path, char *filename, int namelen)
{
	char			*f_path;

	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if((f_path = ft_properjoin(b_path, filename) == NULL))
		ft_error(1, filename);
	return (f_path);
}

int		display(DIR *pDir, t_dlist **dir_list)
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

int		open_dir(char *dpath, char *dname)
{
	int					i;
	DIR					*pDir;
	t_dlist				*dir_list;
	
	i = 0;
	pDir = opendir(dpath);
	if (pDir == NULL)
		ft_error(3, dname);
	display(pDir, &dir_list);
	while (dir_list != NULL)
	{
		open_dir(format_path(dpath, dir_list->dname), dir_list->dname);
		dir_list = dir_list->next;
	}
	return (0);
}

/* fonction qui sera recursive et appelera toutes les autres fonctions */

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
	while (i < argmt.arg_nb)
	{
		open_dir(argmt.fpath[i], argmt.n_arg[i]);
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
}

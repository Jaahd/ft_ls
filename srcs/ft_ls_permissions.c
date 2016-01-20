/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:07:32 by avacher           #+#    #+#             */
/*   Updated: 2016/01/20 17:47:59 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"
#include "libft.h"

int		file_size(t_flist **lst, t_arg **option, struct stat buff_stat)
{
	int						size;
	(*lst)->size = ft_itoa(buff_stat.st_size);
	size = ft_strlen((*lst)->size);
	printf("taille de la size%d\n", size);
	if (size > (*t_arg)->size_len)
		(*t_arg)->size_len = size;
	return (0);
}

int		file_rights(t_flist **lst, struct stat buff_stat)
{
		(*lst)->rights[0] = (*lst)->type;
		(*lst)->rights[1] = (buff_stat.st_mode & S_IRUSR) ? 'r' : '-';
		(*lst)->rights[2] = (buff_stat.st_mode & S_IWUSR) ? 'w' : '-';
		(*lst)->rights[3] = (buff_stat.st_mode & S_IXUSR) ? 'x' : '-';
		(*lst)->rights[4] = (buff_stat.st_mode & S_IRGRP) ? 'r' : '-'; 
		(*lst)->rights[5] = (buff_stat.st_mode & S_IWGRP) ? 'w' : '-'; 
		(*lst)->rights[6] = (buff_stat.st_mode & S_IXGRP) ? 'x' : '-';
		(*lst)->rights[7] = (buff_stat.st_mode & S_IROTH) ? 'r' : '-';
		(*lst)->rights[8] = (buff_stat.st_mode & S_IWOTH) ? 'w' : '-';
		(*lst)->rights[9] = (buff_stat.st_mode & S_IXOTH) ? 'x' : '-';
		(*lst)->rights[10] = '\0';
		return (0);
}

char	file_type(struct stat buff_stat)
{
	char				type;

	if(S_ISBLK(buff_stat.st_mode))
		type = 'b';
	else if(S_ISREG(buff_stat.st_mode))
		type = '-';
	else if(S_ISCHR(buff_stat.st_mode))
		type = 'c';
	else if(S_ISDIR(buff_stat.st_mode))
		type = 'd';
	else if(S_ISFIFO(buff_stat.st_mode))
		type = 'p';
	else if(S_ISLNK(buff_stat.st_mode))
		type = 'l';
	else if(S_ISSOCK(buff_stat.st_mode))
		type = 's';
	else
		type = '?';
	return (type);
}

int		option_l(struct stat buff_stat, struct passwd *passwd, struct group *group, t_flist **lst, t_arg **option)
{
		(*lst)->owner = passwd->pw_name;
		printf("owner : %s\t", (*lst)->owner);
		(*lst)->group = group->gr_name;
		printf("group : %s\t", (*lst)->group);
		file_rights(lst, buff_stat);
		printf("rights : %s\t", (*lst)->rights);
/*		(*lst)->size = file_size(lst, buff_stat);
		printf("size : %s\n", (*lst)->size);
	*/	(*lst)->link_nb = ft_itoa(buff_stat.st_nlink);
		printf("nb de liens : %s\n", (*lst)->link_nb);
/*		if ((*lst)->type == 'l')
		{
			(*lst)->link = readlink();
			printf("link : %s\n", (*lst)->link);
		}*/
		return (0);
}
		
int		file_info(char *path, t_arg **option, t_flist **lst)
{
	//	printf("fct : isadir\n");
	struct stat			buff_stat;
	struct passwd		*passwd;
	struct group		*group;
	char				*time_tmp;

	lstat(path, &buff_stat);
	if ((passwd = getpwuid(buff_stat.st_uid)) == NULL)
		passwd->pw_name = ft_itoa(buff_stat.st_uid);
 	if ((group = getgrgid(buff_stat.st_gid)) == NULL)
		group->gr_name = ft_itoa(buff_stat.st_gid);
 	group = getgrgid(buff_stat.st_gid);
	(*lst)->type = file_type(buff_stat);
	printf("type de fichier : %c\t", (*lst)->type);
	time_tmp = NULL;
	if (option.l == 1 || option.t == 1)
	{
		time_tmp = ctime(&buff_stat.st_mtime);
		(*lst)->date = ft_strsub(time_tmp, 4, 12);
		printf("date : %s\t", (*lst)->date);
	}
	if (option.l == 1)
	{
		option_l(buff_stat, passwd, group, lst, option);
	}
	return (S_ISDIR(buff_stat.st_mode));
}

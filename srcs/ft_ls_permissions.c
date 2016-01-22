/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:07:32 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:25:17 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <sys/syslimits.h> /*pour path_max */
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> /*pour la fonction readlink */
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"
#include "libft.h"

int		file_size(t_flist *lst, t_arg *option, struct stat buff_stat)
{
	lst->size = ft_itoa(buff_stat.st_size);
	lst->fsize_len = ft_strlen(lst->size);
	if (lst->fsize_len > option->size_len)
		option->size_len = lst->fsize_len;
	return (0);
}

int		file_rights(t_flist *lst, struct stat buff_stat)
{
		lst->rights[0] = lst->type;
		lst->rights[1] = (buff_stat.st_mode & S_IRUSR) ? 'r' : '-';
		lst->rights[2] = (buff_stat.st_mode & S_IWUSR) ? 'w' : '-';
		lst->rights[3] = (buff_stat.st_mode & S_IXUSR) ? 'x' : '-';
		lst->rights[4] = (buff_stat.st_mode & S_IRGRP) ? 'r' : '-'; 
		lst->rights[5] = (buff_stat.st_mode & S_IWGRP) ? 'w' : '-'; 
		lst->rights[6] = (buff_stat.st_mode & S_IXGRP) ? 'x' : '-';
		lst->rights[7] = (buff_stat.st_mode & S_IROTH) ? 'r' : '-';
		lst->rights[8] = (buff_stat.st_mode & S_IWOTH) ? 'w' : '-';
		lst->rights[9] = (buff_stat.st_mode & S_IXOTH) ? 'x' : '-';
		lst->rights[10] = ' ';
		lst->rights[11] = ' ';
		lst->rights[12] = '\0';
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

int		type_l(t_flist *lst)
{
	char				link_buff[1024];
	int					ret;

	if ((ret = readlink(lst->path, link_buff, 1023)) == -1)
		ft_error(1, lst->name);
	else
	{
		link_buff[ret] = '\0';
		lst->link = link_buff;
	}
	return (0);
}

int		option_l(struct stat b_stat, char *cheat[], t_flist *lst, t_arg *opt)
{
	int					len_tmp;

	lst->owner = ft_strdup(cheat[0]);
	if ((len_tmp = ft_strlen(lst->owner)) > opt->own_len)
		opt->own_len = len_tmp; 
	lst->group = ft_strdup(cheat[1]);
	if ((len_tmp = ft_strlen(lst->group)) > opt->gr_len)
		opt->gr_len = len_tmp; 
	file_rights(lst, b_stat);
	file_size(lst, opt, b_stat);
	lst->link_nb = ft_itoa(b_stat.st_nlink);
	if ((len_tmp = ft_strlen(lst->link_nb)) > opt->lk_len)
		opt->lk_len = len_tmp; 
	if (lst->type == 'l')
		type_l(lst);
	return (0);
}

int		file_info(char *path, t_arg *option, t_flist *lst)
{
	//	printf("fct : isadir\n");
	struct stat			buff_stat;
	struct passwd		*pwd;
	struct group		*grp;
	char				*time_tmp;
	char				*cheat[2];

	lstat(path, &buff_stat);
	lst->type = file_type(buff_stat);
	time_tmp = NULL;
	if (option->l == 1 || option->t == 1)
	{
		time_tmp = ctime(&buff_stat.st_mtime);
		lst->date = ft_strsub(time_tmp, 4, 12);
	}
	if (option->l == 1)
	{
		if ((pwd = getpwuid(buff_stat.st_uid)) == NULL)
			pwd->pw_name = ft_itoa(buff_stat.st_uid);
		if ((grp = getgrgid(buff_stat.st_gid)) == NULL)
			grp->gr_name = ft_itoa(buff_stat.st_gid);
		cheat[0] = pwd->pw_name;
		cheat[1] = grp->gr_name;
		option_l(buff_stat, cheat, lst, option);
	}
	return (S_ISDIR(buff_stat.st_mode));
}

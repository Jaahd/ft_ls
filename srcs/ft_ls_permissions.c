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

int		get_minmaj(struct stat buff_stat, t_arg **opt, t_flist **lst)
{
	char	*maj;
	char	*tmp;
	int		i;

	maj = ft_itoa(major(buff_stat.st_rdev));
	tmp = ft_strjoin(maj, ", ");
	(*lst)->major = ft_strdup(tmp);
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (i = ft_strlen((*lst)->major)) > (*opt)->maj_len)
		(*opt)->maj_len = i;
	(*lst)->minor = ft_itoa(minor(buff_stat.st_rdev));
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (i = ft_strlen((*lst)->minor)) > (*opt)->min_len)
		(*opt)->min_len = i;
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (i = (*opt)->maj_len + (*opt)->min_len + 1) > (*opt)->size_len)
		(*opt)->size_len = i;
	ft_strdel(&maj);
	ft_strdel(&tmp);
	return (0);
}

int		file_size(t_flist **lst, t_arg **option, struct stat buff_stat)
{
	if (((*option)->a == 1 || ((*option)->a == 0 && (*lst)->name[0] != '.'))
			&& ((*lst)->type == 'b' || (*lst)->type == 'c'))
		get_minmaj(buff_stat, option, lst);
	else
	{
		(*lst)->size = ft_itoa(buff_stat.st_size);
		(*lst)->fsize_len = ft_strlen((*lst)->size);
	}
	if (((*option)->a == 1 || ((*option)->a == 0 && (*lst)->name[0] != '.'))
			&& (*lst)->fsize_len > (*option)->size_len)
		(*option)->size_len = (*lst)->fsize_len;
	return (0);
}

char		get_uid(struct stat buff_stat)
{
	char 	ret;
	
	ret = (buff_stat.st_mode & S_IXUSR) ? 'x' : '-';
	if (ret == 'x' && (buff_stat.st_mode & S_ISUID))
		ret = 's';
	else if (ret == '-' && (buff_stat.st_mode & S_ISUID))
		ret = 'S';
	return (ret);
}

char		get_gid(struct stat buff_stat)
{
	char	ret;

	ret = (buff_stat.st_mode & S_IXGRP) ? 'x' : '-';
	if (ret == 'x' && (buff_stat.st_mode & S_ISGID))
		ret = 's';
	else if (ret == '-' && (buff_stat.st_mode & S_ISGID))
		ret = 'S';
	return (ret);
}

char		sticky_bit(struct stat buff_stat)
{
	char	ret;

	ret = (buff_stat.st_mode & S_IXOTH) ? 'x' : '-';
	if (ret == 'x' && (buff_stat.st_mode & S_ISVTX))
		ret = 't';
	else if (ret == '-' && (buff_stat.st_mode & S_ISVTX))
		ret = 'T';
	return (ret);
}

int		file_rights(t_flist **lst, struct stat buff_stat)
{
		(*lst)->rights[0] = (*lst)->type;
		(*lst)->rights[1] = (buff_stat.st_mode & S_IRUSR) ? 'r' : '-';
		(*lst)->rights[2] = (buff_stat.st_mode & S_IWUSR) ? 'w' : '-';
		(*lst)->rights[3] = get_uid(buff_stat); 
		(*lst)->rights[4] = (buff_stat.st_mode & S_IRGRP) ? 'r' : '-'; 
		(*lst)->rights[5] = (buff_stat.st_mode & S_IWGRP) ? 'w' : '-'; 
		(*lst)->rights[6] = get_gid(buff_stat); 
		(*lst)->rights[7] = (buff_stat.st_mode & S_IROTH) ? 'r' : '-';
		(*lst)->rights[8] = (buff_stat.st_mode & S_IWOTH) ? 'w' : '-';
		(*lst)->rights[9] = sticky_bit(buff_stat);
		(*lst)->rights[10] = ' ';
		(*lst)->rights[11] = ' ';
		(*lst)->rights[12] = '\0';
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

int		type_l(t_flist **lst)
{
	char				link_buff[1024];
	int					ret;

	if ((ret = readlink((*lst)->path, link_buff, 1023)) == -1)
		ft_error(1, (*lst)->name);
	else
	{
		link_buff[ret] = '\0';
		(*lst)->link = ft_strdup(link_buff);
	}
	return (0);
}

int		option_l(struct stat b_stat, char *cheat[], t_flist **lst, t_arg **opt)
{
	int					len_tmp;

	(*lst)->owner = ft_strdup(cheat[0]);
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (len_tmp = ft_strlen((*lst)->owner)) > (*opt)->own_len)
		(*opt)->own_len = len_tmp; 
	(*lst)->group = ft_strdup(cheat[1]);
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (len_tmp = ft_strlen((*lst)->group)) > (*opt)->gr_len)
		(*opt)->gr_len = len_tmp; 
	file_size(lst, opt, b_stat);
	(*lst)->link_nb = ft_itoa(b_stat.st_nlink);
	if ((*opt)->a == 1 || ((*opt)->a != 1 && (*lst)->name[0] != '.'))
		(*lst)->block = b_stat.st_blocks;
	(*opt)->tot_blocks += (*lst)->block;
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (len_tmp = ft_strlen((*lst)->link_nb)) > (*opt)->lk_len)
		(*opt)->lk_len = len_tmp; 
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (*lst)->type == 'l')
		type_l(lst);
	return (0);
}

int		get_time(t_flist **lst, struct stat buff_stat)
{
	int					today;
	char				*tmp;
	char				*str;

	str = NULL;
	today = time(NULL);
	tmp = ctime(&buff_stat.st_mtime);	
	(*lst)->epoc = buff_stat.st_mtime;
	(*lst)->date = ft_strsub(tmp, 4, 7);
	(*lst)->year = ((today - (*lst)->epoc) > 15768000 ?
		ft_strjoin(" ", (str = ft_strsub(tmp, 20, 4))) :
		ft_strsub(tmp, 11, 5));
	free(str);
	return (0);
}

int		file_info(char *path, t_arg *option, t_flist **lst)
{
	//	printf("fct : isadir\n");
	struct stat			buff_stat;
	struct passwd		*pwd;
	struct group		*grp;
	char				*cheat[2];

	lstat(path, &buff_stat);
	(*lst)->type = file_type(buff_stat);
	file_rights(lst, buff_stat);
	if (option->l == 1 || option->t == 1)
		get_time(lst, buff_stat);
	if (option->l == 1)
	{
		if ((pwd = getpwuid(buff_stat.st_uid)) == NULL)
			pwd->pw_name = ft_itoa(buff_stat.st_uid);
		if ((grp = getgrgid(buff_stat.st_gid)) == NULL)
			grp->gr_name = ft_itoa(buff_stat.st_gid);
		cheat[0] = pwd->pw_name;
		cheat[1] = grp->gr_name;
		option_l(buff_stat, cheat, lst, &option);
	}
	return (S_ISDIR(buff_stat.st_mode));
}

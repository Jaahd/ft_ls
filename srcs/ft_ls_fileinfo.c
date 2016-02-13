/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_fileinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 17:03:22 by avacher           #+#    #+#             */
/*   Updated: 2016/02/13 17:03:22 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"
#include "libft.h"

static int		get_minmaj(struct stat buff_stat, t_arg **opt, t_flist **lst)
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

static int		file_size(t_flist **lst, t_arg **option, struct stat buff_stat)
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

static int		type_l(t_flist **lst)
{
	char				link_buff[1024];
	int					ret;
	char				*tmp;

	tmp = NULL;
	if ((ret = readlink((*lst)->path, link_buff, 1023)) == -1)
	{
		ft_error(3, (tmp = ft_strjoin("cannot read symbolic link ",
									(*lst)->name)));
		return (-1);
	}
	else
	{
		link_buff[ret] = '\0';
		(*lst)->link = ft_strdup(link_buff);
	}
	free(tmp);
	return (0);
}

static int		option_l(struct stat b_stat, char *cheat[], t_flist **lst,
				t_arg **opt)
{
	int					tmp;

	(*lst)->owner = ft_strdup(cheat[0]);
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (tmp = ft_strlen((*lst)->owner)) > (*opt)->own_len)
		(*opt)->own_len = tmp;
	(*lst)->group = ft_strdup(cheat[1]);
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (tmp = ft_strlen((*lst)->group)) > (*opt)->gr_len)
		(*opt)->gr_len = tmp;
	file_size(lst, opt, b_stat);
	(*lst)->link_nb = ft_itoa(b_stat.st_nlink);
	if ((*opt)->a == 1 || ((*opt)->a != 1 && (*lst)->name[0] != '.'))
		(*lst)->block = b_stat.st_blocks;
	(*opt)->tot_blocks += (*lst)->block;
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (tmp = ft_strlen((*lst)->link_nb)) > (*opt)->lk_len)
		(*opt)->lk_len = tmp;
	if (((*opt)->a == 1 || ((*opt)->a == 0 && (*lst)->name[0] != '.'))
			&& (*lst)->type == 'l')
		if ((tmp = type_l(lst)) == -1)
			return (-1);
	return (0);
}

int				file_info(char *path, char *name, t_arg *option, t_flist **lst)
{
	struct stat			buff_stat;
	struct passwd		*pwd;
	struct group		*grp;
	char				*cheat[2];

	if (lstat(path, &buff_stat) == -1)
	{
		ft_error(3, name);
		return (-1);
	}
	(*lst)->type = file_type(buff_stat);
	file_rights(lst, buff_stat);
	if (option->l == 1 || option->t == 1 || option->g == 1 || option->o == 1)
		get_time(lst, buff_stat);
	if (option->l == 1 || option->o == 1 || option->g == 1)
	{
		getpwgr(&pwd, &grp, buff_stat);
		cheat[0] = pwd->pw_name;
		cheat[1] = grp->gr_name;
		if (option_l(buff_stat, cheat, lst, &option) == -1)
			return (-1);
	}
	return (S_ISDIR(buff_stat.st_mode));
}

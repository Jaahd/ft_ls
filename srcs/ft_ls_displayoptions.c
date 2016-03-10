/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_displayoptions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 17:03:22 by avacher           #+#    #+#             */
/*   Updated: 2016/02/13 17:03:22 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include "libft.h"
#include "ft_ls.h"

static int		format_majmin(t_flist **lst, t_arg **option)
{
	char		len[(*option)->min_len + 1];
	char		*tmp;
	int			size;
	int			i;
	int			j;

	i = -1;
	j = -1;
	len[(*option)->min_len] = '\0';
	size = ((*option)->min_len - ft_strlen((*lst)->minor));
	while (++i < size)
		len[i] = ' ';
	while ((*lst)->minor[++j])
		len[i++] = (*lst)->minor[j];
	if ((tmp = ft_strjoin((*lst)->major, len)) == NULL)
		ft_error(3, (*lst)->major);
	if (((*lst)->size = ft_strdup(tmp)) == NULL)
		ft_error(3, tmp);
	(*lst)->fsize_len = ft_strlen((*lst)->size);
	if (((*option)->a == 1 || ((*option)->a == 0 && (*lst)->name[0] != '.'))
			&& (*lst)->fsize_len > (*option)->size_len)
		(*option)->size_len = (*lst)->fsize_len;
	ft_strdel(&tmp);
	return (0);
}

static int		display_size_date(t_flist **lst, t_arg *opt)
{
	put_space((*lst)->size, opt->size_len);
	ft_putstr((*lst)->size);
	ft_putchar(' ');
	ft_putstr((*lst)->date);
	ft_putstr((*lst)->year);
	ft_putchar(' ');
	return (0);
}

int				long_display(t_flist **lst, t_arg *opt)
{
	ft_putstr((*lst)->rights);
	put_space((*lst)->link_nb, opt->lk_len);
	ft_putstr((*lst)->link_nb);
	ft_putchar(' ');
	if (opt->g == 0)
	{
		ft_putstr((*lst)->owner);
		put_space((*lst)->owner, (opt->own_len + 2));
	}
	if (opt->o == 0)
	{
		ft_putstr((*lst)->group);
		put_space((*lst)->group, (opt->gr_len + 2));
	}
	if (opt->o == 1 && opt->g == 1)
		ft_putstr("  ");
	if ((opt->a == 1 || (opt->a == 0 && (*lst)->name[0] != '.'))
			&& ((*lst)->type == 'b' || (*lst)->type == 'c'))
		format_majmin(lst, &opt);
	display_size_date(lst, opt);
	return (0);
}

int				display_colors(t_flist **lst)
{
	if ((*lst)->rights[0] == 'd')
		ft_putstr("\033[1;34m");
	if ((*lst)->rights[0] == 'l')
		ft_putstr("\033[1;36m");
	if ((*lst)->rights[0] == 'b')
		ft_putstr("\033[1;33m");
	if ((*lst)->rights[0] == 'c')
		ft_putstr("\033[1;31m");
	if ((*lst)->rights[0] == 'p')
		ft_putstr("\033[1;35m");
	if ((*lst)->rights[0] == 's')
		ft_putstr("\033[1;37m");
	if ((*lst)->rights[0] == '-' && ((*lst)->rights[3] == 'x' ||
				(*lst)->rights[6] == 'x' || (*lst)->rights[9] == 'x'))
		ft_putstr("\033[1;32m");
	if ((*lst)->rights[3] == 's' || (*lst)->rights[6] == 's')
		ft_putstr("\033[1;32;46m");
	if ((*lst)->rights[3] == 'S' || (*lst)->rights[6] == 'S')
		ft_putstr("\033[1;46m");
	if ((*lst)->rights[9] == 't')
		ft_putstr("\033[1;32;100m");
	if ((*lst)->rights[9] == 'T')
		ft_putstr("\033[1;100m");
	return (0);
}

int				display_total(t_arg **opt, int i)
{
	if ((((*opt)->a == 1 && i > 2) || i > 0)
			&& ((*opt)->l == 1 || (*opt)->o == 1 || (*opt)->g == 1))
	{
		ft_putstr("total ");
		ft_putnbrendl((*opt)->tot_blocks);
	}
	(*opt)->tot_blocks = 0;
	return (0);
}

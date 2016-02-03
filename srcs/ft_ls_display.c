/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:33:45 by avacher           #+#    #+#             */
/*   Updated: 2016/01/22 17:25:28 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int		display_total(t_arg **option)
{
//	printf("fct : display_total\n");
	if ((*option)->l == 1)
	{
		ft_putstr("total ");
		ft_putnbrendl((*option)->tot_blocks);
	}
	(*option)->tot_blocks = 0;
//	(*option)->lk_len = 0;
	return (0);
}

int		display_dirname(t_arg *option, char *str)
{
//	printf("fct : display_dirname\n");
	if(option->arg_nb >  1 || option->recu == 1)
	{
		ft_putchar('\n');
		ft_putstr(str);
		ft_putendl(":");
	}
	return (0);
}

int		second_display(t_arg *option, t_flist *tmp)
{
//	printf("fct : second_display\n");
	if (option->a == 1  && tmp->type == 'd')
	{
		if (option->arg_nb > 1)
			display_dirname(option, tmp->name);
		open_dir(option, tmp->path);
	}
	else if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
			&& option->a != 1 && ft_strcmp(tmp->name, ".."))
	{
		if (option->arg_nb > 1)
			display_dirname(option, tmp->name);
		open_dir(option, tmp->path);
	}
	return (0);
}

int		first_display(t_flist **lst, t_arg *option)
{
//	printf("fct : first_display\n");
	t_flist		*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->type != 'd')	
			ls_display(option, &tmp);
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp != NULL)
	{
		second_display(option, tmp);
		tmp = tmp->next;
	}
//	free_s_flist(lst);
	return (0);
}

int		put_space(char *str, int len)
{
//	printf("fct : put_space\n");
	int			i;

	i = ft_strlen(str);
	while(i < len)
	{
		ft_putchar(' ');
		i++;
	}
	return (0);
}

int		format_majmin(t_flist **lst, t_arg **option)
{
//	printf("fct : format_majmin\n");
	char		len[(*option)->min_len + 1];
	char		*tmp;
	int			size;
	int			i;
	int			j;

	i = -1;
	j = -1;
	len[(*option)->min_len] = '\0';
	size = ((*option)->min_len - ft_strlen((*lst)->minor));
	while(++i < size)
		len[i] = ' ';
	while((*lst)->minor[++j])
	{
		len[i] = (*lst)->minor[j];
		i++;
	}
	//	printf("minor : %s\tlen : |%s|\tmin_len : %d\t size : %d\n", (*lst)->minor, len, (*option)->min_len, size);
	tmp = ft_strjoin((*lst)->major, len);
	(*lst)->size = ft_strdup(tmp);
	(*lst)->fsize_len = ft_strlen((*lst)->size);
	if (((*option)->a == 1 || ((*option)->a == 0 && (*lst)->name[0] != '.'))
			&& (*lst)->fsize_len > (*option)->size_len)
		(*option)->size_len = (*lst)->fsize_len;
	//	ft_strdel(&tmp);
	return (0);
}

int		long_display(t_flist **lst, t_arg *option)
{
//		printf("fct : long_display : option->link_len : %d\n", option->lk_len);
	ft_putstr((*lst)->rights);
	put_space((*lst)->link_nb, option->lk_len);
	ft_putstr((*lst)->link_nb);
	ft_putchar(' ');
	ft_putstr((*lst)->owner);
	put_space((*lst)->owner, (option->own_len + 2));
	ft_putstr((*lst)->group);
	put_space((*lst)->group, (option->gr_len + 2));
	if ((option->a == 1 || (option->a == 0 && (*lst)->name[0] != '.'))
			&& ((*lst)->type == 'b' || (*lst)->type == 'c'))
		format_majmin(lst, &option);
	put_space((*lst)->size, option->size_len);
	ft_putstr((*lst)->size);
	ft_putchar(' ');
	ft_putstr((*lst)->date);
	ft_putstr((*lst)->year);
	ft_putchar(' ');
	return (0);
}

int		display_colors(t_flist **lst)
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
		ft_putstr("\033[1;32;100m");
	if ((*lst)->rights[3] == 'S' || (*lst)->rights[6] == 'S')
		ft_putstr("\033[1;100m");
	if ((*lst)->rights[9] == 't')
		ft_putstr("\033[1;32;46m");
	if ((*lst)->rights[9] == 'T')
		ft_putstr("\033[1;46m");
	return (0);
}

int		ls_display(t_arg *option, t_flist **lst)
{
//		printf("fct : ls_display\n");
	if (option->l == 1)
		long_display(lst, option);
	if (option->colors == 1)
		display_colors(lst);
	ft_putstr((*lst)->name);
	if (option->colors)
		ft_putstr("\033[0m");
	if (option->l == 1 && (*lst)->type == 'l')
	{
		ft_putstr(" -> ");
		ft_putstr((*lst)->link);
	}
	ft_putendl("");
	return (0);
}

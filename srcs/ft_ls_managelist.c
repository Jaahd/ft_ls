/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:27:11 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 17:32:45 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		dirlst_pushb(t_dlist **dirlist, t_dlist *new)
{
	t_dlist		*tmp;

	tmp = *dirlist;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

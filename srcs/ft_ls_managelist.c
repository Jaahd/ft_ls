/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_managelist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 17:27:11 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 18:47:29 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_ls.h"

int		dirlst_pushb(t_dlist **dirlist, char *dname)
{
	t_dlist		*tmp;
	t_dlist		*new;

	tmp = *dirlist;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if ((new = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		ft_error(1, dname);
	new->next = NULL;
	if ((new->dname = ft_strdup(dname)) == NULL)
		ft_error(1, dname);
	if (tmp)
		tmp->next = new;
	else
		tmp = new;
	return (0);
}

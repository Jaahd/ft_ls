/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:07:32 by avacher           #+#    #+#             */
/*   Updated: 2016/01/20 13:34:37 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft.h"

int		isadir(char *path)
{
//	printf("fct : isadir\n");
	struct stat			buff_stat;

	lstat(path, &buff_stat);
	return (S_ISDIR(buff_stat.st_mode));
}

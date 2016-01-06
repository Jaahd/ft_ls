#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/errno.h>
#include "libft.h"

int				main (int ac, char **av) 
{
	struct dirent	*pDirent;
	DIR				*pDir;

	if (ac < 2) 
		av[1] = ".";
	pDir = opendir (av[1]);
	if (pDir == NULL)
	{
		perror(av[1]);
		return 1;
	}
	while ((pDirent = readdir(pDir)) != NULL) 
	{
		ft_putendl(pDirent->d_name);
	}
	closedir (pDir);
	return 0;
}

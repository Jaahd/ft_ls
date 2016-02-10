#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "libft.h"
#include "ft_ls.h"

int				get_time(t_flist **lst, struct stat buff_stat)
{
	if (DEBUG == 1)
		printf("fct : get_time\n");
	int				today;
	char			*tmp;
	char			*str;

	str = NULL;
	today = time(NULL);
	tmp = ctime(&buff_stat.st_mtime);
	(*lst)->epoc = buff_stat.st_mtime;
	if (((*lst)->date = ft_strsub(tmp, 4, 7)) == NULL)
		ft_error(3, tmp);
	if (((*lst)->year = ((today - (*lst)->epoc) > 15768000 ?
			ft_strjoin(" ", (str = ft_strsub(tmp, 20, 4))) :
			ft_strsub(tmp, 11, 5))) == NULL)
		ft_error(3, tmp);
//		free(str);
	return (0);
}

static int		first_link(char *str, t_arg *option, t_flist **new)
{
	if (DEBUG == 1)
		printf("fct : first_link\n");
	char			*tmp;
	char			*t2;

	tmp = NULL;
	t2 = NULL;
	if (str[0] == '/')
	{
		if ((*new = lst_new(str, str, &option)) == NULL)
			return (-1);
	}
	else
	{
		if ((t2 = ft_strdup(str)) == NULL)
			ft_error(3, str);
		tmp = format_path("./", t2, ft_strlen(str));
		if ((*new = lst_new(str, tmp, &option)) == NULL)
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

int				get_name(t_arg *option, t_flist **lst, int ac_c, char **av)
{
	if (DEBUG == 1)
		printf("fct : get_name\n");
	t_flist			*new;
	int				cpt;

	cpt = 1;
	if (ac_c == 0)
		recu_dir(option, "./", ".");
	while (av[cpt] && av[cpt][0] == '-')
		cpt++;
	while (av[cpt])
	{
		if((first_link(av[cpt], option, &new)) == -1)
		{
			cpt++;
			break;
		}
		if (*lst == NULL && new)
			*lst = new;
		else if (option->t == 1 && new)
			lst_time_insert(option, lst, new);
		else if (new)
			lst_insert(option, lst, new);
		cpt++;
	}
	//	free(t2);
	return (0);
}

char			*format_path(char *b_path, char *filename, int namelen)
{
	if (DEBUG == 1)
		printf("fct : format_path\n");
	char			*tmp;
	char			*f_path;
	int				p_len;

	tmp = NULL;
	p_len = ft_strlen(b_path);
	if (filename[namelen - 1] == '/')
		filename[namelen - 1] = '\0';
	if (p_len > 0 && b_path[p_len - 1] != '/')
	{
		if ((tmp = ft_properjoin(b_path, "/")) == NULL)
			ft_error(1, b_path);
	}
	else if (p_len > 0)
	{
		if ((tmp = ft_strdup(b_path)) == NULL)
			ft_error(1, b_path);
	}
	if (((f_path = ft_properjoin(tmp, filename)) == NULL))
		ft_error(1, filename);
	free(tmp);
	return (f_path);
}

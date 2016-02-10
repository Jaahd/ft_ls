#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "ft_ls.h"
#include "libft.h"

static int		first_display_dir(t_flist **lst2, t_arg *option)
{
	if (DEBUG == 1)
		printf("fct : first_display_dir\n");
	t_flist				*tmp;

	tmp = *lst2;
	display_total(&option);
	while (tmp)
	{
		if (option->a == 1 || (option->a == 0 && tmp->name[0] != '.'))
			ls_display(option, &tmp);
		tmp = tmp->next;
	}
	return (0);
}

static int		fill_list(DIR *p_dir, t_flist **lst2, t_arg *option, char *path)
{
	if (DEBUG == 1)
		printf("fct : fill_list\n");
	struct dirent		*p_dirent;
	t_flist				*new;
	char				*str;

	while ((p_dirent = readdir(p_dir)) != NULL)
	{
		str = format_path(path, p_dirent->d_name, ft_strlen(p_dirent->d_name));
		if ((new = lst_new(p_dirent->d_name, str, &option)) == NULL)
			return (-1);
		free(str);
		if (*lst2 == NULL)
			*lst2 = new;
		else if (option->t == 1)
			lst_time_insert(option, lst2, new);
		else
			lst_insert(option, lst2, new);
	}
	first_display_dir(lst2, option);
	return (0);
}

static int		open_dir(t_flist **lst2, t_arg *option, char *dpath, char *name)
{
	if (DEBUG == 1)
		printf("fct : open_dir\n");
	DIR					*p_dir;

	if ((p_dir = opendir(dpath)) == NULL)
		return (ft_error(3, name));
	if ((fill_list(p_dir, lst2, option, dpath)) == -1)
		return (-1);
	closedir(p_dir);
	return (0);
}

int				recu_dir(t_arg *option, char *dpath, char *name)
{
	if (DEBUG == 1)
		printf("fct : recu_dir\n");
	t_flist				*lst2;
	t_flist				*tmp;
	char				*str;

	lst2 = NULL;
	if ((open_dir(&lst2, option, dpath, name)) == -1)
		return (-1);
	tmp = lst2;
	while (option->recu == 1 && tmp)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
				&& ft_strcmp(tmp->name, "..") && (option->a == 1
					|| (option->a != 1 && tmp->name[0] != '.')))
		{
			display_dirname(option, tmp->path);
			option->lk_len = 0;
			option->size_len = 0;
			recu_dir(option, (str = format_path(dpath, tmp->name,
							ft_strlen(tmp->name))), tmp->name);
			free(str);
		}
		option->size_len = 0;
		tmp = tmp->next;
	}
	//	//	free_s_flist(&lst2); ////	free a revoir
	return (1);
}

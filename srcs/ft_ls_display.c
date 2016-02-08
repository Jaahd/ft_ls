//#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int				display_dirname(t_arg *option, char *str)
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

static int		second_display(t_arg *option, t_flist *tmp)
{
	//	printf("fct : second_display\n");
	if (option->a == 1  && tmp->type == 'd')
	{
		if (option->arg_nb > 1)
			display_dirname(option, tmp->name);
		recu_dir(option, tmp->path, tmp->name);
	}
	else if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
			&& option->a != 1 && ft_strcmp(tmp->name, ".."))
	{
		if (option->arg_nb > 1)
			display_dirname(option, tmp->name);
		recu_dir(option, tmp->path, tmp->name);
	}
	return (0);
}

int				first_display(t_flist **lst, t_arg *option)
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

int				put_space(char *str, int len)
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

int				ls_display(t_arg *option, t_flist **lst)
{
	//		printf("fct : ls_display\n");
	if (option->l == 1 || option->o == 1 || option->g == 1)
		long_display(lst, option);
	if (option->colors == 1)
		display_colors(lst);
	ft_putstr((*lst)->name);
	if (option->p && (*lst)->type == 'd')
		ft_putchar('/');
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

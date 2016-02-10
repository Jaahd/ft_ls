#include <string.h>
#include <pwd.h>
#include <grp.h>
#include "libft.h"
#include "ft_ls.h"

int				init_options(t_arg *option)
{
	if (DEBUG == 1)
		printf("fct : init_options\n");
	option->recu = 0;
	option->a = 0;
	option->g = 0;
	option->l = 0;
	option->o = 0;
	option->p = 0;
	option->r = 0;
	option->t = 0;
	option->colors = 0;
	option->arg_nb = 0;
	option->own_len = 0;
	option->gr_len = 0;
	option->lk_len = 0;
	option->maj_len = 0;
	option->min_len = 0;
	option->size_len = 0;
	option->tot_blocks = 0;
	return (0);
}

static int		fill_options(char to_check, t_arg *opt)
{
	if (DEBUG == 1)
		printf("fct : fill_options\n");
	opt->a = (to_check == 'a') ? 1 : opt->a;
	opt->g = (to_check == 'g') ? 1 : opt->g;
	opt->l = (to_check == 'l') ? 1 : opt->l;
	opt->o = (to_check == 'o') ? 1 : opt->o;
	opt->p = (to_check == 'p') ? 1 : opt->p;
	opt->r = (to_check == 'r') ? 1 : opt->r;
	opt->t = (to_check == 't') ? 1 : opt->t;
	opt->recu = (to_check == 'R') ? 1 : opt->recu;
	opt->colors = (to_check == 'G') ? 1 : opt->colors;
	return (0);
}

int				get_options(t_arg *opt, int *ac_c, char **av)
{
	if (DEBUG == 1)
		printf("fct : get_options\n");
	int				i;
	int				cpt;

	cpt = 0;
	while (++cpt < *ac_c)
	{
		i = 1;
		while (av[cpt][0] == '-' && av[cpt][i])
		{
			if (av[cpt][i] != 'R' && av[cpt][i] != 'a' && av[cpt][i] != 'l' &&
				av[cpt][i] != 'r' && av[cpt][i] != 't' && av[cpt][i] != 'G' &&
				av[cpt][i] != 'g' && av[cpt][i] != 'o' && av[cpt][i] != 'p')
				ft_error(2, &av[cpt][i]);
			fill_options(av[cpt][i], opt);
			i++;
		}
		if (av[cpt][0] != '-')
			break ;
	}
	*ac_c -= cpt;
	return (0);
}

int				getpwgr(struct passwd **pwd, struct group **grp, struct stat bs)
{
	if (DEBUG == 1)
		printf("fct : getpwgr\n");
	if ((*pwd = getpwuid(bs.st_uid)) == NULL)
	{
		if ((*pwd = (struct passwd *)malloc(sizeof(struct passwd))) == NULL)
			ft_error(1, "ower info");
		(*pwd)->pw_name = ft_itoa(bs.st_uid);
	}
	if ((*grp = getgrgid(bs.st_gid)) == NULL)
	{
		if ((*grp = (struct group *)malloc(sizeof(struct group))) == NULL)
			ft_error(1, "group info");
		(*grp)->gr_name = ft_itoa(bs.st_gid);
	}
	return (0);
}

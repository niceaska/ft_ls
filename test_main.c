#include "ft_ls.h"

int main(int ac, char **ag)
{
	t_env *e;

	e = init_env();
	ag = ft_parser(&e, ag, ac);
	printf("terminal - %d\n", e->w_width);
	printf("%d\n", e->flags);
//	printf("ac = %d ag_cnt = %d", ac, e->ag_cnt);
	process_args(&e, ag, ac - e->ag_cnt);
	free(e);
}
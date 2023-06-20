
#include "minishell.h"

void	naked_export(char **envp)
{
	int		i;
	char	**sorted_envp;
	char	*tmp;

	i = 0;
	sorted_envp = (char **)ft_array_dup((void **)envp, false, true);
	if (!sorted_envp)
		exit(EXIT_FAILURE); //TODO: call exit function
	i = -1;
	ft_sort_array(sorted_envp);
	while (sorted_envp[++i])
	{
		tmp = ft_strchr(sorted_envp[i], '=');
		if (!tmp)
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", sorted_envp[i]);
		else
		{
			*tmp = '\0';
			ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", sorted_envp[i], tmp + 1);
			*tmp = '=';
		}
	}
	ft_free_array((void **)sorted_envp);
}

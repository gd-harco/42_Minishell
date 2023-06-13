# include "minishell.h"

char	**minishell_env_dup(char **envp)
{
	size_t	envp_len;

	envp_len = ft_array_length((void**)envp);

}

char	*get_env(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

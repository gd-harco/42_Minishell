
#include "minishell.h"

bool	unvalid_identifier(char *key);

void	unset(char **argv, t_exec *exec_data)
{
	size_t	i;
	size_t	line_index;

	i = 0;
	while (argv[++i])
	{
		if (unvalid_identifier(argv[i]))
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n", argv[i]);
			continue ;
		}
		else
		{
			line_index = 0;
			while (exec_data->envp[line_index])
			{
				if (ft_strncmp(exec_data->envp[line_index], argv[i], ft_strlen(argv[i])) == 0)
				{
					ft_remove_array_line(
						(void **)exec_data->envp, line_index, true);
					break ;
				}
				line_index++;
			}
		}
	}
}

bool	unvalid_identifier(char *key)
{
	size_t	i;

	i = -1;
	while (key[++i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			continue ;
		else
			return (true);
	}
	return (false);
}

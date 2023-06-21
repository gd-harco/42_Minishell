/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:55:32 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:03:16 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_env(char *str, t_exec *exec_data);
static bool	only_key_already_in_env(char *str, t_exec *exec_data);
void		naked_export(char **envp);

void	export(t_exec *exec_data)
{
	int	i;

	i = 0;
	if (!exec_data->cmd->argv[1])
		naked_export(exec_data->envp);
	while (exec_data->cmd->argv[++i])
	{
		if (already_in_env(exec_data->cmd->argv[i], exec_data))
			continue ;
		else
			exec_data->envp = add_env(exec_data->cmd->argv[i], exec_data);

	}
}

bool	check_for_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static char	**add_env(char *str, t_exec *exec_data)
{
	size_t	old_len;
	char	**new_envp;

	old_len = ft_array_length((void **)exec_data->envp);
	new_envp = ft_calloc(old_len + 2, sizeof(char *));
	if (!new_envp)
		exit(EXIT_FAILURE); //TODO: call exit function
	ft_memmove(new_envp, exec_data->envp, old_len * sizeof(char *));
	new_envp[old_len] = ft_strdup(str);
	free(exec_data->envp);
	return (new_envp);
}

bool	already_in_env(char *str, t_exec *exec_data)
{
	int		i;
	int		len_until_equal;
	bool	have_equal;

	have_equal = check_for_equal(str);
	if (!have_equal)
		return (only_key_already_in_env(str, exec_data));
	i = 0;
	len_until_equal = 0;
	while (str[len_until_equal] && str[len_until_equal] != '=')
		len_until_equal++;
	while (exec_data->envp[i])
	{
		if (ft_strncmp(str, exec_data->envp[i], len_until_equal) == 0)
		{
			free(exec_data->envp[i]);
			exec_data->envp[i] = ft_strdup(str);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	only_key_already_in_env(char *str, t_exec *exec_data)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(str);
	i = -1;
	while (exec_data->envp[++i])
	{
		if (ft_strncmp(str, exec_data->envp[i], key_len) == 0)
			return (true);
	}
	return (false);
}

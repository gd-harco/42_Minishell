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

char	**add_env(char *str, char **envp);

void export(t_exec *exec_data)
{
	int	i;

	i = 1;
	while (exec_data->cmd->argv[i])
	{
		// if (already_in_env(argv[i], envp))
		//	replace_env(argv[i], envp);
		//else
		exec_data->envp = add_env(exec_data->cmd->argv[i], exec_data->envp);
		i++;
	}
}

char	**add_env(char *str, char **envp)
{
	size_t	old_len;
	char	**new_envp;

	old_len = ft_array_length((void **)envp);
	new_envp = ft_calloc(old_len + 2, sizeof(char *));
	if (!new_envp)
		exit(EXIT_FAILURE); //TODO: call exit function
	ft_memmove(new_envp, envp, old_len * sizeof(char *));
	new_envp[old_len] = ft_strdup(str);
	free(envp);
	return (new_envp);
}

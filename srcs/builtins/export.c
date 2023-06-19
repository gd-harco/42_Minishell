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
bool	already_in_env(char *str, char **envp);
bool	check_for_equal(const char *str);
bool	only_key_already_in_env(char *str, char **envp);


//TODO export tout seul doit imprimer tes lignes dans l'ordres ascii. (les gens ne le check pas mais fait le)
void export(t_exec *exec_data)
{
	int	i;

	i = 0;
	while (exec_data->cmd->argv[++i])
	{
		if (already_in_env(exec_data->cmd->argv[i], exec_data->envp))
			continue ;
		else
			exec_data->envp = add_env(exec_data->cmd->argv[i], exec_data->envp);

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
//TODO si allready in env tu dois quand meme verifier que la key a une valeur. export a tout seul n'enleve pas la value d'un ancien export
bool	already_in_env(char *str, char **envp)
{
	int		i;
	int		len_until_equal;
	bool	have_equal;

	have_equal = check_for_equal(str);
	if (!have_equal)
		return (only_key_already_in_env(str, envp));
	i = 0;
	len_until_equal = 0;
	while (str[len_until_equal] && str[len_until_equal] != '=')
		len_until_equal++;
	while (envp[i])
	{
		if (ft_strncmp(str, envp[i], len_until_equal) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (true);
		}
		i++;
	}
	return (false);
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

bool	only_key_already_in_env(char *str, char **envp)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(str);
	i = 0;
	while (envp[i++])
	{
		if (ft_strncmp(str, envp[i], key_len) == 0)
			return (true);
	}
	return (false);
}

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

static char	**add_env(char *str, char **envp);
static bool	already_in_env(char *str, char **envp);
static bool	only_key_already_in_env(char *str, char **envp);
static void	naked_export(char **envp);


//TODO export tout seul doit imprimer tes lignes dans l'ordres ascii. (les gens ne le check pas mais fait le)
void export(t_exec *exec_data)
{
	int	i;

	i = 0;
	if (!exec_data->cmd->argv[1])
		naked_export(exec_data->envp);
	while (exec_data->cmd->argv[++i])
	{
		if (already_in_env(exec_data->cmd->argv[i], exec_data->envp))
			continue ;
		else
			exec_data->envp = add_env(exec_data->cmd->argv[i], exec_data->envp);

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

static char	**add_env(char *str, char **envp)
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

static bool	already_in_env(char *str, char **envp)
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

static bool	only_key_already_in_env(char *str, char **envp)
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

//todo sort in ascii order before printing. Add double quotes around values
void	naked_export(char **envp)
{
int		i;
	int		j;
	char	**sorted_envp;

	i = 0;
	j = 0;
	sorted_envp = ft_calloc(ft_array_length((void **)envp) + 1, sizeof(char *));
	if (!sorted_envp)
		exit(EXIT_FAILURE); //TODO: call exit function
	while (envp[i])
		sorted_envp[j++] = ft_strdup(envp[i++]);
	i = 0;
	while (sorted_envp[i])
		ft_dprintf(STDOUT_FILENO, "declare -x %s\n", sorted_envp[i++]);
	ft_free_array((void **)sorted_envp);
}

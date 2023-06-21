/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:30:50 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_exec *exec_data);
static char	*get_env(char *str, char **envp);
//TODO : handle cd - (go back to previous directory)
//TODO : When cd success, update PWD and OLDPWD in env

void	cd(char **argv, t_exec *exec_data)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = get_env("HOME", exec_data->envp);
		if (path == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			return ;
		}
		if (chdir(&path[5]) == -1)
			return (ft_dprintf(
				STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno)), (void)0);
		return (update_env(exec_data), (void)0);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (ft_dprintf(
				STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno)), (void)0);
	return (update_env(exec_data), (void)0);
}

static char	*get_env(char *str, char **envp)
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

static void	update_env(t_exec *exec_data)
{
	char	*tmp;
	char	*n_old_pwd;
	char	*n_pwd;

	tmp = get_env("PWD", exec_data->envp);
	n_old_pwd = ft_strjoin("OLDPWD=", tmp + 4);
	n_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	already_in_env(n_old_pwd, exec_data);
	already_in_env(n_pwd, exec_data);
}

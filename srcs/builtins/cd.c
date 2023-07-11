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

static void	update_env(t_exec *exec_data, char *old_pwd);
static char	*get_env(char *str, char **envp);

//TODO : handle cd - (go back to previous directory)

void	cd(char **argv, t_exec *exec_data)
{
	char	*path;
	char	*pwd_before;

	if (argv[1] && argv[2])
		return (g_return_value = 1, ft_dprintf(STDERR_FILENO,
				"minishell: cd: too many arguments\n"), (void)0);
	pwd_before = ft_strdup(getcwd(NULL, 0));
	if (argv[1] == NULL)
	{
		path = get_env("HOME", exec_data->envp);
		if (path == NULL)
			return (ft_dprintf(STDERR_FILENO,
					"cd: HOME not set\n"), g_return_value = 1, (void)0);
		if (chdir(&path[5]) == -1)
			return (g_return_value = 1, ft_dprintf(STDERR_FILENO, "cd: %s: %s\n",
					path, strerror(errno)), (void)0);
		return (g_return_value = 0, update_env(exec_data, pwd_before), (void)0);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (g_return_value = 1, ft_dprintf(
				STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno)), (void)0);
	return (g_return_value = 0, update_env(exec_data, pwd_before), (void)0);
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

static void	update_env(t_exec *exec_data, char *old_pwd)
{
	char	*n_old_pwd;
	char	*n_pwd;

	n_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	n_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!already_in_env(n_old_pwd, exec_data))
		exec_data->envp = add_env(n_old_pwd, exec_data);
	if (!already_in_env(n_pwd, exec_data))
		exec_data->envp = add_env(n_pwd, exec_data);
}

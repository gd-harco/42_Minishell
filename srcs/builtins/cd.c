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

static char	*get_env(char *str, char **envp);

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
			ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
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

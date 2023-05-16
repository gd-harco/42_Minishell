/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:19:20 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/16 14:41:13 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	**split_path;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split_path = ft_split(path, ':');
	free(path);
	return (split_path);
}

char	**path_arg_cat(char **src, char *root_arg)
{
	int		i;
	char	**pathsrc;

	pathsrc = malloc(sizeof(char *) * (5 + 3));
	if (!pathsrc)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		pathsrc[i] = ft_strjoin(src[i], root_arg);
		i++;
	}
	pathsrc[i] = NULL;
	return (pathsrc);
}

char	*process(char *str, char **path, int *ind)
{
	char	**path_cmb;
	int		i;
	char	**split_argv;
	char	*root_arg;

	split_argv = ft_split(str, ' ');
	root_arg = ft_strjoin("/", split_argv[*ind]);
	path_cmb = path_arg_cat(path, root_arg);
	i = 0;
	while (access(path_cmb[i], X_OK) == -1 && path_cmb[i])
		i++;
	if (!path_cmb[i])
	{
		return (split_argv[*ind]);
	}
	free(split_argv[0]);
	split_argv[0] = path_cmb[i];
	free(root_arg);
	free(path_cmb);
	return (split_argv[0]);
}

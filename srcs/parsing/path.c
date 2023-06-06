/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:19:20 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/05 16:40:18 by tdutel           ###   ########.fr       */
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

	pathsrc = malloc(sizeof(char *) * (ft_array_length((void **)src) + 1));
	if (!pathsrc)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	i = 0;
	while (src[i])
	{
		pathsrc[i] = ft_freestrjoin(src[i], root_arg);
		i++;
	}
	pathsrc[i] = NULL;
	return (pathsrc);
}

char	*process(char *str, char **path, int ind)
{
	char	**path_cmb;
	int		i;
	char	**split_argv;
	char	*root_arg;

	split_argv = ft_split(str, ' ');
	root_arg = ft_strjoin("/", split_argv[ind]);
	path_cmb = path_arg_cat(path, root_arg);
	i = 0;
	while (path_cmb[i] && access(path_cmb[i], X_OK) == -1)
		i++;
	if (!path_cmb[i])
	{
		return (split_argv[ind]);
	}
	free(root_arg);
	ft_free_split(split_argv);
	// ft_free_array((void *)path_cmb);
	return (path_cmb[i]);
}

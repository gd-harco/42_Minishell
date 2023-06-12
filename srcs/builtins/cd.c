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

void	cd(char **argv, t_exec *exec_data)
{
	char	*path;

	if (argv[1] == NULL)
	{
		(void)exec_data;
		//TODO get HOME from env
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
}

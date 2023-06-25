/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:05 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/24 15:32:15 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_exec	*exec_data)
{
	pid_t	pid;

	rl_clear_history();
	if (exec_data->secret_array)
	{
		pid = fork();
		if (pid == 0)
			execve(exec_data->secret_array[0],
				exec_data->secret_array, exec_data->envp);
		ft_free_array((void **)exec_data->secret_array);
	}
	ft_dprintf(STDOUT_FILENO,
		"La Team Rocket s'envole vers d'autres cieux!\n");
	ft_free_array((void **)exec_data->envp);
	free_exec(exec_data);
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit(EXIT_SUCCESS);
}

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

static int	get_return_value(char **argv);

void	exit_shell(t_exec	*exec_data)
{
	pid_t	pid;
	int		return_value;

	clear_history();
	if (exec_data->secret_array)
	{
		pid = fork();
		if (pid == 0)
			execve(exec_data->secret_array[0],
				exec_data->secret_array, exec_data->envp);
		ft_free_array((void **)exec_data->secret_array);
	}
	return_value = get_return_value(exec_data->cmd->argv);
	ft_dprintf(STDOUT_FILENO,
		"La Team Rocket s'envole vers d'autres cieux!\n");
	ft_free_array((void **)exec_data->envp);
	free_exec(exec_data);
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (return_value == 2)
		ft_dprintf(STDERR_FILENO,
			"Minishell: exit: required numerical argument\n");
	if (return_value == 1)
		ft_dprintf(STDERR_FILENO,
			"Minishell: exit: too many argument\n");
	exit(return_value);
}

int	get_return_value(char **argv)
{
	int	i;

	if (!argv[1])
		return (g_return_value);
	else if (argv[1] && argv[2])
		return (1);
	else
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (2);
			i++;
		}
		return (ft_atoi(argv[1]));
	}
}

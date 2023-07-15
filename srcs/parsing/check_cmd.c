/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:59:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 13:41:09 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_str(char *str, const char *s1);
static bool	lst_cmd(t_cmd *cmd, int i, int nb_cmd);

bool	catls_check(t_exec *exec_data, int i, size_t nb_cmd)
{
	char	*tmp;
	pid_t	ls_pid;

	while (i < (int)nb_cmd
		&& is_str(exec_data->cmd[i].argv[0], "/usr/bin/cat") == false)
		i++;
	if (is_str(exec_data->cmd[i].argv[0], "/usr/bin/cat") == true
		&& lst_cmd(&exec_data->cmd[i], i, (int)nb_cmd) == true)
	{
		ls_pid = fork();
		if (ls_pid == 0)
			execve(exec_data->cmd[nb_cmd - 1].argv[0],
				exec_data->cmd[nb_cmd - 1].argv, exec_data->envp);
		waitpid(ls_pid, NULL, 0);
		while (is_str(exec_data->cmd[i].argv[0], "/usr/bin/cat") == true)
		{
			tmp = readline("");
			ft_printf("\n");
			rl_on_new_line();
			i++;
			ft_free_secure(&tmp);
		}
		return (true);
	}
	return (false);
}

static bool	lst_cmd(t_cmd *cmd, int i, int nb_cmd)
{
	while (i < nb_cmd - 1)
		i++;
	if (is_str(cmd[i].argv[0], "/usr/bin/ls") == true)
		return (true);
	return (false);
}

static bool	is_str(char *str, const char *s1)
{
	int	i;

	i = 0;
	while (str[i] && s1[i])
	{
		if (str[i] != s1[i])
			return (false);
		i++;
	}
	return (true);
}

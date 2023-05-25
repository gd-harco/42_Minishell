/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/25 15:09:07 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_loop(t_exec *exec);
// static void	open_io_file(t_cmd *cmd);

void	master_exec(t_minishell *minishell_data)
{
	t_exec	*exec;
	size_t	cur_cmd_nb;

	exec = malloc(sizeof(t_exec));
	exec->envp = minishell_data->envp;
	exec->token_list = minishell_data->token_list;
	exec->nb_cmd = get_nb_cmd(exec->token_list);
	if (exec->nb_cmd == 0)
		return ;
	exec->nb_here_doc = get_nb_here_doc(exec->token_list);
	if (exec->nb_here_doc != 0)
		process_here_doc(exec);
	else
		exec->here_doc = NULL;
	exec->cmd = ft_calloc(exec->nb_cmd, sizeof(t_cmd));
	//TODO : call funciton pointer exit
	if (exec->cmd == NULL)
		exit(EXIT_FAILURE);
	cur_cmd_nb = 0;
	while (cur_cmd_nb < exec->nb_cmd)
		translate_token_in_cmd(exec, cur_cmd_nb++);
	exec_loop(exec);
}

void	exec_loop(t_exec *exec)
{
	size_t	cur_cmd_nb;

	cur_cmd_nb = 0;
	while (cur_cmd_nb < exec->nb_cmd)
	{
		// open_io_file(&exec->cmd[cur_cmd_nb]);
		exec->cmd[cur_cmd_nb].pid = fork();
		if (exec->cmd[cur_cmd_nb].pid == 0)
			execve(exec->cmd[cur_cmd_nb].path, exec->cmd[cur_cmd_nb].cmd, exec->envp);
		else
			wait(&exec->cmd[cur_cmd_nb].pid);
		cur_cmd_nb++;
	}
}

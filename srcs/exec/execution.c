/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/26 14:38:56 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_loop(t_exec *exec);
static void	open_io_file(t_cmd *cmd);
static void	exec_cmd(t_cmd *cmd, char **envp);

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
	int		old_stdin;
	int		old_stdout;

	cur_cmd_nb = 0;
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	while (cur_cmd_nb < exec->nb_cmd)
	{
		exec_cmd(&exec->cmd[cur_cmd_nb], exec->envp);
		cur_cmd_nb++;
	}
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
}

void	open_io_file(t_cmd	*cmd)
{
	if (cmd->in_type == INFILE)
		cmd->file_fd[0] = open(cmd->in_file, O_RDONLY);
	else if (cmd->in_type == HERE_DOC_I)
		ft_dprintf(STDOUT_FILENO, "todo here_doc");
		//TODO: handled here_doc;
	else
		cmd->file_fd[0] = STDIN_FILENO;
	if (cmd->out_type == OUTFILE)
		cmd->file_fd[1]
			= open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->out_type == OUTFILE_APPEND)
		cmd->file_fd[1]
			= open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	//TODO: call function pointer exit
	else
		cmd->file_fd[1] = STDOUT_FILENO;
	if (cmd->file_fd[0] == -1 || cmd->file_fd[1] == -1)
		exit(EXIT_FAILURE);
}

void	exec_cmd(t_cmd *cmd, char **envp, t_exec *exec)
{
	open_io_file(cmd);
	dup2(cmd->file_fd[0], STDIN_FILENO);
	dup2(cmd->file_fd[1], STDOUT_FILENO);
	pipe(exec->pipe_fd);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		execve(cmd->path, cmd->cmd, envp);
	}
	else
	{
		wait(&cmd->pid);
	}
}

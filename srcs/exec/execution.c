/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:53:45 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/06 14:26:34 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec		*get_exec_data(t_minishell *minishell);
static size_t		get_nb_cmd(t_token *token_list);
static void			exec_last_cmd(t_exec *exec_data, size_t current_cmd);

void	master_exec(t_minishell	*minishell)
{
	t_exec	*exec_data;
	size_t	current_cmd;

	exec_data = get_exec_data(minishell);
	if (exec_data->nb_cmd == 1 && exec_data->cmd[0].builtin)
		exec_builtin(exec_data, 0);
	else
	{
		current_cmd = 0;
		while (current_cmd < exec_data->nb_cmd - 1)
		{
			dprintf(STDERR_FILENO, "current_cmd: %zu\n", current_cmd);
			pipe(exec_data->pipe_fd);
			exec_data->pid[current_cmd] = fork();
			if (exec_data->pid[current_cmd] == -1)
				exit(EXIT_FAILURE); //TODO: Call exit function
			if (exec_data->pid[current_cmd] == 0)
			{
				dup2(exec_data->pipe_fd[1], STDOUT_FILENO);
				close(exec_data->pipe_fd[0]);
				close(exec_data->pipe_fd[1]);
				exec_piped_cmd(exec_data, current_cmd);
			}
			dup2(exec_data->pipe_fd[0], STDIN_FILENO);
			close(exec_data->pipe_fd[0]);
			close(exec_data->pipe_fd[1]);
			current_cmd++;
		}
		exec_last_cmd(exec_data, current_cmd);
		current_cmd = -1;
		while (++current_cmd < exec_data->nb_cmd)
			waitpid(exec_data->pid[current_cmd], NULL, 0);
	}
	dup2(exec_data->std_save[0], STDIN_FILENO);
	dup2(exec_data->std_save[1], STDOUT_FILENO);
	free_exec(exec_data);
}

static t_exec	*get_exec_data(t_minishell *minishell)
{
	t_exec	*exec_data;
	size_t	i;

	exec_data = ft_calloc(1, sizeof(t_exec));
	if (!exec_data)
		exit(EXIT_FAILURE);//TODO: Call exit function
	exec_data->token_list = minishell->token_list;
	exec_data->envp = minishell->envp;
	exec_data->std_save[0] = dup(STDIN_FILENO);
	exec_data->std_save[1] = dup(STDOUT_FILENO);
	exec_data->nb_cmd = get_nb_cmd(minishell->token_list);
	exec_data->nb_pipe = exec_data->nb_cmd - 1;
	exec_data->here_doc_fd = get_here_doc_fd(minishell->token_list, exec_data);
	exec_data->cmd = get_cmd_data(exec_data);
	exec_data->pid = malloc(sizeof(pid_t) * exec_data->nb_cmd);
	if (!exec_data->pid)
		exit(EXIT_FAILURE);//TODO: Call exit function
	i = -1;
	while (++i < exec_data->nb_cmd)
		exec_data->pid[i] = -1;
	return (exec_data);
}

static size_t	get_nb_cmd(t_token *token_list)
{
	size_t	nb_cmd;

	nb_cmd = 1;
	while (token_list)
	{
		if (token_list->type == PIPE)
			nb_cmd++;
		token_list = token_list->next;
	}
	return (nb_cmd);
}

static void	exec_last_cmd(t_exec *exec_data, size_t current_cmd)
{
	dprintf(STDERR_FILENO, "current_cmd: %zu\n", current_cmd);
	exec_data->pid[current_cmd] = fork();
	if (exec_data->pid[current_cmd] == -1)
		exit(EXIT_FAILURE); //TODO: Call exit function
	if (exec_data->pid[current_cmd] != 0)
		return ;
	dprintf(STDERR_FILENO, "cmd: %s\n", exec_data->cmd[current_cmd].argv[0]);
	handle_io(exec_data, current_cmd);
	if (exec_data->cmd[current_cmd].builtin != NONE)
	{
		exec_builtin(exec_data, current_cmd);
		free_exec(exec_data);
		exit(EXIT_SUCCESS);//TODO: Call exit function
	}
	execve(exec_data->cmd[current_cmd].argv[0],
		exec_data->cmd[current_cmd].argv, exec_data->envp);
	dprintf(STDERR_FILENO, "execve failed in cmd %zu\n", current_cmd);
	exit(EXIT_FAILURE);//TODO: Call exit function
}

void	free_exec(t_exec *exec_data)
{
	size_t	i;
	size_t	str_to_free;
	size_t	last_hd_free;

	i = 0;
	close(exec_data->std_save[0]);
	close(exec_data->std_save[1]);
	last_hd_free = 0;
	while (last_hd_free < exec_data->nb_here_doc)
		close(exec_data->here_doc_fd[last_hd_free++]);
	free(exec_data->here_doc_fd);
	free(exec_data->pid);
	i = exec_data->nb_cmd;
	while (i--)
	{
		str_to_free = ft_array_length((void **)exec_data->cmd[i].argv);
		while (str_to_free--)
			free(exec_data->cmd[i].argv[str_to_free]);
		free(exec_data->cmd[i].argv);
	}
	free(exec_data->cmd);
	free(exec_data);
}

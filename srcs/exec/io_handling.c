/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:47:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/03 13:40:48 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_input_fd(t_token token, int *fd_to_change, t_exec *exec_data);
static void	set_output_fd(t_token token, int *fd_to_change);

void	get_cmd_io(t_token *f_token, t_cmd cmd, t_exec *exec_data)
{
	t_token	*tmp;

	tmp = f_token;
	cmd.io_fd[0] = dup(STDIN_FILENO);
	cmd.io_fd[1] = dup(STDOUT_FILENO);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN || tmp->type == HERE_DOC)
			set_input_fd(*tmp, &cmd.io_fd[0], exec_data);
		else if (tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND)
			set_output_fd(*tmp, &cmd.io_fd[1]);
		if (cmd.io_fd[0] == -1 || cmd.io_fd[1] == -1)
			exit(IO_FAILURE);//TODO: Call exit function case infile or outfile fail
		tmp = tmp->next;
	}
}

static void	set_input_fd(t_token token, int fd_to_change[2], t_exec *exec_data)
{
	if (token.type == FILE_IN)
	{
		dup2(open(token.content[0], O_RDONLY), fd_to_change[0]);
	}
	else if (token.type == HERE_DOC)
	{
		dup2(exec_data->here_doc_fd[exec_data->nb_current_hd], fd_to_change[0]);
		close(exec_data->here_doc_fd[exec_data->nb_current_hd]);
		exec_data->nb_current_hd++;
	}
}

static void	set_output_fd(t_token token, int fd_to_change[2])
{
	if (token.type == FILE_OUT)
		dup2(open(token.content[0],
				O_WRONLY | O_CREAT | O_TRUNC, 0644), fd_to_change[1]);
	else if (token.type == FILE_OUT_APPEND)
		dup2(open(token.content[0],
				O_WRONLY | O_CREAT | O_APPEND, 0644), fd_to_change[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:26:34 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/25 14:35:58 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static enum e_i_type	exec_get_in_type(t_token *first_token);
static enum e_o_type	exec_get_out_type(t_token *first_token);
static char				*exec_get_path(t_token *first_token);
static char				**exec_get_cmd(t_token	*first_token);

void	translate_token_in_cmd(t_exec *exec, size_t cmd_nb)
{
	t_token	*first_token;
	size_t	i;

	exec->cmd[cmd_nb].command_id = cmd_nb;
	i = 0;
	first_token = exec->token_list;
	while (i < cmd_nb && cmd_nb != 0)
	{
		if (first_token->type == PIPE)
			i++;
		first_token = first_token->next;
	}
	exec->cmd[cmd_nb].in_type = exec_get_in_type(first_token);
	exec->cmd[cmd_nb].out_type = exec_get_out_type(first_token);
	if (exec->cmd[cmd_nb].in_type == INFILE
		|| exec->cmd[cmd_nb].out_type == OUTFILE
		|| exec->cmd[cmd_nb].out_type == OUTFILE_APPEND)
		get_io_file_path(&exec->cmd[cmd_nb], first_token);
	exec->cmd[cmd_nb].path = exec_get_path(first_token);
	exec->cmd[cmd_nb].cmd = exec_get_cmd(first_token);
}

enum e_i_type	exec_get_in_type(t_token *first_token)
{
	t_token	*cur_token;

	cur_token = first_token;
	while (cur_token && cur_token->type != PIPE)
	{
		if (cur_token->type == FILE_IN)
			return (INFILE);
		else if (cur_token->type == HERE_DOC)
			return (HERE_DOC_I);
		cur_token = cur_token->next;
	}
	return (STDIN);
}

enum e_o_type	exec_get_out_type(t_token *first_token)
{
	t_token	*cur_token;

	cur_token = first_token;
	while (cur_token && cur_token->type != PIPE)
	{
		if (cur_token->type == FILE_OUT)
			return (OUTFILE);
		else if (cur_token->type == FILE_OUT_APPEND)
			return (OUTFILE_APPEND);
		cur_token = cur_token->next;
	}
	return (STDOUT);
}

char	*exec_get_path(t_token *first_token)
{
	t_token	*cur_token;

	cur_token = first_token;
	while (cur_token && cur_token->type != PIPE)
	{
		if (cur_token->type == CMD)
			return (cur_token->content[0]);
		cur_token = cur_token->next;
	}
	return (NULL);
}

char	**exec_get_cmd(t_token	*first_token)
{
	t_token	*cur_token;

	cur_token = first_token;
	while (cur_token && cur_token->type != PIPE)
	{
		if (cur_token->type == CMD)
			return (exec_create_cmd(cur_token));
		cur_token = cur_token->next;
	}
	return (NULL);
}

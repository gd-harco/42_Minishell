/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:53:45 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/03 13:39:10 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec		*get_exec_data(t_minishell *minishell);
size_t		get_nb_cmd(t_token *token_list);
void		exec_command(t_cmd cmd, t_exec *exec_data);
void		exec_final_cmd(t_exec *exec_data);

void	master_exec(t_minishell	*minishell)
{
	t_exec	*exec_data;
	size_t	current_cmd;

	exec_data = get_exec_data(minishell);
	current_cmd = 0;

	dup2(exec_data->std_save[0], STDIN_FILENO);
	dup2(exec_data->std_save[1], STDOUT_FILENO);
}

t_exec	*get_exec_data(t_minishell *minishell)
{
	t_exec	*exec_data;

	exec_data = ft_calloc(1, sizeof(t_exec));
	if (!exec_data)
		exit(EXIT_FAILURE);//TODO: Call exit function
	exec_data->token_list = minishell->token_list;
	exec_data->envp = minishell->envp;
	exec_data->std_save[0] = dup(STDIN_FILENO);
	exec_data->std_save[1] = dup(STDOUT_FILENO);
	exec_data->nb_cmd = get_nb_cmd(minishell->token_list);
	exec_data->here_doc_fd = get_here_doc_fd(minishell->token_list);
	exec_data->cmd = get_cmd_data(exec_data);
	return (exec_data);
}

size_t	get_nb_cmd(t_token *token_list)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:53:45 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/01 14:09:28 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec		*get_exec_data(t_minishell *minishell);
size_t		get_nb_cmd(t_token *token_list);

void	master_exec(t_minishell	*minishell)
{
	// t_token	*tmp;
	t_exec	*exec_data;

	exec_data = get_exec_data(minishell);
	(void)exec_data;
	//TODO: Check for here doc, get the data and transform it into a fd using pipe
	//TODO: Check for pipe and allocate the good nimber of command
}

t_exec	*get_exec_data(t_minishell *minishell)
{
	t_exec	*exec_data;

	exec_data = malloc(sizeof(t_exec));
	if (!exec_data)
		exit(EXIT_FAILURE);//TODO: Call exit function
	exec_data->token_list = minishell->token_list;
	exec_data->envp = minishell->envp;
	exec_data->nb_cmd = get_nb_cmd(minishell->token_list);
	exec_data->cmd = malloc(sizeof(t_cmd) * exec_data->nb_cmd);
	exec_data->here_doc = get_here_doc_data(minishell->token_list);
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

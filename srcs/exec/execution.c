/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/24 12:16:50 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	master_exec(t_minishell *minishell_data)
{
	t_exec	*exec;

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
	exec->cmd = malloc(sizeof(t_cmd) * exec->nb_cmd);
	printf("filled");
}

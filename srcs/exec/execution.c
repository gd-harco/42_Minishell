/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/21 14:56:54 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	master_exec(t_minishell *minishell_data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->minishell_data = minishell_data;
	exec->nb_cmd = get_nb_cmd(minishell_data->token_list);
	if (exec->nb_cmd == 0)
		return ;
	translate_token_in_cmd(exec);
	exec->nb_here_doc = get_nb_here_doc(minishell_data->token_list);
	if (exec->nb_here_doc != 0)
		process_here_doc(exec);
	exec->cmd = malloc(sizeof(t_cmd) * exec->nb_cmd);
	// fill_cmd(exec);
	printf("filled");
}

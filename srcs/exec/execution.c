/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/19 12:33:27 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	master_exec(t_minishell *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->data = data;
	exec->nb_cmd = get_nb_cmd(data->token_list);
	exec->nb_here_doc = get_nb_here_doc(data->token_list);
	if (exec->nb_here_doc != 0)
		process_here_doc(exec);
}

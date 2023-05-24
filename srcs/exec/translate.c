/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:26:34 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/24 12:17:20 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	translate_token_in_cmd(t_exec *exec)
{
	int		i;
	t_token	*first_token;
	t_token	*tmp;

	first_token = exec->token_list;
	i = 0;
	exec->cmd = malloc(sizeof(t_cmd) * exec->nb_cmd);
	while (i < exec->nb_cmd)
	{
		tmp = first_token;

		exec->cmd[i].command_id = i;
		while (tmp->type != PIPE)
		{
			if (tmp->type == HERE_DOC)
				exec->cmd[i].in_type = HERE_DOC_I;
			else if (tmp->type == FILE_IN)
				exec->cmd[i].in_type = INFILE;
			else if (tmp->type == FILE_OUT)
				exec->cmd[i].out_type = OUTFILE;
			else if (tmp->type == FILE_OUT_APPEND)
				exec->cmd[i].out_type = OUTFILE_APPEND;
			tmp = tmp->next;
		}
		tmp = first_token;
		while (tmp->type != PIPE)
		{
			if (tmp->type == CMD)
			{
				exec->cmd[i].path = ft_strdup(tmp->content[0]);
				exec->cmd[i].cmd = tmp->content;
			}
			tmp = tmp->next;
		}
		exec->cmd[i].envp = exec->envp;
		if (i != exec->nb_cmd - 1)
		{
			while (first_token->type != PIPE)
				first_token = first_token->next;
			first_token = first_token->next;
		}
		i++;
	}
}

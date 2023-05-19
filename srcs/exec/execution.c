/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/19 12:18:36 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exec
{
	t_minishell	*data;
	int			nb_cmd;
	int			nb_here_doc;
	char 		*here_doc;
}				t_exec;

void	master_exec(t_minishell *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->data = data;
	exec->nb_cmd = get_nb_cmd(data->token_list);
	exec->nb_here_doc = get_nb_here_doc(data->token_list);
	printf("nb_cmd: %d\n", exec->nb_cmd);
	printf("nb_here_doc: %d\n", exec->nb_here_doc);
}

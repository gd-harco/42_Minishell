/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:59:10 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/26 11:40:55 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exec_create_cmd(t_token	*cur_token)
{
	char	**tmp;
	char	**cmd;
	int		nb_arg;

	tmp = ft_split(cur_token->content[1], ' ');
	nb_arg = ft_array_length((void **)tmp);
	cmd = ft_calloc(sizeof(char *), (nb_arg + 2));
	cmd[0] = cur_token->content[0];
	cmd[nb_arg++] = NULL;
	while (--nb_arg > 0)
		cmd[nb_arg] = ft_strdup(tmp[nb_arg - 1]);
	ft_free_split((void **)tmp);
	return (cmd);
}

void	get_io_file_path(t_cmd *cmd, t_token *first_token)
{
	t_token	*tmp;

	if (cmd->in_type == INFILE)
	{
		tmp = first_token;
		while (tmp && tmp->type != FILE_IN)
			tmp = tmp->next;
		cmd->in_file = ft_strdup(tmp->content[0]);
	}
	else
		cmd->in_file = NULL;
	if (cmd->out_type != 0)
	{
		tmp = first_token;
		while (tmp && !(tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND))
			tmp = tmp->next;
		cmd->out_file = ft_strdup(tmp->content[0]);
	}
	else
		cmd->out_file = NULL;
}

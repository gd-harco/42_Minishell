/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:13 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/11 13:40:53 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	identify_string(t_token *current, enum e_type prev);

//Repasse sur la liste de tokens et remplace les
//tokens de type STING par CALL_ENV_VAR, BUILTIN, CMD
void	second_parsing(t_token *token_list)
{
	t_token		*tmp;
	enum e_type	prev_type;

	prev_type = NULL;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == STRING)
			identify_string(tmp, prev_type);
		prev_type = tmp->type;
		tmp = tmp->next;
	}
}

static void	identify_string(t_token *current, enum e_type prev)
{
	if (prev == PIPE)
		current->type = CMD;
	else if (prev == CHEVRON_IN)
		current->type = FILE_IN;
	else if (prev == CHEVRON_OUT)
		current->type = FILE_OUT;
	else if (prev == DOUBLE_CHEVRON_OUT)
		current->type = FILE_OUT_APPEND;
	else
	{
		if (current->content[0][0] == "$")
			current->type = CALL_ENV_VAR;
		else
			identify_cmd(current);
	}
}

static void	identify_cmd(t_token *current)
{
	if (current->content[0] == "echo" || current->content[0] == "cd"
		|| current->content[0] == "pwd" || current->content[0] == "export"
		|| current->content[0] == "unset" || current->content[0] == "env"
		|| current->content[0] == "exit")
		current->type = BUILTIN;
	else
		current->type = CMD;
}

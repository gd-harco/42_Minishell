/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:56:13 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/10 15:48:16 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Repasse sur la liste de tokens et remplace les
//tokens de type STING par CALL_ENV_VAR, BUILTIN, CMD
void	second_parsing(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp->type != STRING)
		tmp = tmp->next;

}

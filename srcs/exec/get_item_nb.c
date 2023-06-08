/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_item_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:15:24 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/19 12:29:06 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_cmd(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

int	get_nb_here_doc(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == HERE_DOC)
			i++;
		token = token->next;
	}
	return (i);
}

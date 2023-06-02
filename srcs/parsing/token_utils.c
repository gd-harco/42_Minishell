/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:15:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/02 17:25:23 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_last(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*tail;

	if (!token)
		return ;
	if (*token)
	{
		tail = token_last(*token);
		tail->next = new;
	}
	else
		*token = new;
}

static void	token_delone(t_token *tkn, void (*del)(void *))
{
	if (!tkn || !del)
		return ;
	// del(tkn->type);
	del(tkn->content);
	free(tkn);
}

void	token_clear(t_token **tkn, void (*f)(void*))
{
	t_token	*buffer;

	if (!f && !tkn)
		return ;
	while (*tkn)
	{
		buffer = (*tkn)->next;
		token_delone(*tkn, f);
		*tkn = buffer;
	}
}

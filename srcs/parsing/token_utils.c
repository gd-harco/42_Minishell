/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:15:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/27 13:45:00 by tdutel           ###   ########.fr       */
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

// void	token_clear(t_token *tkn)
// {
// 	t_token	*buffer;

// 	if (!tkn)
// 		return ;
// 	while (tkn)
// 	{
// 		buffer = tkn->next;
// 		ft_free_array((void **)tkn->content);
// 		// free(tkn->content);
// 		// free(tkn->content[1]);
// 		tkn = buffer;
// 	}
// }

void	token_clear(t_token *tkn)
{
	int	i;

	i = 0;
	if (tkn == NULL)
		return ;
	while (i < 2)
	{
		if (tkn->content[i] != NULL)
		{
			free(tkn->content[i]);
			tkn->content[i] = NULL;
		}
		i++;
	}
	token_clear(tkn->next); // Appel récursif pour les tokens suivants
	free(tkn);
	tkn = NULL;
}

// void	token_clear(t_token **tkn)
// {
// 	t_token	*buffer;

// 	if (!tkn)
// 		return ;
// 	while (tkn)
// 	{
// 		buffer = (*tkn)->next;
// 		ft_free_array((void **)(*tkn)->content);
// 		// free(tkn->content);
// 		// free(tkn->content[1]);
// 		free(*tkn);
// 		*tkn = buffer;
// 	}
// }

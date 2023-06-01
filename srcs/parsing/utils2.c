/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/01 14:33:53 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_last(t_token *token);

bool	already_pipe(t_token t_new)
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}

int	ft_nb_pipe(char *str)
{
	int	i;
	int	c;

	if (!str)
		return (0);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

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

// void	token_add_front(t_token **token, t_token *new)
// {
// 	if (new && token)
// 	{
// 		new->next = *token;
// 		*token = new;
// 	}
// }

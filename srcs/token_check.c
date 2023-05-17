/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:47:52 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/17 11:48:17 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	already_cmd(t_token *t_new, t_token *tmp)
{
	t_token	*tmp2;

	tmp2 = malloc(sizeof(t_token));
	tmp2 = t_new;

	while (tmp2 && tmp2 != tmp)
	{
		if (tmp2->type == PIPE)
			t_new = tmp2->next;
		tmp2 = tmp2->next;
	}
	if (t_new && (tmp->type == CMD || tmp->type == BUILTIN))
	{
		while (t_new->next && t_new->type != PIPE
			&& t_new->type != CMD && t_new->type != BUILTIN)
			t_new = t_new->next;
		if (!t_new->next || t_new == tmp)
			return (false);
		else if (t_new->type == PIPE)
			return (already_cmd(t_new->next, tmp));
		else
			return (true);
	}
	else
		return (false);
}

void	token_arg(char **s, int **i)
{
	if (!s[**i])
		return ;
	while (s[**i + 1] && s[**i + 1][0] != '<' && s[**i + 1][0] != '>'
		&& s[**i + 1][0] != '|' && s[**i + 1][0] != '\0')
	{
		++**i;
	}
}

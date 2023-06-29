/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:47:52 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/29 11:28:13 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	cmd_check(t_token *t_new, t_token *tmp)
{
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

bool	already_cmd(t_token *t_new, t_token *tmp)
{
	t_token	*tmp2;

	tmp2 = malloc(sizeof(t_token));
	if (!tmp2)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	tmp2 = t_new;
	while (tmp2 && tmp2 != tmp)
	{
		if (tmp2->type == PIPE)
			t_new = tmp2->next;
		tmp2 = tmp2->next;
	}
	token_clear(&tmp2);
	return (cmd_check(t_new, tmp));
}

void	token_arg(t_var *var)
{
	if (!var->s[var->i])
		return ;
	while (var->s[var->i + 1] && var->s[var->i + 1][0] != '<'
		&& var->s[var->i + 1][0] != '>' && var->s[var->i + 1][0] != '|'
		&& var->s[var->i + 1][0] != '\0')
	{
		++var->i;
	}
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

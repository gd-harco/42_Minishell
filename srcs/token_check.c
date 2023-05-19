/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:47:52 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/19 13:18:42 by tdutel           ###   ########.fr       */
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


int	is_quote_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '"')
			return (2);
		i++;
	}
	return (0);
}

bool	var_init(t_var *var)
{
	var->spipe = ft_split(var->str, '|');
	var->s = ft_split(var->spipe[var->index], ' ');
	var->new_tkn = malloc(sizeof(t_token));
	var->new_tkn->content = malloc(sizeof(char *) * 2);
	if (!var->new_tkn->content || !var->spipe || !var->s)
		return (false);
	return (true);
}

	// if (var->spipe[var->index][0] != '\'' && var->spipe[var->index][0] != '"')

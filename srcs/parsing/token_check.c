/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:47:52 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/31 13:55:28 by tdutel           ###   ########.fr       */
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

bool	var_init(t_var *var, t_quote *quote)
{
	if (is_quote_in(var->str) != 0)
		quote->is_quote = true;
	var->spipe = ft_split(var->str, '|');
	var->s = ft_split(var->spipe[var->index], ' ');
	var->new_tkn = malloc(sizeof(t_token));
	var->new_tkn->content = malloc(sizeof(char *) * 2);
	if (!var->new_tkn->content || !var->spipe || !var->s)
		return (false);
	return (true);
}

char	*check_var(t_var *var, t_varenv *v_e)
{
	v_e->j = var->i;
	if (is_env_in(*var, v_e->j) == true)
	{
		var->s_p = ft_strjoinsp(NULL, ft_trunc(var->s[0], 0, '$'));
		env_arg(var, v_e);
		var->s_p = ft_strjoin(var->s_p, var->env);
		return (var->s_p);
	}
	else
		return (ft_strdup(var->s_p));
}

	// if (var->spipe[var->index][0] != '\'' && var->spipe[var->index][0] != '"')

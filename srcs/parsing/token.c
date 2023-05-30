/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/23 10:30:53 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*token_last(t_token *token);
void			token_add_back(t_token **token, t_token *new);

t_token	*get_token(t_var *var)
{
	t_token	*t_new;
	t_token	*tmp;

	var->index = 0;
	var->i = 0;
	t_new = token_init(var);
	var->i++;
	while (var->spipe[var->index])
	{
		while (var->s[var->i])
		{
			tmp = token_init(var);
			if (tmp != NULL && already_cmd(t_new, tmp) != true)
				token_add_back(&t_new, tmp);
			var->i++;
		}
		if (var->spipe[var->index + 1] != NULL)
		{
			tmp = token_pipe();
			token_add_back(&t_new, tmp);
		}
		var->index++;
		var->i = 0;
	}
	return (t_new);
}

t_token	*token_init(t_var *var)
{
	if (var_init(var) == false || !var->s[var->i]
		|| (var->i != 0 && var->s[var->i][0] == '-'))
		return (NULL);
	if (var->s[var->i][0] == '<')
	{
		if (token_infile(var) == -1)
			return (NULL);
	}
	else if (var->s[var->i][0] == '>')
		token_outfile(var);
	else
	{
		if (is_builtin(var->s[var->i]) == true)
			token_builtin(var);
		else
			token_cmd(var);
		token_arg(var);
	}
	var->new_tkn->next = NULL;
	return (var->new_tkn);
}

static t_token	*token_last(t_token *token)
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



// gerer var env et '' ""

/*
echo "$(echo "upg")"
	upg
echo '$(echo"upg")'
	$(echo"upg")
*/

//gerer les space de '<' et '>' ex: <<in>>out	heredoc et out append




// gerer les string (ex : echo hello)
//differencier un infile d'un argument de cmd
//	(ex: echo bonjour : echo, bonjour mais aussi bonjour, null	a enlever)
//gerer plusieurs infile	ok
// refaire strjoin pour add space	ok
//gerer les spaces de '|' ex : echo bonjour|rev	doit faire ruojnob	ok

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/18 13:00:39 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	heredoc_infile(t_var var)
{
	if (var.s[var.i][2] != '\0')
		var.new_tkn->content[0] = ft_strdup(ft_substr
				(var.s[var.i], 2, ft_strlen(var.s[var.i])));
	else
		var.new_tkn->content[0] = ft_strdup(var.s[++var.i]);
	var.new_tkn->type = HERE_DOC;
}

int	token_infile(t_var *var)
{
	if (is_last_infile(var->s, var->i) != true)
	{
		if (var->s[var->i][1] == '\0')
			++var->i;
		return (-1);
	}
	if (var->s[var->i][1] == '<')
	{
		heredoc_infile(*var);
	}
	else if (var->s[var->i][1] != '\0')
	{
		var->new_tkn->type = FILE_IN;
		var->new_tkn->content[0] = ft_strdup(ft_substr
				(var->s[var->i], 1, ft_strlen(var->s[var->i])));
	}
	else
	{
		var->new_tkn->type = FILE_IN;
		var->new_tkn->content[0] = ft_strdup(var->s[++var->i]);
	}
	var->new_tkn->content[1] = NULL;
	return (0);
}

void	token_outfile(t_var var)
{
	if (var.s[var.i + 1] && var.s[var.i][1] == '>' )
	{
		if (var.s[var.i][2] != '\0')
			var.new_tkn->content[0] = ft_strdup(ft_substr(
						var.s[var.i], 2, ft_strlen(var.s[var.i])));
		else
			var.new_tkn->content[0] = ft_strdup(var.s[++var.i]);
		var.new_tkn->type = FILE_OUT_APPEND;
	}
	else if (var.s[var.i][1] != '\0')
	{
		var.new_tkn->content[0] = ft_strdup(ft_substr
				(var.s[var.i], 1, ft_strlen(var.s[var.i])));
		var.new_tkn->type = FILE_OUT;
	}
	else
	{
		var.new_tkn->content[0] = ft_strdup(var.s[++var.i]);
		var.new_tkn->type = FILE_OUT;
	}
	var.new_tkn->content[1] = NULL;
}

/*void	token_pipe(t_var var)
{
	if (var.s[var.i][0] == '|' && var.s[var.i][1] == '\0')
	{
		var.new_tkn->type = PIPE;
		var.new_tkn->content[0] = ft_strdup("|");
		var.new_tkn->content[1] = NULL;
		return ;
	}
}*/

t_token	*token_pipe(t_var var)
{
	var.new_tkn->type = PIPE;
	var.new_tkn->content[0] = ft_strdup("|");
	var.new_tkn->content[1] = NULL;
	var.new_tkn->next = NULL;
	return (var.new_tkn);
}
	// si [0] != '|'
	// 	c = ft_split(s, '|');
	// 	gerer le c[0] puis ecrire pipe puis gerer suite
	// else token pour premiere partie du char jusquau | puis tkn pipe puis 2eme partie
		// return (token_pipe(new, ft_substr(s, 1, ft_strlen(s))));

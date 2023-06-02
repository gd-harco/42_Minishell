/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/02 17:24:11 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_infile(t_var *var)
{
	if (var->s[var->i][2] != '\0')
		var->new_tkn->content[0] = ft_strdup(ft_substr
				(var->s[var->i], 2, ft_strlen(var->s[var->i])));
	else
	{
		var->i++;
		var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
	}
	var->new_tkn->type = HERE_DOC;
}

void	token_infile(t_var *var)
{
	if (var->s[var->i][1] && var->s[var->i][1] == '<')
	{
		heredoc_infile(var);
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
}

void	token_outfile(t_var *var)
{
	if (var->s[var->i][1] && var->s[var->i][1] == '>' )
	{
		if (var->s[var->i][2] != '\0')
			var->new_tkn->content[0] = ft_strdup(ft_substr(
						var->s[var->i], 2, ft_strlen(var->s[var->i])));
		else
		{
			var->i++;
			var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
		}
		var->new_tkn->type = FILE_OUT_APPEND;
	}
	else if (var->s[var->i][1] != '\0')
	{
		var->new_tkn->content[0] = ft_strdup(ft_substr
				(var->s[var->i], 1, ft_strlen(var->s[var->i])));
		var->new_tkn->type = FILE_OUT;
	}
	else
	{
		var->new_tkn->content[0] = ft_strdup(var->s[++var->i]);
		var->new_tkn->type = FILE_OUT;
	}
	var->new_tkn->content[1] = NULL;
}

t_token	*token_pipe(void)
{
	t_token	*tmp;


	tmp = malloc(sizeof(t_token));
	if (!tmp)
		exit(EXIT_FAILURE);//TODO: Call exit function
	tmp->type = PIPE;
	tmp->content = malloc(sizeof(char *) * 2);
	if (!tmp->content)
		exit(EXIT_FAILURE);//TODO: Call exit function
	tmp->content[0] = ft_strdup("|");
	tmp->content[1] = NULL;
	tmp->next = NULL;
	return (tmp);
}

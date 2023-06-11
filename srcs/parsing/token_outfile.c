/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/11 13:55:08 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_outfile(t_var *var)
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
}

static void	append_outfile(t_var *var, t_varenv *v_e)
{
	if (var->s[var->i][2] != '\0')
	{
		quote_manager_inout(var, v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
	}
	else
	{
		var->i++;
		v_e->j++;
		quote_manager(var, v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
	}
	var->new_tkn->type = FILE_OUT_APPEND;
}

static void	fill_quote_outfile(t_var *var)
{
	t_varenv	v_e;

	v_e.j = var->i;
	if (var->s[var->i][1] && var->s[var->i][1] == '>' )
	{
		append_outfile(var, &v_e);
	}
	else if (var->s[var->i][1] != '\0')
	{
		var->new_tkn->type = FILE_OUT;
		quote_manager_inout(var, &v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
	}
	else
	{
		var->i++;
		v_e.j++;
		var->new_tkn->type = FILE_OUT;
		quote_manager(var, &v_e);
		var->quote_cmd = true;
		var->new_tkn->content[0] = ft_strdup(var->quote);
	}
}

int	token_outfile(t_var *var)
{
	if ((var->s[var->i][1] == '\0' && !var->s[var->i + 1])
	|| (var->s[var->i][1] == '>' && var->s[var->i][2] == '\0'
	&& !var->s[var->i + 1]))
		return (-1);
	if (is_quote_in(var->s[var->i]) == 0 && ((var->s[var->i][1] == '\0'
			&& is_quote_in(var->s[var->i + 1]) == 0)
		|| (var->s[var->i][1] == '>' && var->s[var->i][2] == '\0'
				&& is_quote_in(var->s[var->i + 1]) == 0)))
	{
		fill_outfile(var);
	}
	else
	{
		fill_quote_outfile(var);
	}
	var->new_tkn->content[1] = NULL;
	return (0);
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

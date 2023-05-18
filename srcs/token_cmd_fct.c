/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/18 14:59:10 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_builtin(t_var *var)
{
	int		j;

	var->arg = NULL;
	j = var->i + 1;
	while (var->s[j])
	{
		if (not_in_out(var->s, j) == true)
			var->arg = ft_strjoinsp(var->arg, var->s[j]);
		j++;
	}
	var->new_tkn->type = BUILTIN;
	var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

void	token_cmd(t_var *var)
{
	int		j;

	var->arg = NULL;
	var->path = get_path(var->envp);
	var->s_p = process(var->spipe[var->index], var->path, var->i);
	j = var->i + 1;
	while (var->s[j])
	{
		if (not_in_out(var->s, j) == true)
			var->arg = ft_strjoinsp(var->arg, var->s[j]);
		j++;
	}
	var->new_tkn->type = CMD;
	var->new_tkn->content[0] = ft_strdup(var->s_p);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

/*bool	is_pipe_in(t_var var, int j)
{
	int	i;

	i = 0;
	while (var.s[j][i])
	{
		if (var.s[j][i] == '|')
			return (true);
		i++;
	}
	return (false);
}

static char	*str_trunc(char *str, char c)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (str[i] != c)
	{
		i++;
	}
	s = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}
*/


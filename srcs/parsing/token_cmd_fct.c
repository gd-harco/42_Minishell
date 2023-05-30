/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/29 15:49:08 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_env_in(t_var var, int j)
{
	int	i;

	i = 0;
	while (var.s[j][i])
	{
		if (var.s[j][i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	is_metachar(char c)
{
	if (c == '.' || c == ',' || c == '/' || c == '\\' || c == '^' || c == '$'
		|| c == '-' || c == '+' || c == '=' || c == '?' || c == '!'
		|| c == '@' || c == '#' || c == '%' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == ':' || c == '~')
		return (true);
	else
		return (false);
}

void	token_builtin(t_var *var)
{
	t_varenv	v_e;

	var->arg = NULL;
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		if (not_in_out(var->s, v_e.j) == true
			&& is_env_in(*var, v_e.j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[v_e.j]);
		else if (is_env_in(*var, v_e.j) == true)
		{
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[v_e.j], 0, '$'));
			env_arg(var, &v_e);
			var->arg = ft_strjoin(var->arg, var->env);
		}
		v_e.j++;
	}
	var->new_tkn->type = BUILTIN;
	var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

void	token_cmd(t_var *var)
{
	t_varenv	v_e;

	var->arg = NULL;
	var->path = get_path(var->envp);
	var->s_p = process(var->spipe[var->index], var->path, var->i);
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		if (not_in_out(var->s, v_e.j) == true
			&& is_env_in(*var, v_e.j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[v_e.j]);
		else if (is_env_in(*var, v_e.j) == true)
		{
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[v_e.j], 0, '$'));
			env_arg(var, &v_e);
			var->arg = ft_strjoin(var->arg, var->env);
		}
		v_e.j++;
	}
	var->new_tkn->type = CMD;
	var->new_tkn->content[0] = check_var(var, &v_e);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

char	*ft_trunc(char *str, int start, char c)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	k = 0;
	if (!str || str[i] == c)
		return ("");
	while (str[i] && str[i] != c)
	{
		i++;
		k++;
	}
	s = malloc(sizeof(char) * (k + 1));
	j = 0;
	while (j < k)
	{
		s[j] = str[start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

// gerer $USER $? -e pour pas avoir content[0] -e $? $USER		ok join NULL
// gerer $? pour pouvoir afficher derriere $?et$USER	ok

//	coder $$ et $?		ok sauf $$ mais pas besoin

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/06 16:39:21 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_builtin(t_var *var)
{
	t_varenv	v_e;

	var->arg = NULL;
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		if (has_in_out(var->s, v_e.j) == false
			&& is_env_in(*var, v_e.j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[v_e.j]);
		else if (is_env_in(*var, v_e.j) == true)
		{
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[v_e.j], 0, '$'));
			env_arg(var, &v_e);
			var->arg = ft_freestrjoin(var->arg, var->env);
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
	char		*tmp;
	int			nb;

	nb = 0;
	var->arg = NULL;
	var->path = get_path(var->envp);
	var->s_p = process(var->spipe[var->index], var->path, var->i);
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		if (is_quote_in(var->s[var->i + 1], nb) == 0)
		{
			if (has_in_out(var->s, v_e.j) == false
				&& is_env_in(*var, v_e.j) == false)
			{
				tmp = ft_strjoinsp(var->arg, var->s[v_e.j]);
				var->arg = ft_strdup(tmp);
				free(tmp);
			}
			else if (is_env_in(*var, v_e.j) == true)
			{
				var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[v_e.j], 0, '$'));
				env_arg(var, &v_e);
				var->arg = ft_freestrjoin(var->arg, var->env);
			}
		}
		else if (is_quote_in(var->s[var->i + 1], nb) != 0)
		{
			nb++;
			var->arg = ft_strjoinsp(var->arg, ft_truncstr(*var, v_e, 0, "\"\'"));
			quote_manager(var, &v_e);
			var->arg = ft_freestrjoin(var->arg, var->quote);
		}
		v_e.j++;
	}
	var->new_tkn->type = CMD;
	var->new_tkn->content[0] = check_var(var, &v_e);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

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
		|| c == '{' || c == '}' || c == ':' || c == '`')
		return (true);
	else
		return (false);
}

int	is_quote_instr(char *str, int ind)
{

	if (!str || !str[ind])
		return (0);
	while (str[ind])
	{
		if (str[ind] == '\'')
			return (1);
		if (str[ind] == '"')
			return (2);
		ind++;
	}
	return (0);
}

int	is_quote_in(char *str, int nb)
{
	int	i;

	i = 0;
	if (!str || !str[nb])
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' && nb == 0)
			return (1);
		else if (str[i] == '"' && nb == 0)
			return (2);
		else if (str[i] == '\'' && nb > 0)
			--nb;
		else if (str[i] == '"' && nb > 0)
			--nb;
		i++;
	}
	return (0);
}

// gerer $USER $? -e pour pas avoir content[0] -e $? $USER		ok join NULL
// gerer $? pour pouvoir afficher derriere $?et$USER	ok

//	coder $$ et $?		ok sauf $$ mais pas besoin

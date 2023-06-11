/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/11 13:14:54 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_arg_builtin(t_var *var, t_varenv *v_e);
static void	fill_arg_cmd(t_var *var, t_varenv *v_e, char **tmp);

void	token_builtin(t_var *var)
{
	t_varenv	v_e;

	var->arg = NULL;
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		fill_arg_builtin(var, &v_e);
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

	v_e.j = var->i;
	var->arg = NULL;
	if (is_quote_in(var->s[v_e.j]) == 0)
	{	
		var->path = get_path(var->env_cpy);
		var->s_p = process(var->spipe[var->index], var->path, var->i);
	}
	else
	{
		quote_manager(var, &v_e);
		var->quote_cmd = true;
		var->s_p = ft_strdup(var->quote);
	}
	v_e.j++;
	while (var->s[v_e.j])
	{
		fill_arg_cmd(var, &v_e, &tmp);
		v_e.j++;
	}
	var->new_tkn->type = CMD;
	var->new_tkn->content[0] = check_var(var, &v_e);
	var->new_tkn->content[1] = ft_strdup(var->arg);
}

static void	fill_arg_builtin(t_var *var, t_varenv *v_e)
{
	if (is_quote_in(var->s[v_e->j]) == 0)
	{
		if (has_in_out(var->s, v_e->j) == false
			&& is_env_in(*var, v_e->j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[v_e->j], 1);
		else if (is_env_in(*var, v_e->j) == true)
		{
			var->arg = ft_strjoinsp(var->arg,
					ft_trunc(var->s[v_e->j], 0, "$", *var), 1);
			env_arg(var, v_e);
			var->arg = ft_strjoinsp(var->arg, var->env, 0);
		}
	}
	else if (is_quote_in(var->s[v_e->j]) != 0)
	{
		quote_manager(var, v_e);
		var->arg = ft_strjoinsp(var->arg, var->quote, 1);
	}
}

static void	fill_arg_cmd(t_var *var, t_varenv *v_e, char **tmp)
{
	if (is_quote_in(var->s[v_e->j]) == 0)
	{
		if (has_in_out(var->s, v_e->j) == false
			&& is_env_in(*var, v_e->j) == false)
		{
			*tmp = ft_strjoinsp(var->arg, var->s[v_e->j], 1);
			var->arg = ft_strdup(*tmp);
			free(*tmp);
		}
		else if (is_env_in(*var, v_e->j) == true)
		{
			var->arg = ft_strjoinsp(var->arg,
					ft_trunc(var->s[v_e->j], 0, "$", *var), 1);
			env_arg(var, v_e);
			var->arg = ft_strjoinsp(var->arg, var->env, 0);
		}
	}
	else if (is_quote_in(var->s[v_e->j]) != 0
		&& has_in_out(var->s, v_e->j - 1) == false)
	{
		quote_manager(var, v_e);
		var->arg = ft_strjoinsp(var->arg, var->quote, 1);
	}
}


//TODO
// quand metachar juste apres $ n'ecris pas apres le metachar : ls << in"s$.,a USER"
// 																ecrit just ins$

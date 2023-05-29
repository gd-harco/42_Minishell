/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:47:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/29 10:55:33 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		add_env_arg(t_var *var, t_varenv *v_e, int l);
void	find_env_var(t_var *var, t_varenv *v_e, int l);
int		fill_env_var(t_var *var, t_varenv *v_e);
int		env_symbol(t_var *var, char c);

void	env_arg(t_var *var, t_varenv *v_e)
{
	int	l;

	var->env = NULL;
	l = 0;
	while (add_env_arg(var, v_e, l) == 0)
	{
		l++;
	}
}

int	add_env_arg(t_var *var, t_varenv *v_e, int l)
{
	int	ret_value;

	v_e->i = -1;
	v_e->k = 0;
	v_e->m = 0;
	while (v_e->m <= l)
	{
		find_env_var(var, v_e, l);
	}
	ret_value = fill_env_var(var, v_e);
	if (ret_value != 2)
		return (ret_value);
	if (var->s[v_e->j][v_e->i + 1 + v_e->k + ft_strlen(ft_trunc
			(var->s[v_e->j], v_e->i + 1 + v_e->k, '$'))] == '$')
		return (0);
	else
		return (1);
}

void	find_env_var(t_var *var, t_varenv *v_e, int l)
{
	v_e->i++;
	while (var->s[v_e->j][v_e->i] && var->s[v_e->j][v_e->i] != '$')
		v_e->i++;
	while (var->s[v_e->j][v_e->i + 1 + v_e->k]
		&& !is_metachar(var->s[v_e->j][v_e->i + 1 + v_e->k]))
		v_e->k++;
	if (v_e->m != l)
	{
		v_e->i = v_e->i + v_e->k;
		v_e->k = 0;
	}
	v_e->m++;
}

int	fill_env_var(t_var *var, t_varenv *v_e)
{
	v_e->var_env = ft_substr(var->s[v_e->j], v_e->i + 1, v_e->k);
	if (v_e->var_env[0] == '\0')
		return (env_symbol(var, var->s[v_e->j][v_e->i + 1 + v_e->k]));
	v_e->m = 0;
	while (var->envp[v_e->m] && ft_strnstr
		(var->envp[v_e->m], v_e->var_env, ft_strlen(v_e->var_env)) == NULL)
		v_e->m++;
	if (var->envp[v_e->m] && var->envp[v_e->m][ft_strlen(v_e->var_env)] == '=')
		var->env = ft_strjoin(var->env, ft_substr(var->envp[v_e->m],
					v_e->k + 1, ft_strlen(var->envp[v_e->m]) - v_e->k));
	else
		var->env = ft_strjoin(var->env, NULL);
	if (var->s[v_e->j][v_e->i + 1 + v_e->k] != '$')
		var->env = ft_strjoin(var->env, ft_substr(var->s[v_e->j],
					v_e->i + 1 + v_e->k, ft_strlen(ft_trunc
						(var->s[v_e->j], v_e->i + 1 + v_e->k, '$'))));
	return (2);
}

int	env_symbol(t_var *var, char c)
{
	var->env = ft_strjoin(var->env, "$");
	if (c != '\0')
		return (0);
	else
		return (1);
}

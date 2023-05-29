/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:47:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/29 15:33:45 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		add_env_arg(t_var *var, t_varenv *v_e, int l);
void	find_env_var(t_var *var, t_varenv *v_e, int l);
int		fill_env_var(t_var *var, t_varenv *v_e);
int		env_symbol(t_var *var, char c, char d);

/*
	la variable l va permettre de faire une comparaison dans la chaine,
	pour savoir combien de var d'env ont été check et pour toutes les gérer.
*/

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

/*
	add_env_arg permet de remplir var->env de toutes
	les variable d'env et d'autres metachar.
	On return 0 si l'indice de fin est toujours un $
	car cela s'ignifie qu'il reste des var d'env à join.
*/

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
	if (ret_value == 1)
		return (ret_value);
	if (var->s[v_e->j] && var->s[v_e->j][v_e->i + 1 + v_e->k + ft_strlen
		(ft_trunc(var->s[v_e->j], v_e->i + 1 + v_e->k, '$'))] == '$')
		return (0);
	else
		return (1);
}

/*
	find_env_var permet de parcourir la chaine jusqu'à trouver le $
	i est ainsi l'indice du $. On parcourt ensuite la suite avec k
	k est ainsi le nombre de charactere de la variable d'env $.
	On regarde si m = l pour voir si on a déjà traité cette variable
	d'environnement $. Sinon, on remet k à 0 et on implémente m.
*/

void	find_env_var(t_var *var, t_varenv *v_e, int l)
{
	v_e->i++;
	while (var->s[v_e->j]
		&& var->s[v_e->j][v_e->i] && var->s[v_e->j][v_e->i] != '$')
		v_e->i++;
	while (var->s[v_e->j] && var->s[v_e->j][v_e->i + 1 + v_e->k]
		&& !is_metachar(var->s[v_e->j][v_e->i + 1 + v_e->k]))
		v_e->k++;
	if (v_e->m != l)
	{
		v_e->i = v_e->i + v_e->k;
		v_e->k = 0;
	}
	v_e->m++;
}

/*
	fill_env_var permet de remplir la variable var_env avec la variable
	d'environnement associée via ft_strjoin() ft_substr() et en cherchant
	la ligne d'envp correspondant via ft_strnstr. le return permet de gérer
	le cas d'un simple $ dans add_env_arg()
	et ansi de sortir de la boucle dans env_arg()
*/

int	fill_env_var(t_var *var, t_varenv *v_e)
{
	v_e->var_env = ft_substr(var->s[v_e->j], v_e->i + 1, v_e->k);
	if (var->s[v_e->j] && var->s[v_e->j][v_e->i + 1 + v_e->k] == '?')
	{	
		env_symbol(var, var->s[v_e->j][v_e->i + 1 + v_e->k],
			var->s[v_e->j][v_e->i + 1 + v_e->k + 1]);
		v_e->k++;
	}
	else if (v_e->var_env && (v_e->var_env[0] == '\0'))
		return (env_symbol(var, var->s[v_e->j][v_e->i + 1 + v_e->k],
			var->s[v_e->j][v_e->i + 1 + v_e->k + 1]));
	v_e->m = 0;
	while (var->envp[v_e->m] && v_e->var_env && ft_strnstr
		(var->envp[v_e->m], v_e->var_env, ft_strlen(v_e->var_env)) == NULL)
		v_e->m++;
	if (var->envp[v_e->m] && var->envp[v_e->m][ft_strlen(v_e->var_env)] == '=')
		var->env = ft_strjoin(var->env, ft_substr(var->envp[v_e->m],
					v_e->k + 1, ft_strlen(var->envp[v_e->m]) - v_e->k));
	else
		var->env = ft_strjoin(var->env, NULL);
	if (var->s[v_e->j] && var->s[v_e->j][v_e->i + 1 + v_e->k] != '$')
		var->env = ft_strjoin(var->env, ft_substr(var->s[v_e->j],
					v_e->i + 1 + v_e->k, ft_strlen(ft_trunc
						(var->s[v_e->j], v_e->i + 1 + v_e->k, '$'))));
	return (2);
}

/*
	le return permet de définir s'il reste des charactères à join
	dans var->env et sinon de sortir de la boucle dans env_arg()
*/

int	env_symbol(t_var *var, char c, char d)
{
	if (c == '?')
		var->env = ft_strjoin(var->env, "var_global");
	else
		var->env = ft_strjoin(var->env, "$");
	if (d != '\0')
		return (0);
	else
		return (1);
}

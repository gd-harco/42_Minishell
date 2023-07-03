/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:25:29 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/02 15:25:56 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_quote(char *str_tmp, t_var *var, t_var_quote *v_q)
{
	if (str_tmp[v_q->i] == '`' && var->is_pquote == true)
		v_q->t[0] = '|';
	else if (str_tmp[v_q->i] == '~' && var->is_squote == true)
		v_q->t[0] = ' ';
	else
		v_q->t[0] = str_tmp[v_q->i];
}

static void	dub_quote(char *str_tmp, t_var *var, t_varenv *v_e, char **tmp)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	v_q.i = 1;
	var->env = NULL;
	if (is_env_in_str(str_tmp) == true)
	{
		v_q.tmp = ft_trunc(str_tmp, 1, "$", *var);
		*tmp = ft_strjoin(*tmp, v_q.tmp);
		ft_free_secure(&v_q.tmp);
		quote_env(str_tmp, var, v_e);
		var->env = ft_reload_dup(var->env, var);
		*tmp = ft_strjoinsp(*tmp, var->env, 0);
		ft_free_secure(&var->env);
	}
	else
	{
		while (str_tmp[v_q.i] != '"' && str_tmp[v_q.i])
		{
			fill_quote(str_tmp, var, &v_q);
			*tmp = ft_strjoinsp(*tmp, v_q.t, 0);
			v_q.i++;
		}
	}
}

static void	single_quote(char *str_tmp, t_var *var, char **tmp)
{
	t_var_quote	v_q;

	v_q.i = 1;
	v_q.t[1] = '\0';
	while (str_tmp[v_q.i] != '\'' && str_tmp[v_q.i])
	{
		fill_quote(str_tmp, var, &v_q);
		*tmp = ft_strjoinsp(*tmp, v_q.t, 0);
		v_q.i++;
	}
}

static int	no_quote(t_var *var, t_varenv *v_e, t_var_quote *v_q)
{
	if (has_in_out(v_q->split_tmp, v_q->i) == true)
		return (-1);
	if (is_env_in_str(v_q->split_tmp[v_q->i]) == true)
	{
		v_q->tmp = ft_strjoin(v_q->tmp, ft_trunc(
					v_q->split_tmp[v_q->i], 0, "$", *var));
		quote_env(v_q->split_tmp[v_q->i], var, v_e);
		var->env = ft_reload_dup(var->env, var);
		v_q->tmp = ft_strjoinsp(v_q->tmp, var->env, 0);
		ft_free_secure(&var->env);
	}
	else
	{
		v_q->j = 0;
		while (v_q->split_tmp[v_q->i][v_q->j])
		{
			if (v_q->split_tmp[v_q->i][v_q->j] == '`' && var->is_pquote == true)
				v_q->t[0] = '|';
			else if (v_q->split_tmp[v_q->i][v_q->j] == '~'
						&& var->is_squote == true)
				v_q->t[0] = ' ';
			else
				v_q->t[0] = v_q->split_tmp[v_q->i][v_q->j];
			v_q->tmp = ft_strjoinsp(v_q->tmp, v_q->t, 0);
			v_q->j++;
		}
	}
	return (0);
}

void	quote_manager(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	var->quote = NULL;
	v_q.split_tmp = ft_split(var->s[v_e->j], ';');
	if (!v_q.split_tmp)
		return ;
	v_q.tmp = NULL;
	var->quote = NULL;
	v_q.i = 0;
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

void	quote_manager_inout(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	var->quote = NULL;
	v_q.split_tmp = ft_split(ft_trunc_start(var->s[v_e->j], "<>", *var), ';');
	if (!v_q.split_tmp)
		return ;
	v_q.tmp = NULL;
	var->quote = NULL;
	v_q.i = 0;
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

/*

/!\
gerer "$ , $USER" et $,$USER pour afficher la , est non $tdutel

gerer les quote dans infile outfile : ls > "<E" doit creer un file <E


echo "$(echo "upg")"	=	echo $(echo "upg")
		upg

echo '$(echo"upg")'
	$(echo"upg")

*/

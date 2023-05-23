/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/23 14:09:25 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_trunc(char *str, char c);

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

static bool	is_metachar(char c)
{
	if (c == '.' || c == ',' || c == '\\' || c == '^' || c == '$'
		|| c == '*' || c == '+' || c == '?')
		return (true);
	else
		return (false);
}

static void	add_env_arg(t_var *var, int j)
{
	int		i;
	int		k;
	char	*var_env;

	var->env = NULL;
	i = 0;
	k = 0;
	while (var->s[j][i] != '$')
		i++;
	while (var->s[j][i + 1 + k] && !is_metachar(var->s[j][i + 1 + k]))
		k++;
	var_env = ft_substr(var->s[j], i + 1, k);
	if (var_env[0] == '\0')
	{
		var->env = ft_strdup("$");
		return ;
	}
	i = 0;
	while (var->envp[i] && ft_strnstr
		(var->envp[i], var_env, ft_strlen(var_env)) == NULL)
		i++;
	if (var->envp[i] && var->envp[i][ft_strlen(var_env)] == '=')	//evite les $HOM :  =/nfs/ho...
		var->env = ft_strjoin(var->env, ft_substr
				(var->envp[i], k + 1, ft_strlen(var->envp[i])));
	else
		var->env = ft_strjoin(var->env, NULL);
}
		// j = 0;
		// i = 0;
		// while (ft_strlen(var_env - j) > 0 && ft_strnstr(var->envp[i],
		// 		var_env, ft_strlen(var_env - j)) == NULL)
		// {
		// 	while (var->envp[i] && ft_strnstr(var->envp[i], var_env,
		// 			ft_strlen(var_env - j)) == NULL)
		// 		i++;
		// 	if (!var->envp[i])
		// 	{
		// 		j++;
		// 		i = 0;
		// 	}
		// }
		// if (ft_strlen(var_env - j) == 0)
		// 	var->env = ft_strjoin(var->env, NULL);
		// else
		// 	var->env = ft_strjoin(var->env, ft_substr
		// 			(var->envp[i], k + 1 - j, ft_strlen(var->envp[i] - j)));


	// l = k;
	// while (var->s[j][i + 1 + l])
	// 	l++;
	// env_rest = ft_substr(var->s[j], k + 1, l);

	// env_rest = ft_substr(env_rest, i, ft_strlen(env_rest));

void	token_builtin(t_var *var)
{
	int		j;

	var->arg = NULL;
	j = var->i + 1;
	while (var->s[j])
	{
		if (not_in_out(var->s, j) == true && is_env_in(*var, j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[j]);
		else if (is_env_in(*var, j) == true)
		{
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[j], '$'));
			add_env_arg(var, j);
			var->arg = ft_strjoin(var->arg, var->env);
		}
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
		if (not_in_out(var->s, j) == true && is_env_in(*var, j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[j]);
		else if (is_env_in(*var, j) == true)
		{
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[j], '$'));
			add_env_arg(var, j);
			var->arg = ft_strjoin(var->arg, var->env);
		}
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
*/

static char	*ft_trunc(char *str, char c)
{
	char	*s;
	int		i;
	int		j;

	if (str[0] == c)
		return ("");
	i = 0;
	while (str[i] && str[i] != c)
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

//	gerer plusieurs $variable a la suite (attache ou non)
//	coder $$ et $?
//	gerer si str apres la $variable (ex: $USERhello		tdutelhello)

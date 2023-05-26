/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/26 15:43:41 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_trunc(char *str, int start, char c);
// void	add_env_arg2(t_var *var, int j, char *var_env, int k);

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
	if (c == '.' || c == ',' || c == '/' || c == '\\' || c == '^' || c == '$'
		|| c == '-' || c == '+' || c == '=' || c == '?' || c == '!'
		|| c == '@' || c == '#' || c == '%' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == ':' || c == '~')
		return (true);
	else
		return (false);
}

// static void	add_env_arg(t_var *var, int j)
// {
// 	int		i;
// 	int		k;
// 	char	*var_env;

// 	var->env = NULL;
// 	i = 0;
// 	k = 0;
// 	while (var->s[j][i] != '$')
// 		i++;
// 	while (var->s[j][i + 1 + k] && !is_metachar(var->s[j][i + 1 + k]))
// 		k++;
// 	var_env = ft_substr(var->s[j], i + 1, k);
// 	if (var_env[0] == '\0')
// 	{
// 		var->env = ft_strdup("$");
// 		return ;
// 	}
// 	add_env_arg2(var, j, var_env, k);
// }

// void	add_env_arg2(t_var *var, int j, char *var_env, int k)
// {
// 	int		i;
// 	int		l;

// 	i = 0;
// 	l = 0;
// 	while (var->s[j][l] != '$')
// 		l++;
// 	while (var->envp[i] && ft_strnstr
// 		(var->envp[i], var_env, ft_strlen(var_env)) == NULL)
// 		i++;
// 	if (var->envp[i] && var->envp[i][ft_strlen(var_env)] == '=')	//evite les $HOM :  =/nfs/ho...
// 		var->env = ft_strjoin(var->env, ft_substr
// 				(var->envp[i], k + 1, ft_strlen(var->envp[i]) - k));
// 	else
// 		var->env = ft_strjoin(var->env, NULL);
// 	if (var->s[j][l + 1 + k] == '$')	// == $
// 		add_env_arg2(var, j, var_env, k);
// 		// var->env = ft_strjoin(var->env, ft_substr(var->s[j], l + 1 + k,
// 		// 			ft_strlen(ft_trunc(ft_substr(var->s[j], 1,
// 		// 						ft_strlen(var->s[j])), '$'))));
// }

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


static int	add_env_arg(t_var *var, int j, int l);

static void	env_arg(t_var *var, int j)
{
	int	l;

	var->env = NULL;
	l = 0;
	while (add_env_arg(var, j, l) == 0)
	{
		l++;
	}
}

static int	add_env_arg(t_var *var, int j, int l)
{
	int		i;
	int		k;
	int		m;
	char	*var_env;

	i = -1;
	k = 0;
	m = 0;
	while (m <= l)
	{
		i++;
		while (var->s[j][i] && var->s[j][i] != '$')
			i++;
		while (var->s[j][i + 1 + k] && !is_metachar(var->s[j][i + 1 + k]))
			k++;
		if (m != l)
		{
			i = i + k;
			k = 0;
		}
		m++;
	}
	var_env = ft_substr(var->s[j], i + 1, k);
	if (var_env[0] == '\0')
	{
		var->env = ft_strjoin(var->env, "$");
		if (var->s[j][i + 1 + k] != '\0')
			return (0);
		else
			return (1);
	}
	m = 0;
	while (var->envp[m] && ft_strnstr
		(var->envp[m], var_env, ft_strlen(var_env)) == NULL)
		m++;
	if (var->envp[m] && var->envp[m][ft_strlen(var_env)] == '=')
		var->env = ft_strjoin(var->env, ft_substr
				(var->envp[m], k + 1, ft_strlen(var->envp[m]) - k));
	else
		var->env = ft_strjoin(var->env, NULL);
	if (var->s[j][i + 1 + k] != '$')
		var->env = ft_strjoin(var->env, ft_substr(var->s[j], i + 1 + k,
					ft_strlen(ft_trunc(var->s[j], i + 1 + k, '$'))));
	if (var->s[j][i + 1 + k + ft_strlen(ft_trunc(var->s[j], i + 1 + k, '$'))] == '$')
		return (0);
	else
		return (1);
}

	// add_env_argbis(var, j, var_env, k);

// void	add_env_argbis(t_var *var, int j, char *var_env, int k)
// {
// 	int		i;
// 	int		l;

// 	i = 0;
// 	l = 0;
// 	while (var->s[j][l] != '$')
// 		l++;
// 	while (var->envp[i] && ft_strnstr
// 		(var->envp[i], var_env, ft_strlen(var_env)) == NULL)
// 		i++;
// 	if (var->envp[i] && var->envp[i][ft_strlen(var_env)] == '=')	//evite les $HOM :  =/nfs/ho...
// 		var->env = ft_strjoin(var->env, ft_substr
// 				(var->envp[i], k + 1, ft_strlen(var->envp[i]) - k));
// 	else
// 		var->env = ft_strjoin(var->env, NULL);
// }

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
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[j], 0, '$'));
			env_arg(var, j);
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
			var->arg = ft_strjoinsp(var->arg, ft_trunc(var->s[j], 0, '$'));
			env_arg(var, j);
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

static char	*ft_trunc(char *str, int start, char c)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	k = 0;
	if (str[i] == c)
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

//	gerer plusieurs $variable a la suite (attache ou non)
//	gerer $USER+$HOME par exemple
//	coder $$ et $?
//	gerer si str apres la $variable (ex: $USERhello		tdutelhello)

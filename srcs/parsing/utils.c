/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:13:16 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/08 12:04:38 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	var_init(t_var *var)
{
	var->spipe = ft_split(var->str, '|');
	var->s = ft_split(var->spipe[var->index], ' ');
	var->new_tkn = malloc(sizeof(t_token));
	var->quote = NULL;
	if (!var->new_tkn)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	var->new_tkn->content = malloc(sizeof(char *) * 2);
	if (!var->new_tkn->content)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	if (!var->spipe || !var->s || !var->s[var->i])
		return (false);
	return (true);
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == true || ft_strcmp(str, "pwd") == true
		|| ft_strcmp(str, "echo") == true || ft_strcmp(str, "export") == true
		|| ft_strcmp(str, "unset") == true || ft_strcmp(str, "env") == true
		|| ft_strcmp(str, "exit") == true)
		return (true);
	else
		return (false);
}

bool	has_in_out(char **s, int j)
{
	if ((s[j][0] == '<') || (s[j][0] == '<' && s[j][1] == '<')
	|| (s[j][0] == '>') || (s[j][0] == '>' && s[j][1] == '>')
	|| (s[j - 1][0] == '<' && s[j - 1][1] == '\0')
	|| (s[j - 1][0] == '>' && s[j - 1][1] == '\0')
	|| (s[j - 1][0] == '<' && s[j - 1][1] == '<' && s[j - 1][2] == '\0')
	|| (s[j - 1][0] == '>' && s[j - 1][1] == '>' && s[j - 1][2] == '\0'))
		return (true);
	return (false);
}

char	*check_var(t_var *var, t_varenv *v_e)
{
	v_e->j = var->i;
	if (is_env_in(*var, v_e->j) == true)
	{
		var->s_p = ft_strjoinsp(NULL, ft_trunc(var->s[0], 0, '$', *var));
		env_arg(var, v_e);
		var->s_p = ft_freestrjoin(var->s_p, var->env);
		return (var->s_p);
	}
	else
		return (ft_strdup(var->s_p));
}

char	*ft_trunc(char *str, int start, char c, t_var var)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	j = 0;
	k = 0;
	if (!str || str[i] == c)
		return ("");
	while (str[i] && str[i] != c)
	{
		i++;
		k++;
	}
	s = malloc(sizeof(char) * (k + 1));
	if (!s)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	j = 0;
	while (j < k)
	{
		if (str[start + j] == '`' && var.is_pquote == true)
			s[j] = '|';
		else if (str[start + j] == '~' && var.is_squote == true)
			s[j] = ' ';
		else
			s[j] = str[start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_truncs(char *str, int start, char *c, t_var var)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	j = 0;
	k = 0;
	while (c[k])
	{
		if (!str || str[i] == c[k])
			return ("");
		k++;
	}
	k = 0;
	while (str[i] && str[i] != c[j])
	{
		while (c[j] && str[i] != c[j])
			j++;
		if (c[j])
			break ;
		i++;
		k++;
		j = 0;
	}
	s = malloc(sizeof(char) * (k + 1));
	j = 0;
	while (j < k)
	{
		if (str[start + j] == '`' && var.is_pquote == true)
			s[j] = '|';
		else if (str[start + j] == '~' && var.is_squote == true)
			s[j] = ' ';
		else
			s[j] = str[start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

// char	*ft_trunc(char *str, int start, char c)
// {
// 	char	*s;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = start;
// 	j = 0;
// 	k = 0;
// 	if (!str || str[i] == c)
// 		return ("");
// 	while (str[i] && str[i] != c)
// 	{
// 		i++;
// 		k++;
// 	}
// 	s = malloc(sizeof(char) * (k + 1));
// 	if (!s)
// 		exit(EXIT_FAILURE); //TODO: call function pointer exit
// 	j = 0;
// 	while (j < k)
// 	{
// 		s[j] = str[start + j];
// 		j++;
// 	}
// 	s[j] = '\0';
// 	return (s);
// }

/*bool	is_last_infile(char **s, int i)
{
	int	j;

	j = i;
	while (s[j] != NULL && s[j][0] != '|')
		j++;
	j--;
	while (s[j][0] != '<' && j >= 0)
		j--;
	if (i == j)
		return (true);
	else
		return (false);
}*/

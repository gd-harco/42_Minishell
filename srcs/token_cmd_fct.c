/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/17 14:05:05 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*str_trunc(char *str, char c);

void	token_builtin(t_token *new, char **s, int **i)
{
	char	*arg;
	int		j;

	arg = NULL;
	j = **i + 1;
	while (s[j] && s[j][0] != '|')
	{
		if (not_in_out(s, j) == true && is_pipe_in(s, j) == false)
			arg = ft_strjoinsp(arg, s[j]);
		else if (not_in_out(s, j) == true && is_pipe_in(s, j) == true)
		{
			arg = ft_strjoinsp(arg, str_trunc(s[j], '|'));
			break ;
		}
		j++;
	}
	new->type = BUILTIN;
	new->content[0] = ft_strdup(s[**i]);
	new->content[1] = ft_strdup(arg);
}

void	token_cmd(char *str, t_token *new, int **i, char **envp)
{
	char	*arg;
	int		j;
	char	**path;
	char	*s_p;
	char	**s;

	s = ft_split (str, ' ');
	arg = NULL;
	path = get_path(envp);
	s_p = process(str, path, *i);
	j = **i + 1;
	while (s[j] && (s[j][0] != '|' || s[j][0] == '\0'))
	{
		if (not_in_out(s, j) == true && is_pipe_in(s, j) == false)
			arg = ft_strjoinsp(arg, s[j]);
		else if (not_in_out(s, j) == true && is_pipe_in(s, j) == true)
		{
			arg = ft_strjoinsp(arg, str_trunc(s[j], '|'));
			break ;
		}
		j++;
	}
	new->type = CMD;
	new->content[0] = ft_strdup(s_p);
	new->content[1] = ft_strdup(arg);
}

bool	is_pipe_in(char **s, int j)
{
	int	i;

	i = 0;
	while (s[j][i])
	{
		if (s[j][i] == '|')
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



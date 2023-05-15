/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/15 16:07:38 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	token_infile(t_token *new, char **s, int **i)
{
	if (is_last_infile(s, **i) != true)
	{
		++**i;
		return (-1);
	}
	if (s[**i][1] == '<')
		new->type = HERE_DOC;
	else if (s[**i][1] != '\0')
	{
		new->type = FILE_IN;
		new->content[0] = ft_strdup(s[**i]);
		new->content[1] = NULL;
		return (0);
	}
	else
		new->type = FILE_IN;
	new->content[0] = ft_strdup(s[++**i]);
	new->content[1] = NULL;
	return (0);
}

void	token_outfile(t_token *new, char **s, int **i)
{
	if (s[**i + 1] && s[**i][1] == '>' )
		new->type = FILE_OUT_APPEND;
	else
		new->type = FILE_OUT;
	new->content[0] = ft_strdup(s[++**i]);
	new->content[1] = NULL;
}

void	token_pipe(t_token *new, char **s, int **i)
{
	new->type = PIPE;
	new->content[0] = ft_strdup(s[**i]);
	new->content[1] = NULL;
}

void	token_builtin(t_token *new, char **s, int **i)
{
	char	*arg;
	int		j;

	arg = NULL;
	j = **i + 1;
	while (s[j] && s[j][0] != '|')
	{
		if (s[j][0] == '-' || not_in_out(s, j, NULL) == true)
			arg = ft_strjoinsp(arg, s[j]);
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
		if (s[j][0] == '-' || not_in_out(s, j, s_p) == true)
			arg = ft_strjoinsp(arg, s[j]);
		j++;
	}
	new->type = CMD;
	new->content[0] = ft_strdup(s_p);
	new->content[1] = ft_strdup(arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/12 17:21:42 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	bool	is_builtin(char *str);

static t_token	*token_last(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*tail;

	if (!token)
		return ;
	if (*token)
	{
		tail = token_last(*token);
		tail->next = new;
	}
	else
		*token = new;
}

t_token	*get_token(char *str, char **envp)
{
	t_token	*t_new;
	t_token	*tmp;
	char	**s;
	int		i;

	i = 0;
	s = ft_split(str, ' ');
	t_new = token_init(str, envp, &i);
	while (s[i++])
	{
		tmp = token_init(str, envp, &i);
		if (tmp != NULL)
			token_add_back(&t_new, tmp);
	}
	return (t_new);
}


t_token	*token_init(char *str, char **envp, int *i)
{
	t_token	*new;
	char	**s;
	int		j;
	char	*arg;
	char	**path;
	char	*s_p;

	arg = NULL;
	s_p = NULL;
	s = ft_split (str, ' ');
	new = malloc(sizeof(t_token));
	new->content = malloc(sizeof(char *) * 2);
	if (!new->content)
		return (NULL);
	// while (s[i] && s[i][0] != '|')
	// {
		if (!s[*i])
			return (NULL);
		if (s[*i][0] == '<')
		{
			if (s[*i][1] == '<')
				new->type = HERE_DOC;
			else
				new->type = FILE_IN;
			new->content[0] = ft_strdup(s[++*i]);
			new->content[1] = NULL;
		}
		else if (s[*i + 1] && s[*i][0] == '>')
		{
			if (s[*i + 1] && s[*i][1] == '>' )
				new->type = FILE_OUT_APPEND;
			else
				new->type = FILE_OUT;
			new->content[0] = ft_strdup(s[++*i]);
			new->content[1] = NULL;
		}
		else if (s[*i][0] == '-')
		{
			return (NULL);
		}
		else if (s[*i + 1] && s[*i][0] == '|')
		{
			new->type = PIPE;
			new->content[0] = ft_strdup(s[*i]);
			new->content[1] = NULL;
		}
		else if (is_builtin(s[*i]) == true)
		{
			j = *i + 1;
			while (s[j] && s[j][0] != '|')
			{
				if (s[j][0] == '-')
					arg = ft_strjoin(arg, s[j]);
				j++;
			}
			new->type = BUILTIN;
			new->content[0] = ft_strdup(s[*i]);
			new->content[1] = ft_strdup(arg);
		}
		else
		{
			j = *i + 1;
			while (s[j] && (s[j][0] != '|' || s[j][0] == '\0'))
			{
				if (s[j][0] == '-')
					arg = ft_strjoin(arg, s[j]);
				j++;
			}
			path = get_path(envp);
			s_p = process(str, path, i);
			new->type = CMD;
			new->content[0] = ft_strdup(s_p);
			new->content[1] = ft_strdup(arg);
		}
	// 	*i++;
	// }
	new->next = NULL;
	return (new);
}

static	bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == true || ft_strcmp(str, "pwd") == true
		|| ft_strcmp(str, "echo") == true || ft_strcmp(str, "export") == true
		|| ft_strcmp(str, "unset") == true || ft_strcmp(str, "env") == true
		|| ft_strcmp(str, "exit") == true)
		return (true);
	else
		return (false);
}


// gerer les string (ex : echo hello)
// refaire strjoin pour add space
// gerer var env et '' ""

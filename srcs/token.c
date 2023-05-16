/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/16 15:44:10 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*token_last(t_token *token);
void			token_add_back(t_token **token, t_token *new);

t_token	*get_token(char *str, char **envp)
{
	t_token	*t_new;
	t_token	*tmp;
	char	**s;
	int		i;

	i = 0;
	s = ft_split(str, ' ');
	t_new = token_init(str, envp, &i, s);
	while (s[i++])
	{
		tmp = token_init(str, envp, &i, s);
		if (tmp != NULL)
			token_add_back(&t_new, tmp);
	}
	return (t_new);
}

// t_token	*token_check(char *str, char **envp, int *i)
// {
// 	char	**s;

// 	s = ft_split(str, ' ');
// 	if (!s[*i])
// 		return (NULL);
// 	while (s[*i][0] != '<')
// 	{}
// }

void	token_arg(char **s, int **i)
{
	if (!s[**i])
		return ;
	while (s[**i + 1] && s[**i + 1][0] != '<' && s[**i + 1][0] != '>'
		&& s[**i + 1][0] != '|' && s[**i + 1][0] != '\0')
	{
		++**i;
	}
}

t_token	*token_init(char *str, char **envp, int *i, char **s)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->content = malloc(sizeof(char *) * 2);
	if (!new->content)
		return (NULL);
	if (!s[*i])
		return (NULL);
	if (s[*i][0] == '<')
	{
		if (token_infile(new, s, &i) == -1)
			return (NULL);
	}
	else if (s[*i + 1] && s[*i][0] == '>')
		token_outfile(new, s, &i);
	else if (s[*i][0] == '-')
		return (NULL);
	else if (s[*i + 1] && s[*i][0] == '|')
		token_pipe(new, s, &i);
	else
	{
		if (is_builtin(s[*i]) == true)
			token_builtin(new, s, &i);
		else
			token_cmd(str, new, &i, envp);
		token_arg(s, &i);
	}
	new->next = NULL;
	return (new);
}

// 	else if (is_builtin(s[*i]) == true)
// 		token_builtin(new, s, &i);
// 	else
// 	{	
// 		token_cmd(str, new, &i, envp);
// 		token_arg(s, &i);
// 	}
// 	new->next = NULL;
// 	return (new);
// }

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


//differencier un infile d'un argument de cmd
//	(ex: echo bonjour : echo, bonjour mais aussi bonjour, null	a enlever)
//gerer plusieurs infile	ok
// refaire strjoin pour add space	ok

// gerer les string (ex : echo hello)
// gerer var env et '' ""

//gerer les spaces de '|' ex : echo bonjour|rev	doit faire ruojnob

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:37 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/17 14:53:05 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	heredoc_infile(t_token *new, char **s, int ***i)
{
	if (s[***i][2] != '\0')
		new->content[0] = ft_strdup(ft_substr(s[***i], 2, ft_strlen(s[***i])));
	else
		new->content[0] = ft_strdup(s[++***i]);
	new->type = HERE_DOC;
}

int	token_infile(t_token *new, char **s, int **i)
{
	if (is_last_infile(s, **i) != true)
	{
		if (s[**i][1] == '\0')
			++**i;
		return (-1);
	}
	if (s[**i][1] == '<')
	{
		heredoc_infile(new, s, &i);
	}
	else if (s[**i][1] != '\0')
	{
		new->type = FILE_IN;
		new->content[0] = ft_strdup(ft_substr(s[**i], 1, ft_strlen(s[**i])));
	}
	else
	{
		new->type = FILE_IN;
		new->content[0] = ft_strdup(s[++**i]);
	}
	new->content[1] = NULL;
	return (0);
}

void	token_outfile(t_token *new, char **s, int **i)
{
	if (s[**i + 1] && s[**i][1] == '>' )
	{
		if (s[**i][2] != '\0')
			new->content[0] = ft_strdup(ft_substr(
						s[**i], 2, ft_strlen(s[**i])));
		else
			new->content[0] = ft_strdup(s[++**i]);
		new->type = FILE_OUT_APPEND;
	}
	else if (s[**i][1] != '\0')
	{
		new->type = FILE_OUT;
		new->content[0] = ft_strdup(ft_substr(s[**i], 1, ft_strlen(s[**i])));
	}
	else
	{
		new->type = FILE_OUT;
		new->content[0] = ft_strdup(s[++**i]);
	}
	new->content[1] = NULL;
}

void	token_pipe(t_token *new, char *s)
{
	if (s[0] == '|' && s[1] == '\0')
	{
		new->type = PIPE;
		new->content[0] = ft_strdup("|");
		new->content[1] = NULL;
		return ;
	}
	// si [0] != '|'
	// 	c = ft_split(s, '|');
	// 	gerer le c[0] puis ecrire pipe puis gerer suite
	
	// else token pour premiere partie du char jusquau | puis tkn pipe puis 2eme partie
		// return (token_pipe(new, ft_substr(s, 1, ft_strlen(s))));
}

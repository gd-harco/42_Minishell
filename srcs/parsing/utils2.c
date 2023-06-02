/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/02 16:38:56 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*ft_quote_str(char *str, int *start, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 1;
	j = 0;
	while (str[*start + i] != c)
	{
		i++;
	}
	i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	while (j < i)
	{
		new[j] = str[*start];
		j++;
		*start = *start + 1;
	}
	*start = *start - 1;
	new[j] = '\0';
	return (new);
}

char	*ft_space_str(t_var *var)
{
	int		i;
	char	*new;
	char	to_join[2];

	var->str = ft_strdup(var->str_in);
	i = 0;
	to_join[1] = 0;
	new = NULL;
	while (var->str[i])
	{
		to_join[0] = var->str[i];
		if (var->str[i] == '\'')
			new = ft_strjoin(new, ft_quote_str(var->str, &i, '\''));
		if (var->str[i] == '"')
			new = ft_strjoin(new, ft_quote_str(var->str, &i, '"'));
		else if (var->str[i] == '|')
		{	
			new = ft_strjoin(new, " | ");
			var->nb_pipe++;
		}
		else if (var->str[i] == '<' && var->str[i - 1] != '<')
			new = ft_strjoin(new, " <");
		else if (var->str[i] == '>' && var->str[i - 1] != '>')
			new = ft_strjoin(new, " >");
		else
			new = ft_strjoin(new, to_join);
		i++;
	}
	return (new);
}

/*bool	already_pipe(t_token t_new)		//plus besoin
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}*/

int	ft_nb_pipe(char *str)
{
	int	i;
	int	c;

	if (!str)
		return (0);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

char	*ft_trunc(char *str, int start, char c)
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
	j = 0;
	while (j < k)
	{
		s[j] = str[start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

/*
char	*ft_truncstr(char *str, int start, char *c)
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
		s[j] = str[start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*trunc_rest(char *str, int start, char *c)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	j = 0;
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
	j = 0;
	s = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	while (str[i + j])
	{
		s[j] = str[i + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

*/

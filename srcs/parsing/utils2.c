/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/06 10:16:17 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	*ft_quote_str(char *str, int *start, char c)
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
	char	*temp;

	temp = ft_strdup(var->str_in);
	if (!temp)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	i = 0;
	to_join[1] = 0;
	new = NULL;
	while (temp && temp[i])
	{
		to_join[0] = temp[i];
		if (temp[i] == '\'')
			new = ft_freestrjoin(new, ft_quote_str(temp, &i, '\''));
		if (temp[i] == '"')
			new = ft_freestrjoin(new, ft_quote_str(temp, &i, '"'));
		else if (temp[i] == '|')
		{	
			new = ft_freestrjoin(new, " | ");
			var->nb_pipe++;
		}
		else if (temp[i] == '<' && temp[i - 1] != '<')
			new = ft_freestrjoin(new, " <");
		else if (temp[i] == '>' && temp[i - 1] != '>')
			new = ft_freestrjoin(new, " >");
		else
			new = ft_freestrjoin(new, to_join);
		i++;
	}
	free(temp);
	return (new);
}

static char	*joningsp(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	result[x] = ' ';
	x++;
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

char	*ft_strjoinsp(char *s1, char *s2)
{
	size_t		joined_size;
	char		*result;

	joined_size = (ft_strlen (s1) + ft_strlen (s2));
	result = malloc(sizeof(char) * joined_size + 2);
	if (!result)
	{
		ft_free_process(s1, NULL);
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	}
	if (!s2 && !s1)
		return (NULL);
	if (!s2 && s1)
		return (ft_free_process(result, ft_strdup(s1)));
	if (!s1 && s2)
		return (ft_free_process(result, ft_strdup(s2)));
	return (ft_free_process(s1, joningsp(result, (char *)s2, (char *)s1)));
}

static char	*joning(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

char	*ft_freestrjoin(char *s1, char *s2)
{
	size_t		joined_size;
	char		*result;

	joined_size = (ft_strlen (s1) + ft_strlen (s2));
	result = malloc(sizeof(char) * joined_size + 1);
	if (!result)
	{
		ft_free_process(s1, NULL);
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	}
	if (!s2 && !s1)
		return (NULL);
	if (!s2 && s1)
		return (ft_free_process(result, ft_strdup(s1)));
	if (!s1 && s2)
		return (ft_free_process(result, ft_strdup(s2)));
	return (ft_free_process(s1, joning(result, (char *)s2, (char *)s1)));
}

char	*ft_free_process(char *to_free, char *to_return)
{
	if (to_free)
		free(to_free);
	return (to_return);
}
/*bool	already_pipe(t_token t_new)		//plus besoin
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}*/

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

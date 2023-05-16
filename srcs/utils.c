/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:13:16 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/16 13:57:24 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

bool	not_in_out(char **s, int j)
{
	if ((s[j][0] == '<')
	|| (s[j][0] == '>')
	|| (s[j][0] == '<' && s[j][1] == '<')
	|| (s[j][0] == '>' && s[j][1] == '>')
	|| (s[j - 1][0] == '<')
	|| (s[j - 1][0] == '>')// le cas : cat <Makefile
	|| (s[j - 1][0] == '<' && s[j - 1][1] == '<')// '\0' permet de gerer 
	|| (s[j - 1][0] == '>' && s[j - 1][1] == '>'))
		return (false);
	// while (j >= 0 && s[j][0] != '|')	//on remonte la chaine pour voir si
	// {									// s correspond a un arg d'une commande
	// 	if (access(s_p, X_OK) != -1 || is_builtin(s[j]) == true)
	// 		return (true);
	// 	j--;
	// }
	// return (false);
	return (true);
}

bool	is_last_infile(char **s, int i)
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

char	*ft_strjoinsp(char const *s1, char const *s2)
{
	size_t		joined_size;
	char		*result;
	size_t		size_s1;
	size_t		size_s2;

	if (!s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	size_s1 = ft_strlen (s1);
	size_s2 = ft_strlen (s2);
	joined_size = (size_s1 + size_s2);
	result = malloc(sizeof(char) * joined_size + 2);
	if (!result)
		return (NULL);
	return (joning(result, (char *)s2, (char *)s1));
}